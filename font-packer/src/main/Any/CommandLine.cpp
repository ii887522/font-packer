// Copyright ii887522

#include "CommandLine.h"
#include <nitro/nitro.h>
#include <string>
#include <stdexcept>
#include <filesystem>
#include <vector>
#include "constants.h"  // NOLINT(build/include_subdir)
#include "../Functions/cli_ext.h"

using std::string;
using std::invalid_argument;
using ii887522::nitro::isUint;
using ii887522::nitro::parseUint;
using ii887522::nitro::isPowerOfTwo;
using ii887522::nitro::hasFileWithExtension;
using std::filesystem::exists;
using std::filesystem::directory_iterator;
using std::vector;
using std::to_string;

namespace ii887522::fontPacker {

CommandLine::CommandLine(int argc, char** argv) {
  if (argc < MIN_COMMAND_LINE_ARGS_REQUIRED) throw invalid_argument{ "There must be at least " + to_string(MIN_COMMAND_LINE_ARGS_REQUIRED) + " command line arguments!" };
  inputDirPath = argv[INPUT_DIRECTORY_PATH_INDEX];
  outputDirPath = argv[OUTPUT_DIRECTORY_PATH_INDEX];
  if (!(isUint(string{ argv[ATLAS_WIDTH_INDEX] }) && isUint(string{ argv[ATLAS_HEIGHT_INDEX] }))) throw invalid_argument{ "Atlas width and atlas height must be unsigned integers!" };
  atlasSize = Size{ static_cast<int>(parseUint(string{ argv[ATLAS_WIDTH_INDEX] })), static_cast<int>(parseUint(string{ argv[ATLAS_HEIGHT_INDEX] })) };
  if (!isFontSizesUint(argc, argv)) throw invalid_argument{ "All font sizes must be unsigned integers!" };
  addFontSizes(argc, argv);
}

void CommandLine::addFontSizes(int argc, char** argv) {
  for (auto i{ 0u }; i != argc - MIN_COMMAND_LINE_ARGS_REQUIRED; ++i) fontSizes.push_back(static_cast<int>(parseUint(string{ argv[FONT_SIZES_START_INDEX + i] })));
}

bool CommandLine::isAllFontSizesPositive() const {
  for (const auto fontSize : fontSizes) {
    if (fontSize < 1) return false;
  }
  return true;
}

unsigned int CommandLine::getInputDirTTFFileCount() const {
  auto result{ 0u };
  for (const auto& entry : directory_iterator{ inputDirPath }) {
    if (entry.path().string().ends_with(LOWER_CASE_FONT_EXTENSION_NAME) || entry.path().string().ends_with(UPPER_CASE_FONT_EXTENSION_NAME)) ++result;
  }
  return result;
}

const string& CommandLine::getInputDirPath() const {
  return inputDirPath;
}

const string& CommandLine::getOutputDirPath() const {
  return outputDirPath;
}

const vector<int>& CommandLine::getFontSizes() const {
  return fontSizes;
}

void CommandLine::validate() const {
  if (!((inputDirPath.ends_with('/') || inputDirPath.ends_with('\\')) && exists(inputDirPath) && (hasFileWithExtension(inputDirPath, LOWER_CASE_FONT_EXTENSION_NAME) ||
    hasFileWithExtension(inputDirPath, UPPER_CASE_FONT_EXTENSION_NAME)))) throw invalid_argument{ "Input directory path must exist and ends with either '/' or '\\'!" };
  if (!(outputDirPath.ends_with('/') || outputDirPath.ends_with('\\'))) throw invalid_argument{ "Output directory path must ends with either '/' or '\\'!" };
  if (!(isPowerOfTwo(atlasSize.w) && isPowerOfTwo(atlasSize.h))) throw invalid_argument{ "Atlas width and atlas height must be power of two!" };
  if (fontSizes.size() != getInputDirTTFFileCount()) throw invalid_argument{ "Number of font sizes must be the same as the number of font files in the input directory!" };
  if (!isAllFontSizesPositive()) throw invalid_argument{ "All font sizes must be positive integers!" };
}

}  // namespace ii887522::fontPacker
