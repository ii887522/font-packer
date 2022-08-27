use super::Font;
use serde::Deserialize;
use std::collections::HashMap;

#[derive(Debug, Deserialize)]
pub(crate) struct Input {
  pub fonts: HashMap<String, Font>,
}
