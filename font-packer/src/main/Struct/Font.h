// Copyright ii887522

#ifndef FONT_PACKER_SRC_MAIN_STRUCT_FONT_H_
#define FONT_PACKER_SRC_MAIN_STRUCT_FONT_H_

namespace ii887522::fontPacker {

struct Font final {
  int size;
  int lineSkip;

  explicit constexpr Font() { }
  explicit constexpr Font(const int size, const int lineSkip) : size{ size }, lineSkip{ lineSkip } { }
};

}  // namespace ii887522::fontPacker

#endif  // FONT_PACKER_SRC_MAIN_STRUCT_FONT_H_
