// Copyright ii887522

#ifndef FONT_PACKER_SRC_MAIN_STRUCT_KERNING_H_
#define FONT_PACKER_SRC_MAIN_STRUCT_KERNING_H_

namespace ii887522::fontPacker {

// It is the process of adjusting the glyph position to reduce spaces between characters to produce a nice looking text.
// See also Glyph.h for more details
struct Kerning final {
  int size;
  char prevCh;
  char nextCh;

  explicit constexpr Kerning() { }
  explicit constexpr Kerning(const int size, const char prevCh, const char nextCh) : size{ size }, prevCh{ prevCh }, nextCh{ nextCh } { }
};

}  // namespace ii887522::fontPacker

#endif  // FONT_PACKER_SRC_MAIN_STRUCT_KERNING_H_
