use crate::structs::{Atlas, AtlasRegion, EnvArgs, Glyph};
use iron_ingot::UVec2;
use png::{BitDepth, ColorType, Compression, FilterType, ScaledFloat, SourceChromaticities};
use rayon::prelude::*;

use std::{
  borrow::Cow,
  cell::RefCell,
  fs::{self, File},
  io::BufWriter,
};

pub(crate) fn flip_vertically(pixels: &[u8], pitch: u32) -> Cow<[u8]> {
  pixels
    .par_chunks_exact(pitch as _)
    .rev()
    .flatten()
    .cloned()
    .collect()
}

pub(crate) fn save_atlas_toml_file(glyphs: &mut [RefCell<Glyph>], env_args: &EnvArgs) {
  let atlas_toml = toml::to_string_pretty(&Atlas {
    regions: glyphs
      .iter_mut()
      .map(|glyph| AtlasRegion::from(glyph.get_mut().clone()))
      .collect(),
  })
  .unwrap();
  fs::create_dir_all(&env_args.output_dir_path).unwrap();
  fs::write(
    format!(
      "{}/{}.toml",
      env_args.output_dir_path,
      &env_args.input_dir_path[(env_args
        .input_dir_path
        .rfind('/')
        .map(|id| id as isize)
        .unwrap_or(-1)
        + 1) as _..],
    ),
    atlas_toml,
  )
  .unwrap();
}

pub(crate) fn save_atlas_png_file(size: UVec2, env_args: &EnvArgs, color_type: ColorType) {
  let channel_count: u32 = match color_type {
    ColorType::Grayscale => 1,
    ColorType::Rgb => 3,
    ColorType::Rgba => 4,
    color_type => {
      panic!(
        "{color_type:?} is unsupported for saving the current framebuffer to an atlas PNG file!"
      )
    }
  };
  let mut atlas = Vec::<u8>::new();
  atlas.resize((size.get_x() * size.get_y() * channel_count) as _, 0);
  unsafe {
    gl::ReadnPixels(
      0,
      0,
      size.get_x() as _,
      size.get_y() as _,
      match color_type {
        ColorType::Grayscale => gl::RED,
        ColorType::Rgb => gl::RGB,
        ColorType::Rgba => gl::RGBA,
        color_type => panic!(
          "{color_type:?} is unsupported for saving the current framebuffer to an atlas PNG file!"
        ),
      },
      gl::UNSIGNED_BYTE,
      atlas.len() as _,
      atlas.as_mut_ptr() as *mut _,
    );
  }
  fs::create_dir_all(&env_args.output_dir_path).unwrap();
  save_png_file(
    &format!(
      "{}/{}.png",
      env_args.output_dir_path,
      &env_args.input_dir_path[(env_args
        .input_dir_path
        .rfind('/')
        .map(|id| id as isize)
        .unwrap_or(-1)
        + 1) as _..]
    ),
    size,
    if color_type == ColorType::Grayscale
      || color_type == ColorType::Rgb
      || color_type == ColorType::Rgba
    {
      color_type
    } else {
      panic!(
        "{color_type:?} is unsupported for saving the current framebuffer to an atlas PNG file!"
      )
    },
    &atlas
      .par_rchunks_exact((size.get_x() * channel_count) as _)
      .flatten()
      .map(|&data| data)
      .collect::<Vec<_>>(),
  );
}

pub(crate) fn save_png_file(file_path: &str, size: UVec2, color_type: ColorType, image: &[u8]) {
  let mut encoder = png::Encoder::new(
    BufWriter::new(File::create(file_path).unwrap()),
    size.get_x(),
    size.get_y(),
  );
  encoder.set_color(color_type);
  encoder.set_depth(BitDepth::Eight);
  encoder.set_source_gamma(ScaledFloat::from_scaled(45455));
  encoder.set_source_chromaticities(SourceChromaticities::new(
    (0.31270, 0.32900),
    (0.64000, 0.33000),
    (0.30000, 0.60000),
    (0.15000, 0.06000),
  ));
  encoder.set_compression(Compression::Fast);
  encoder.set_filter(FilterType::Paeth);
  encoder
    .write_header()
    .unwrap()
    .write_image_data(image)
    .unwrap();
}
