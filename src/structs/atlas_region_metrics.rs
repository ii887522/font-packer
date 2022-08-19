use sdl2::ttf::GlyphMetrics;
use serde::Serialize;

#[derive(Clone, Debug, Serialize)]
pub(crate) struct AtlasRegionMetrics {
  pub minx: i32,
  pub maxx: i32,
  pub miny: i32,
  pub maxy: i32,
  pub advance: i32,
}

impl From<GlyphMetrics> for AtlasRegionMetrics {
  fn from(metrics: GlyphMetrics) -> Self {
    Self {
      minx: metrics.minx,
      maxx: metrics.maxx,
      miny: metrics.miny,
      maxy: metrics.maxy,
      advance: metrics.advance,
    }
  }
}
