// Copyright ii887522

#ifndef FONT_PACKER_SRC_MAIN_STRUCT_GLYPH_H_
#define FONT_PACKER_SRC_MAIN_STRUCT_GLYPH_H_

#include <viewify/viewify.h>

using ii887522::viewify::Rect;
using ii887522::viewify::Point;

namespace ii887522::fontPacker {

/// <summary>It is a single part of a texture atlas.</summary>
struct Glyph final {
  unsigned int atlasI;
  Rect<int> rect;
  int advance;
  bool isRotated;

  explicit constexpr Glyph() { }
  explicit constexpr Glyph(const unsigned int atlasI, const Rect<int>& rect, const int advance, const bool isRotated = false) : atlasI{ atlasI }, rect{ rect }, advance{ advance },
    isRotated{ isRotated } { }
};

}  // namespace ii887522::fontPacker

#endif  // FONT_PACKER_SRC_MAIN_STRUCT_GLYPH_H_
