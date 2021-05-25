// Copyright ii887522

#ifndef FONT_PACKER_SRC_MAIN_FUNCTIONS_UTIL_H_
#define FONT_PACKER_SRC_MAIN_FUNCTIONS_UTIL_H_

#include "../Struct/Glyph.h"
#include <string>

using std::string;

namespace ii887522::fontPacker {

// Param inputDirPath: it must exists and ends with either '/' or '\\'
string getFontNameEnumFileContent(const string& inputDirPath);

// Param inputDirPath: it must exists and ends with either '/' or '\\'
// Param outputDirPath: it must ends with either '/' or '\\'
void writeFontNameEnumFile(const string& inputDirPath, const string& outputDirPath);

// Param glyph: it must not be assigned to nullptr or integer
// See alsp ../Struct/Glyph.h for more details
void rotate(Glyph*const glyph);

}  // namespace ii887522::fontPacker

#endif  // FONT_PACKER_SRC_MAIN_FUNCTIONS_UTIL_H_
