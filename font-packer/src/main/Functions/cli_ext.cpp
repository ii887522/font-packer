// Copyright ii887522

#include "cli_ext.h"  // NOLINT(build/include_subdir)
#include <nitro/nitro.h>
#include <string>
#include "../Any/constants.h"

using std::string;
using ii887522::nitro::isUint;

namespace ii887522::fontPacker {

bool isFontSizesUint(int argc, char** argv) {
  for (auto i{ 0u }; i != argc - MIN_COMMAND_LINE_ARGS_REQUIRED; ++i) {
    if (!isUint(string{ argv[FONT_SIZES_START_INDEX + i] })) return false;
  }
  return true;
}

}  // namespace ii887522::fontPacker
