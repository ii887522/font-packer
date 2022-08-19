use serde::Deserialize;

#[derive(Clone, Debug, Deserialize)]
pub(crate) struct Font {
  pub file_name: String,
  pub size: u16,
  pub generate_blur: Option<bool>,
}
