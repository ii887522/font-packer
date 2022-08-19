#[cfg(windows)]
use winres::WindowsResource;

#[cfg(windows)]
fn main() {
  let mut res = WindowsResource::new();
  res.set_icon("res/favicon.ico");
  res.compile().unwrap();
  println!("cargo:rerun-if-changed=res/favicon.ico");
}

#[cfg(unix)]
fn main() {}
