mod any;
mod funcs;
mod opengl;
mod structs;

use iron_ingot::UVec2;
use opengl::GLApp;

fn main() {
  GLApp::new("Font Packer", UVec2::new((1600, 900))).start();
}
