use super::Font;
use serde::Deserialize;

#[derive(Debug, Deserialize)]
pub(crate) struct Input {
  pub fonts: Vec<Font>,
}
