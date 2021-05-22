// Copyright ii887522

#include "util.h"  // NOLINT(build/include_subdir)
#include <nitro/Functions/util.h>
#include "../Struct/Glyph.h"

using ii887522::nitro::swap;

namespace ii887522::fontPacker {

void rotate(Glyph*const glyph) {
  swap(glyph->imageRect.size.w, glyph->imageRect.size.h);  // NOLINT(build/include_what_you_use)
  glyph->isRotated = !glyph->isRotated;
}

}  // namespace ii887522::fontPacker
