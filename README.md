# font-packer
[![Semantic Versioning 2.0.0](https://img.shields.io/badge/semver-2.0.0-standard.svg)](https://semver.org/)
[![Linux](https://svgshare.com/i/Zhy.svg)](https://svgshare.com/i/Zhy.svg)
[![Windows](https://svgshare.com/i/ZhY.svg)](https://svgshare.com/i/ZhY.svg)
[![made-with-rust](https://img.shields.io/badge/Made%20with-Rust-1f425f.svg)](https://www.rust-lang.org/)
[![MIT license](https://img.shields.io/badge/License-MIT-blue.svg)](https://lbesson.mit-license.org/)

![Sample font atlas](docs/atlas.png)

A CLI tool used to generate glyph atlases for graphics applications such as GUI, video games and so on to improve performance of these applications.

## Table of contents
- [Usage](https://github.com/ii887522/font-packer#prerequisites)
- [Prerequisites](https://github.com/ii887522/font-packer#prerequisites)
- [Format the project](https://github.com/ii887522/font-packer#format-the-project)
- [Automatically format the project on change](https://github.com/ii887522/font-packer#automatically-format-the-project-on-change)
- [Lint the project](https://github.com/ii887522/font-packer#lint-the-project)
- [Automatically lint the project on change](https://github.com/ii887522/font-packer#automatically-lint-the-project-on-change)
- [Build the vcpkg dependencies in the project](https://github.com/ii887522/font-packer#build-the-vcpkg-dependencies-in-the-project)
- [Build the project](https://github.com/ii887522/font-packer#build-the-project)
- [Automatically build the project on change](https://github.com/ii887522/font-packer#automatically-build-the-project-on-change)
- [Test the project](https://github.com/ii887522/font-packer#test-the-project)
- [Automatically test the project on change](https://github.com/ii887522/font-packer#automatically-test-the-project-on-change)
- [Run the project](https://github.com/ii887522/font-packer#run-the-project)

## Usage
```
font-packer <input-dir-path> <output-dir-path>
```
`input-dir-path` is an input directory path where the directory is located contains a list of TTF font files and a `input.toml` file that contains a list of TOML tables called `fonts`. Each TOML table in `fonts` must include a variable called `file_name` which is a relative path to TTF font file, a variable called `size` that specify font size in pts, and optionally contains a variable called `generate_blur` which is a boolean that specify whether to generate blur glyphs for the associated font.

`output-dir-path` is an output directory path where the directory is located contains a generated font atlas file and a glyph reference file in TOML format. Each glyph reference inside the TOML file points to a small area of the texture atlas. That small area is actually an image (rotated or not) which comes from the input directory.

## Prerequisites
- Windows 11 or Linux
- [Visual Studio Code](https://code.visualstudio.com/) with plugins:
  - Better TOML
  - CodeLLDB
  - EditorConfig for VS Code
  - GLSL Lint
  - Markdown All in One
  - rust-analyzer
  - Shader languages support for VS Code
  - YAML
- [Rust 1.61.0](https://www.rust-lang.org/) and later
- [rustfmt 1.4.38](https://github.com/rust-lang/rustfmt) and later
- [clippy 0.1.60](https://github.com/rust-lang/rust-clippy) and later
- [cargo-watch 8.1.1](https://github.com/watchexec/cargo-watch) and later
- [cargo-vcpkg 0.1.6](https://crates.io/crates/cargo-vcpkg) and later

## Format the project
```sh
cargo fmt
```

## Automatically format the project on change
```sh
cargo watch -x fmt
```

## Lint the project
```sh
cargo clippy --all-features
```

## Automatically lint the project on change
```sh
cargo watch -x "clippy --all-features"
```

## Build vcpkg dependencies in the project
```sh
cargo vcpkg build
```

## Build the project
```sh
cargo build
```

## Automatically build the project on change
```sh
cargo watch -x build
```

## Test the project
```sh
cargo test
```

## Automatically test the project on change
```sh
cargo watch -x test
```

## Run the project
```sh
cargo run
```
