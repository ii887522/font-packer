use serde::Deserialize;

#[derive(Clone, Debug, Deserialize)]
pub(crate) struct Font {
  pub size: u16,
  pub generate_blur: Option<bool>,
}
