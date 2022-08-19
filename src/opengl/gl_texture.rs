use crate::funcs::util::flip_vertically;
use gl::types::*;
use iron_ingot::UVec2;
use sdl2::{pixels::PixelFormatEnum, surface::Surface};
use std::fmt::{self, Debug, Formatter};

pub(crate) enum ImgAttr {
  Surface(Surface<'static>),
  Size(UVec2),
}

pub(crate) struct Arg {
  pub img_attr: ImgAttr,
  pub tex_unit: GLuint,
  pub min_filter: GLenum,
  pub mag_filter: GLenum,
  pub wrap_s: GLenum,
  pub wrap_t: GLenum,
  pub internal_format: GLenum,
}

impl Debug for Arg {
  fn fmt(&self, formatter: &mut Formatter<'_>) -> fmt::Result {
    formatter
      .debug_struct("Arg")
      .field("tex_unit", &self.tex_unit)
      .field("min_filter", &self.min_filter)
      .field("mag_filter", &self.mag_filter)
      .field("wrap_s", &self.wrap_s)
      .field("wrap_t", &self.wrap_t)
      .field("internal_format", &self.internal_format)
      .finish_non_exhaustive()
  }
}

pub(crate) struct GLTexture {
  id: GLuint,
  img_attr: ImgAttr,
  tex_unit: GLuint,
  min_filter: GLenum,
  mag_filter: GLenum,
  wrap_s: GLenum,
  wrap_t: GLenum,
  internal_format: GLenum,
  size: UVec2,
  is_opaque: bool,
}

impl Debug for GLTexture {
  fn fmt(&self, formatter: &mut Formatter<'_>) -> fmt::Result {
    formatter
      .debug_struct("GLTexture")
      .field("id", &self.id)
      .field("tex_unit", &self.tex_unit)
      .field("min_filter", &self.min_filter)
      .field("mag_filter", &self.mag_filter)
      .field("wrap_s", &self.wrap_s)
      .field("wrap_t", &self.wrap_t)
      .field("internal_format", &self.internal_format)
      .field("size", &self.size)
      .field("is_opaque", &self.is_opaque)
      .finish_non_exhaustive()
  }
}

impl GLTexture {
  pub(crate) fn new(arg: Arg) -> Self {
    let Arg {
      img_attr,
      tex_unit,
      min_filter,
      mag_filter,
      wrap_s,
      wrap_t,
      internal_format,
    } = arg;
    if let ImgAttr::Size(size) = img_attr {
      debug_assert!(
        size.get_x() >= 1,
        "Width must be greater than or equal to 1!"
      );
      debug_assert!(
        size.get_y() >= 1,
        "Height must be greater than or equal to 1!"
      );
    }
    Self {
      id: 0,
      img_attr,
      tex_unit,
      min_filter,
      mag_filter,
      wrap_s,
      wrap_t,
      internal_format,
      size: UVec2::new(()),
      is_opaque: false,
    }
  }

  pub(crate) const fn get_id(&self) -> GLuint {
    self.id
  }

  pub(crate) const fn get_size(&self) -> UVec2 {
    self.size
  }

  pub(crate) fn init(&mut self) {
    unsafe {
      gl::CreateTextures(gl::TEXTURE_2D, 1, &mut self.id);
      gl::BindTextureUnit(self.tex_unit, self.id);
      gl::TextureParameteri(self.id, gl::TEXTURE_MIN_FILTER, self.min_filter as _);
      gl::TextureParameteri(self.id, gl::TEXTURE_MAG_FILTER, self.mag_filter as _);
      gl::TextureParameteri(self.id, gl::TEXTURE_WRAP_S, self.wrap_s as _);
      gl::TextureParameteri(self.id, gl::TEXTURE_WRAP_T, self.wrap_t as _);
      gl::TextureParameterfv(
        self.id,
        gl::TEXTURE_BORDER_COLOR,
        &[1.0f32, 1.0f32, 1.0f32, 1.0f32] as *const _,
      );
      match &self.img_attr {
        ImgAttr::Surface(surface) => {
          let img = surface.convert_format(PixelFormatEnum::RGBA8888).unwrap();
          self.size = UVec2::new((img.width(), img.height()));
          gl::TextureStorage2D(
            self.id,
            1,
            self.internal_format,
            img.width() as _,
            img.height() as _,
          );
          let pitch = img.pitch();
          let width = img.width();
          let height = img.height();
          let pixels = img.without_lock().unwrap();
          gl::TextureSubImage2D(
            self.id,
            0,
            0,
            0,
            width as _,
            height as _,
            gl::RGBA,
            gl::UNSIGNED_BYTE,
            &*flip_vertically(pixels, pitch) as *const _ as *const _,
          );
        }
        &ImgAttr::Size(size) => {
          self.size = size;
          gl::TextureStorage2D(
            self.id,
            1,
            self.internal_format,
            size.get_x() as _,
            size.get_y() as _,
          )
        }
      }
    }
  }

  pub(crate) fn grow(&mut self) {
    if let ImgAttr::Size(size) = self.img_attr {
      self.img_attr = ImgAttr::Size(if size.get_x() == size.get_y() {
        UVec2::new((self.size.get_x() << 1, self.size.get_y()))
      } else {
        UVec2::new((self.size.get_x(), self.size.get_y() << 1))
      });
      unsafe {
        gl::DeleteTextures(1, &self.id);
      }
      self.init();
    }
  }
}

impl Drop for GLTexture {
  fn drop(&mut self) {
    unsafe {
      gl::DeleteTextures(1, &self.id);
    }
  }
}
