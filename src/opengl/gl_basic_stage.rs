use super::{
  gl_postfx_scene,
  gl_texture::{self, ImgAttr},
  GLBasicScene, GLPostFXScene, GLStage, GLTexture,
};

use crate::{
  any::consts::{BASIC_ATLAS_GAP, BLUR_INPUT_ATLAS_GAP, INITIAL_SIZE},
  funcs::util::{save_atlas_png_file, save_atlas_toml_file},
  structs::{EnvArgs, Glyph, Input, Rect},
};

use iron_ingot::{FVec2, UVec2};
use itertools::Itertools;
use png::ColorType;
use rayon::prelude::*;
use sdl2::{pixels::Color, video::Window};

use std::{
  cell::{Cell, RefCell},
  env,
  error::Error,
  fmt::{self, Display, Formatter},
  fs,
};

#[derive(Copy, Clone, Debug)]
struct AtlasOverflowError;

impl Error for AtlasOverflowError {}

impl Display for AtlasOverflowError {
  fn fmt(&self, formatter: &mut Formatter<'_>) -> fmt::Result {
    write!(
      formatter,
      "There is not enough space to fill the texture given!"
    )
  }
}

#[derive(Debug)]
pub(crate) struct GLBasicStage {
  env_args: EnvArgs,
  // size: UVec2,
  _glyph_texs: Vec<GLTexture>,
  blur_input_glyphs: Option<Vec<RefCell<Glyph>>>,
  glyphs: Vec<RefCell<Glyph>>,
  blur_input_scene: Option<RefCell<GLBasicScene>>,
  blur_scenes: Option<RefCell<Vec<GLPostFXScene>>>,
  basic_scene: GLBasicScene,
  // identity_scene: GLPostFXScene,
  current_tex_position: Cell<UVec2>,
  max_tex_h: Cell<u32>,
  used_size: Cell<UVec2>,
}

impl GLBasicStage {
  pub(crate) fn new(_size: UVec2) -> Self {
    let mut command_line_args = env::args().take(3);
    command_line_args.next();
    let input_dir_path = command_line_args
      .next()
      .expect("The first argument which is an input directory path is missing and it is required!")
      .trim_end_matches('/')
      .to_owned();
    let output_dir_path = command_line_args
      .next()
      .expect(
        "The second argument which is an output directory path is missing and it is required!",
      )
      .trim_end_matches('/')
      .to_owned();
    let ttf = sdl2::ttf::init().unwrap();
    let input = toml::from_str::<Input>(
      &fs::read_to_string(format!("{input_dir_path}/input.toml")).unwrap_or_else(|_| {
        panic!("Could not read \"{input_dir_path}/input.toml\"!");
      }),
    )
    .unwrap_or_else(|err| {
      if let Some((line, col)) = err.line_col() {
        panic!(
          "Syntax error occured at line {line}, col {col} in \"{input_dir_path}/input.toml\"!"
        );
      } else {
        panic!("Syntax error occured in \"{input_dir_path}/input.toml\"!");
      }
    });
    let (blur_input_glyphs, glyphs, glyph_texs) = input
      .fonts
      .iter()
      .map(|(font_file_name, font)| {
        (
          font_file_name,
          font,
          ttf
            .load_font(format!("{input_dir_path}/{}", font_file_name), font.size)
            .unwrap(),
        )
      })
      .flat_map(|(font_file_name, font, ttf_font)| {
        (' '..='~')
          .map(|ch| {
            let mut tex = GLTexture::new(gl_texture::Arg {
              img_attr: ImgAttr::Surface(ttf_font.render_char(ch).blended(Color::WHITE).unwrap()),
              tex_unit: 0,
              min_filter: gl::LINEAR,
              mag_filter: gl::LINEAR,
              wrap_s: gl::CLAMP_TO_EDGE,
              wrap_t: gl::CLAMP_TO_EDGE,
              internal_format: gl::R8,
            });
            tex.init();
            let glyph = Glyph {
              font_name: font_file_name[..font_file_name.find('.').unwrap()].to_owned(),
              font_size: font.size,
              name: ch.to_string(),
              atlas_id: tex.get_id(),
              atlas_size: tex.get_size(),
              line_spacing: ttf_font.recommended_line_spacing(),
              advance: ttf_font.find_glyph_metrics(ch).unwrap().advance,
              prev_position: UVec2::new(()),
              position: UVec2::new(()),
              size: tex.get_size(),
              is_rotated: tex.get_size().get_x() < tex.get_size().get_y(),
            };
            (
              if font.generate_blur.is_some() && font.generate_blur.unwrap() {
                Some(Glyph {
                  name: ch.to_string() + "_blur",
                  ..glyph.clone()
                })
              } else {
                None
              },
              glyph,
              tex,
            )
          })
          .collect::<Vec<_>>()
      })
      .multiunzip::<(Vec<_>, Vec<_>, Vec<_>)>();
    let can_generate_blur = input
      .fonts
      .par_iter()
      .any(|(_, font)| font.generate_blur.is_some());
    Self {
      env_args: EnvArgs {
        input_dir_path,
        output_dir_path,
      },
      // size,
      _glyph_texs: glyph_texs,
      blur_input_glyphs: if can_generate_blur {
        let mut blur_input_glyphs = blur_input_glyphs
          .into_par_iter()
          .filter_map(|blur_input_glyph| blur_input_glyph.map(RefCell::new))
          .collect::<Vec<_>>();
        blur_input_glyphs.par_sort_unstable_by(|a, b| {
          let a = a.borrow();
          let b = b.borrow();
          b.size
            .get_x()
            .min(b.size.get_y())
            .cmp(&a.size.get_x().min(a.size.get_y()))
        });
        Some(blur_input_glyphs)
      } else {
        None
      },
      glyphs: glyphs.into_par_iter().map(RefCell::new).collect(),
      blur_input_scene: if can_generate_blur {
        Some(RefCell::new(GLBasicScene::new(
          UVec2::new((INITIAL_SIZE >> 1, INITIAL_SIZE >> 1)),
          UVec2::new((INITIAL_SIZE, INITIAL_SIZE)),
          1,
        )))
      } else {
        None
      },
      blur_scenes: if can_generate_blur {
        Some(RefCell::new(vec![
          GLPostFXScene::new(gl_postfx_scene::Arg {
            size: UVec2::new((INITIAL_SIZE >> 1, INITIAL_SIZE >> 1)),
            frag_shader_code: include_bytes!("../../res/blur.frag"),
            from_tex_unit: 1,
            to_tex_unit: Some(2),
            internal_format: gl::R8,
            init_uniforms: |program| unsafe {
              gl::ProgramUniform1i(program, 2, 1);
            },
          }),
          GLPostFXScene::new(gl_postfx_scene::Arg {
            size: UVec2::new((INITIAL_SIZE >> 1, INITIAL_SIZE >> 1)),
            frag_shader_code: include_bytes!("../../res/blur.frag"),
            from_tex_unit: 2,
            to_tex_unit: Some(3),
            internal_format: gl::R8,
            init_uniforms: |program| unsafe {
              gl::ProgramUniform1i(program, 2, 0);
            },
          }),
        ]))
      } else {
        None
      },
      basic_scene: GLBasicScene::new(
        UVec2::new((INITIAL_SIZE, INITIAL_SIZE)),
        UVec2::new((INITIAL_SIZE, INITIAL_SIZE)),
        4,
      ),
      // identity_scene: GLPostFXScene::new(gl_postfx_scene::Arg {
      //   size,
      //   frag_shader_code: include_bytes!("../../res/identity.frag"),
      //   from_tex_unit: 4,
      //   to_tex_unit: None,
      //   internal_format: gl::RGBA8,
      //   init_uniforms: |_| {},
      // }),
      current_tex_position: Cell::new(UVec2::new(())),
      max_tex_h: Cell::new(0),
      used_size: Cell::new(UVec2::new(())),
    }
  }

  fn show_atlas(
    &self,
    basic_scene: &GLBasicScene,
    glyphs: &[RefCell<Glyph>],
    gap: u32,
  ) -> Result<(), AtlasOverflowError> {
    self
      .current_tex_position
      .set(UVec2::new((gap >> 1, gap >> 1)));
    self.max_tex_h.set(0);
    self.used_size.set(UVec2::new(()));
    basic_scene.get_fbo().use_();
    unsafe {
      gl::Viewport(
        0,
        0,
        basic_scene.get_fbo().get_size().get_x() as _,
        basic_scene.get_fbo().get_size().get_y() as _,
      );
    }
    for (i, glyph) in glyphs.iter().enumerate().filter(|(_, glyph)| {
      let glyph = glyph.borrow();
      glyph.size.get_x() != 0 || glyph.size.get_y() != 0
    }) {
      if self.show_glyph(basic_scene, glyph, gap).is_err() {
        Glyph::reset_positions(&glyphs[..i]);
        return Err(AtlasOverflowError);
      }
    }
    Ok(())
  }

  fn show_glyph(
    &self,
    basic_scene: &GLBasicScene,
    glyph: &RefCell<Glyph>,
    gap: u32,
  ) -> Result<(), AtlasOverflowError> {
    let atlas_tex_size: UVec2;
    {
      let glyph = glyph.borrow();
      atlas_tex_size = UVec2::new((
        glyph.size.get_x().max(glyph.size.get_y()),
        glyph.size.get_x().min(glyph.size.get_y()),
      ));
      if self.current_tex_position.get().get_x() + atlas_tex_size.get_x() + (gap >> 1)
        > basic_scene.get_virtual_size().get_x()
      {
        self.current_tex_position.set(UVec2::new((
          gap >> 1,
          self.current_tex_position.get().get_y() + self.max_tex_h.get() + gap,
        )));
        self.max_tex_h.set(0);
        if self.current_tex_position.get().get_x() + atlas_tex_size.get_x() + (gap >> 1)
          > basic_scene.get_virtual_size().get_x()
          || self.current_tex_position.get().get_y() + atlas_tex_size.get_y() + (gap >> 1)
            > basic_scene.get_virtual_size().get_y()
        {
          return Err(AtlasOverflowError);
        }
      }
      unsafe {
        gl::BindTextureUnit(0, glyph.atlas_id);
      }
      basic_scene.set_atlas_size(glyph.atlas_size);
      basic_scene.set_rect(Rect {
        position: self.current_tex_position.get().into(),
        size: atlas_tex_size,
        tex_position: glyph.position,
        tex_size: glyph.size,
        is_rotated: glyph.size.get_x() < glyph.size.get_y(),
      });
      basic_scene.show();
    }
    glyph.borrow_mut().position =
      self.current_tex_position.get() - UVec2::new((gap >> 1, gap >> 1));
    self
      .current_tex_position
      .set(self.current_tex_position.get() + UVec2::new((atlas_tex_size.get_x() + gap, 0)));
    self
      .max_tex_h
      .set(self.max_tex_h.get().max(atlas_tex_size.get_y()));
    self.used_size.set(UVec2::new((
      self
        .used_size
        .get()
        .get_x()
        .max(self.current_tex_position.get().get_x() - (gap >> 1)),
      self
        .used_size
        .get()
        .get_y()
        .max(self.current_tex_position.get().get_y() + self.max_tex_h.get() + (gap >> 1)),
    )));
    Ok(())
  }

  fn grow(&self) {
    self.blur_input_scene.as_ref().unwrap().borrow_mut().grow();
    self.grow_blur_scenes();
  }

  fn grow_blur_scenes(&self) {
    for blur_scene in self.blur_scenes.as_ref().unwrap().borrow_mut().iter_mut() {
      blur_scene.grow();
    }
  }

  fn update_blur_input_glyphs(&self) {
    for blur_input_glyph in self.blur_input_glyphs.as_ref().unwrap() {
      self.update_blur_input_glyph(blur_input_glyph);
    }
  }

  fn update_blur_input_glyph(&self, blur_input_glyph: &RefCell<Glyph>) {
    let mut blur_input_glyph = blur_input_glyph.borrow_mut();
    blur_input_glyph.atlas_id = self.blur_scenes.as_ref().unwrap().borrow()[1]
      .get_tex_id()
      .unwrap();
    blur_input_glyph.atlas_size = self
      .blur_input_scene
      .as_ref()
      .unwrap()
      .borrow()
      .get_virtual_size();
    blur_input_glyph.prev_position = blur_input_glyph.position;
    blur_input_glyph.is_rotated = blur_input_glyph.size.get_x() < blur_input_glyph.size.get_y();
    blur_input_glyph.size = UVec2::new((
      blur_input_glyph
        .size
        .get_x()
        .max(blur_input_glyph.size.get_y())
        + BLUR_INPUT_ATLAS_GAP,
      blur_input_glyph
        .size
        .get_x()
        .min(blur_input_glyph.size.get_y())
        + BLUR_INPUT_ATLAS_GAP,
    ));
  }

  fn update_blur_scenes_scale(&self) {
    let scale = FVec2::from(self.used_size.get())
      / FVec2::from(
        self
          .blur_input_scene
          .as_ref()
          .unwrap()
          .borrow()
          .get_virtual_size(),
      );
    for blur_scene in self.blur_scenes.as_ref().unwrap().borrow().iter() {
      blur_scene.set_scale(scale);
    }
  }

  fn blur(&self) {
    let blur_scenes = self.blur_scenes.as_ref().unwrap().borrow();
    const BLUR: usize = 4;
    for i in 0..BLUR {
      for blur_scene in blur_scenes.iter() {
        blur_scene.show();
      }
      if i == 0 {
        blur_scenes[0].set_from_tex_unit(3);
      }
    }
    blur_scenes[0].set_from_tex_unit(1);
  }

  fn update_glyphs(&self) {
    for glyph in &self.glyphs {
      self.update_glyph(glyph);
    }
  }

  fn update_glyph(&self, glyph: &RefCell<Glyph>) {
    let mut glyph = glyph.borrow_mut();
    glyph.atlas_id = self.basic_scene.get_fbo().get_tex_id();
    glyph.atlas_size = self.basic_scene.get_virtual_size();
    glyph.prev_position = glyph.position;
    glyph.size = UVec2::new((
      glyph.size.get_x().max(glyph.size.get_y()),
      glyph.size.get_x().min(glyph.size.get_y()),
    ));
  }
}

impl GLStage for GLBasicStage {
  fn show(&mut self, _window: &Window) {
    if let Some(blur_input_scene) = &self.blur_input_scene {
      while self
        .show_atlas(
          &blur_input_scene.borrow_mut(),
          self.blur_input_glyphs.as_ref().unwrap(),
          BLUR_INPUT_ATLAS_GAP,
        )
        .is_err()
      {
        self.grow();
      }
      self.update_blur_input_glyphs();
      self.update_blur_scenes_scale();
      self.blur();
      self.glyphs.append(self.blur_input_glyphs.as_mut().unwrap());
    }
    self.glyphs.par_sort_unstable_by(|a, b| {
      let a = a.borrow();
      let b = b.borrow();
      b.size
        .get_x()
        .min(b.size.get_y())
        .cmp(&a.size.get_x().min(a.size.get_y()))
    });
    while self
      .show_atlas(&self.basic_scene, &self.glyphs, BASIC_ATLAS_GAP)
      .is_err()
    {
      self.basic_scene.grow();
    }
    self.update_glyphs();
    save_atlas_png_file(
      self.basic_scene.get_physical_size(),
      &self.env_args,
      ColorType::Grayscale,
    );
    save_atlas_toml_file(&mut self.glyphs, &self.env_args);

    // Show the output atlas onto the screen.
    //
    // unsafe {
    //   gl::Viewport(0, 0, self.size.get_x() as _, self.size.get_y() as _);
    //   gl::Enable(gl::BLEND);
    // }
    // self.identity_scene.set_scale(
    //   FVec2::from(self.used_size.get()) / FVec2::from(self.basic_scene.get_virtual_size()),
    // );
    // self.identity_scene.show();
    // unsafe {
    //   gl::Disable(gl::BLEND);
    // }
    // window.gl_swap_window();
  }
}
