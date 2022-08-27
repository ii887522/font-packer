use gl::types::*;
use iron_ingot::UVec2;
use std::cell::RefCell;

#[derive(Clone, Debug)]
pub(crate) struct Glyph {
  pub font_name: String,
  pub font_size: u16,
  pub name: String,
  pub atlas_id: GLenum,
  pub atlas_size: UVec2,
  pub line_spacing: i32,
  pub advance: i32,
  pub prev_position: UVec2,
  pub position: UVec2,
  pub size: UVec2,
  pub is_rotated: bool,
}

impl Glyph {
  pub(crate) fn reset_position(&mut self) {
    self.position = self.prev_position;
  }

  pub(crate) fn reset_positions(glyphs: &[RefCell<Glyph>]) {
    for glyph in glyphs {
      glyph.borrow_mut().reset_position();
    }
  }
}
