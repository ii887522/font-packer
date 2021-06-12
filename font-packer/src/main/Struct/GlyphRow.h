// Copyright ii887522

#ifndef FONT_PACKER_SRC_MAIN_STRUCT_GLYPHROW_H_
#define FONT_PACKER_SRC_MAIN_STRUCT_GLYPHROW_H_

#include <nitro/nitro.h>

using ii887522::nitro::Range;

namespace ii887522::fontPacker {

/// <summary>See also Glyph.h for more details</summary>
struct GlyphRow final {
  Range<unsigned int> indices;
  int width;

  /// <summary>See also Glyph.h for more details</summary>
  explicit constexpr GlyphRow() { }

  /// <summary>See also Glyph.h for more details</summary>
  explicit constexpr GlyphRow(const Range<unsigned int>& indices, const int width) : indices{ indices }, width{ width } { }
};

}  // namespace ii887522::fontPacker

#endif  // FONT_PACKER_SRC_MAIN_STRUCT_GLYPHROW_H_
