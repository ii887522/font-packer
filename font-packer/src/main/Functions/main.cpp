// Copyright ii887522

#ifndef TEST

#define ALLOCATOR_IMPLEMENTATIONS
#include <nitro/nitro.h>

#include <SDL.h>
#include <viewify/viewify.h>
#include <stdexcept>
#include <iostream>
#include "../Any/CommandLine.h"
#include "../ViewGroupFactory/FontPackerViewGroupFactory.h"

using ii887522::viewify::App;
using ii887522::viewify::Subsystems;
using ii887522::viewify::eventLoop;
using ii887522::viewify::Size;
using ii887522::viewify::Color;
using std::invalid_argument;
using std::cerr;

namespace ii887522::fontPacker {

static int main(int argc, char** argv) try {
  const CommandLine commandLine{ argc, argv };
  commandLine.validate();
  const Subsystems subsystems;
  FontPackerViewGroupFactory fontPackerViewGroupFactory{ commandLine.getInputDirPath(), commandLine.getOutputDirPath(), commandLine.getAtlasSize(), commandLine.getFontSizes() };
    // See also ../ViewGroupFactory/FontPackerViewGroupFactory.h for more details
  eventLoop(App{ "Font Packer", commandLine.getAtlasSize(), Color{ 0u, 0u, 0u, 0u }, &fontPackerViewGroupFactory, SDL_WINDOW_MINIMIZED });
  return EXIT_SUCCESS;
} catch (const invalid_argument&) {
  cerr << "Command Line: font-packer <input-directory-path> <output-directory-path> <atlas-width> <atlas-height> <font-sizes>\n";
  cerr << "Param <input-directory-path>: it must exists, has at least 1 ttf file and ends with either '/' or '\\'\n";
  cerr << "Param <output-directory-path>: it must ends with either '/' or '\\'\n";
  cerr << "Param <atlas-width>: it must be equal to 2^n where n is a non-negative integer, and big enough to fill glyphs\n";
  cerr << "Param <atlas-height>: it must be equal to 2^n where n is a non-negative integer, and big enough to fill glyphs\n";
  cerr << "Param <font-sizes>: it must be an array of positive integers with array size equals to the number of font files in <input-directory-path>\n";
  return EXIT_FAILURE;
}

}  // namespace ii887522::fontPacker

int main(int argc, char** argv) {
  return ii887522::fontPacker::main(argc, argv);
}

#endif
