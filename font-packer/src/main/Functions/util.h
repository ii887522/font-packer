// Copyright ii887522

#ifndef FONT_PACKER_SRC_MAIN_FUNCTIONS_UTIL_H_
#define FONT_PACKER_SRC_MAIN_FUNCTIONS_UTIL_H_

#include <string>
#include "../Struct/Glyph.h"

using std::string;

namespace ii887522::fontPacker {

/// <param name="inputDirPath">It must exists and ends with either '/' or '\\'</param>
string getFontNameEnumFileContent(const string& inputDirPath);

/// <param name="inputDirPath">It must exists and ends with either '/' or '\\'</param>
/// <param name="outputDirPath">It must ends with either '/' or '\\'</param>
void writeFontNameEnumFile(const string& inputDirPath, const string& outputDirPath);

/// <summary>See alsp ../Struct/Glyph.h for more details</summary>
/// <param name="glyph">It must not be assigned to nullptr or integer</param>
void rotate(Glyph*const glyph);

}  // namespace ii887522::fontPacker

#endif  // FONT_PACKER_SRC_MAIN_FUNCTIONS_UTIL_H_
