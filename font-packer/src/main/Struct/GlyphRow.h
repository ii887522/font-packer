// Copyright ii887522

#ifndef FONT_PACKER_SRC_MAIN_STRUCT_GLYPH_ROW_H_
#define FONT_PACKER_SRC_MAIN_STRUCT_GLYPH_ROW_H_

#include <nitro/Struct/Range.h>

using ii887522::nitro::Range;

namespace ii887522::fontPacker {

// See also Glyph.h for more details
struct GlyphRow final {
  Range<unsigned int> indices;
  int width;

  // See also Glyph.h for more details
  explicit constexpr GlyphRow() { }

  // See also Glyph.h for more details
  explicit constexpr GlyphRow(const Range<unsigned int>& indices, const int width) : indices{ indices }, width{ width } { }
};

}  // namespace ii887522::fontPacker

#endif  // FONT_PACKER_SRC_MAIN_STRUCT_GLYPH_ROW_H_
