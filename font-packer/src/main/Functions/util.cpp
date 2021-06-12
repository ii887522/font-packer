// Copyright ii887522

#include "util.h"  // NOLINT(build/include_subdir)
#include <nitro/nitro.h>
#include <string>
#include <filesystem>
#include <vector>
#include "../Struct/Glyph.h"
#include "../Any/constants.h"

using ii887522::nitro::swap;
using ii887522::nitro::getFileName;
using ii887522::nitro::toUpperCase;
using ii887522::nitro::write;
using std::string;
using std::filesystem::directory_iterator;
using std::vector;

namespace ii887522::fontPacker {

string getFontNameEnumFileContent(const string& inputDirPath) {
  string content{
R"(// Copyright ii887522

#ifndef FONT_PACKER_SRC_MAIN_ANY_FONT_NAME_H_
#define FONT_PACKER_SRC_MAIN_ANY_FONT_NAME_H_

namespace ii887522::fontPacker {

enum class FontName : unsigned int {
)"
  };
  for (const auto& entry : directory_iterator{ inputDirPath }) {
    if (!(entry.path().string().ends_with(LOWER_CASE_FONT_EXTENSION_NAME) || entry.path().string().ends_with(UPPER_CASE_FONT_EXTENSION_NAME))) continue;
    auto fontName{ getFileName(entry.path().string()) };
    toUpperCase(&fontName);
    content += "\t_" + fontName + ",\n";
  }
  return content +
R"(};

}  // namespace ii887522::fontPacker

#endif  // FONT_PACKER_SRC_MAIN_ANY_FONT_NAME_H_
)";
}

void writeFontNameEnumFile(const string& inputDirPath, const string& outputDirPath) {
  const auto content{ getFontNameEnumFileContent(inputDirPath) };
  write<char, vector>(outputDirPath + "FontName.h", vector(content.begin(), content.end()));
}

void rotate(Glyph*const glyph) {
  swap(glyph->imageRect.size.w, glyph->imageRect.size.h);  // NOLINT(build/include_what_you_use)
  glyph->isRotated = !glyph->isRotated;
}

}  // namespace ii887522::fontPacker
