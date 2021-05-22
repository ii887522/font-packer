// Copyright ii887522

#include "CommandLine.h"
#include <nitro/Functions/math_ext.h>
#include <string>
#include <stdexcept>
#include <filesystem>
#include "constants.h"

using std::string;
using std::invalid_argument;
using ii887522::nitro::isUint;
using ii887522::nitro::parseUint;
using ii887522::nitro::isPowerOfTwo;
using std::filesystem::exists;

namespace ii887522::fontPacker {

CommandLine::CommandLine(int argc, char** argv) {
  if (argc != 6u) throw invalid_argument{ "There must be only 5 command line arguments!" };
  fontFilePath = argv[TTF_FILE_PATH_INDEX];
  if (!isUint(string{ argv[FONT_SIZE_INDEX] })) throw invalid_argument{ "Font size must be an unsigned integer!" };
  fontSize = static_cast<int>(parseUint(string{ argv[FONT_SIZE_INDEX] }));
  outputDirPath = argv[OUTPUT_DIRECTORY_PATH_INDEX];
  if (!(isUint(string{ argv[ATLAS_WIDTH_INDEX] }) && isUint(string{ argv[ATLAS_HEIGHT_INDEX] }))) throw invalid_argument{ "Atlas width and atlas height must be unsigned integers!" };
  atlasSize = Size{ static_cast<int>(parseUint(string{ argv[ATLAS_WIDTH_INDEX] })), static_cast<int>(parseUint(string{ argv[ATLAS_HEIGHT_INDEX] })) };
}

const string& CommandLine::getFontFilePath() const {
  return fontFilePath;
}

const string& CommandLine::getOutputDirPath() const {
  return outputDirPath;
}

void CommandLine::validate() const {
  if (!(fontFilePath.ends_with(".ttf") && exists(fontFilePath))) throw invalid_argument{ "TTF file path must exists and ends with .ttf!" };
  if (fontSize <= 0) throw invalid_argument{ "Font size must be a positive integer!" };
  if (!(outputDirPath.ends_with('/') || outputDirPath.ends_with('\\'))) throw invalid_argument{ "Output directory path must ends with either '/' or '\\'!" };
  if (!(isPowerOfTwo(atlasSize.w) && isPowerOfTwo(atlasSize.h))) throw invalid_argument{ "Atlas width and atlas height must be power of two!" };
}

}  // namespace ii887522::fontPacker
