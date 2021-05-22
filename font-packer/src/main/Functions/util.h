// Copyright ii887522

#ifndef FONT_PACKER_SRC_MAIN_FUNCTIONS_UTIL_H_
#define FONT_PACKER_SRC_MAIN_FUNCTIONS_UTIL_H_

#include "../Struct/Glyph.h"

namespace ii887522::fontPacker {

// Param glyph: it must not be assigned to nullptr or integer
// See alsp ../Struct/Glyph.h for more details
void rotate(Glyph*const glyph);

}  // namespace ii887522::fontPacker

#endif  // FONT_PACKER_SRC_MAIN_FUNCTIONS_UTIL_H_
