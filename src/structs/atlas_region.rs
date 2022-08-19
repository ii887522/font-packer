use super::{AtlasRegionMetrics, Glyph};
use serde::Serialize;

#[derive(Clone, Debug, Serialize)]
pub(crate) struct AtlasRegion {
  pub ch: char,
  pub atlas_width: u32,
  pub atlas_height: u32,
  pub line_spacing: i32,
  pub x: u32,
  pub y: u32,
  pub w: u32,
  pub h: u32,
  pub is_rotated: bool,
  pub metrics: AtlasRegionMetrics,
}

impl From<Glyph> for AtlasRegion {
  fn from(glyph: Glyph) -> Self {
    Self {
      ch: glyph.ch,
      atlas_width: glyph.atlas_size.get_x(),
      atlas_height: glyph.atlas_size.get_y(),
      line_spacing: glyph.line_spacing,
      x: glyph.position.get_x(),
      y: glyph.position.get_y(),
      w: glyph.size.get_x(),
      h: glyph.size.get_y(),
      is_rotated: glyph.is_rotated,
      metrics: glyph.metrics.into(),
    }
  }
}
