// Copyright ii887522

#ifdef TEST

#include <viewify/viewify.h>
#include <catch.hpp>
#include "../../main/Functions/util.h"

using ii887522::viewify::Rect;
using ii887522::viewify::Point;
using ii887522::viewify::Size;

namespace ii887522::fontPacker {

TEST_CASE("test rotate() function") {
  {
    Glyph glyph{ 0u, Rect{ Point{ 0, 0 }, Size{ 1, 1 } }, Rect{ Point{ 0, 0 }, Size{ 1, 1 } }, 1, false };
    rotate(&glyph);
    REQUIRE(glyph.atlasI == 0u);
    REQUIRE(glyph.imageRect.position.x == 0);
    REQUIRE(glyph.imageRect.position.y == 0);
    REQUIRE(glyph.imageRect.size.w == 1);
    REQUIRE(glyph.imageRect.size.h == 1);
    REQUIRE(glyph.rect.position.x == 0);
    REQUIRE(glyph.rect.position.y == 0);
    REQUIRE(glyph.rect.size.w == 1);
    REQUIRE(glyph.rect.size.h == 1);
    REQUIRE(glyph.advance == 1);
    REQUIRE(glyph.isRotated);
  }
  {
    Glyph glyph{ 1u, Rect{ Point{ 0, 0 }, Size{ 1, 1 } }, Rect{ Point{ 0, 0 }, Size{ 1, 1 } }, 1, false };
    rotate(&glyph);
    REQUIRE(glyph.atlasI == 1u);
    REQUIRE(glyph.imageRect.position.x == 0);
    REQUIRE(glyph.imageRect.position.y == 0);
    REQUIRE(glyph.imageRect.size.w == 1);
    REQUIRE(glyph.imageRect.size.h == 1);
    REQUIRE(glyph.rect.position.x == 0);
    REQUIRE(glyph.rect.position.y == 0);
    REQUIRE(glyph.rect.size.w == 1);
    REQUIRE(glyph.rect.size.h == 1);
    REQUIRE(glyph.advance == 1);
    REQUIRE(glyph.isRotated);
  }
  {
    Glyph glyph{ 1u, Rect{ Point{ 1, 0 }, Size{ 1, 1 } }, Rect{ Point{ 0, 0 }, Size{ 1, 1 } }, 1, false };
    rotate(&glyph);
    REQUIRE(glyph.atlasI == 1u);
    REQUIRE(glyph.imageRect.position.x == 1);
    REQUIRE(glyph.imageRect.position.y == 0);
    REQUIRE(glyph.imageRect.size.w == 1);
    REQUIRE(glyph.imageRect.size.h == 1);
    REQUIRE(glyph.rect.position.x == 0);
    REQUIRE(glyph.rect.position.y == 0);
    REQUIRE(glyph.rect.size.w == 1);
    REQUIRE(glyph.rect.size.h == 1);
    REQUIRE(glyph.advance == 1);
    REQUIRE(glyph.isRotated);
  }
  {
    Glyph glyph{ 1u, Rect{ Point{ 1, 1 }, Size{ 1, 1 } }, Rect{ Point{ 0, 0 }, Size{ 1, 1 } }, 1, false };
    rotate(&glyph);
    REQUIRE(glyph.atlasI == 1u);
    REQUIRE(glyph.imageRect.position.x == 1);
    REQUIRE(glyph.imageRect.position.y == 1);
    REQUIRE(glyph.imageRect.size.w == 1);
    REQUIRE(glyph.imageRect.size.h == 1);
    REQUIRE(glyph.rect.position.x == 0);
    REQUIRE(glyph.rect.position.y == 0);
    REQUIRE(glyph.rect.size.w == 1);
    REQUIRE(glyph.rect.size.h == 1);
    REQUIRE(glyph.advance == 1);
    REQUIRE(glyph.isRotated);
  }
  {
    Glyph glyph{ 1u, Rect{ Point{ 1, 1 }, Size{ 2, 1 } }, Rect{ Point{ 0, 0 }, Size{ 1, 1 } }, 1, false };
    rotate(&glyph);
    REQUIRE(glyph.atlasI == 1u);
    REQUIRE(glyph.imageRect.position.x == 1);
    REQUIRE(glyph.imageRect.position.y == 1);
    REQUIRE(glyph.imageRect.size.w == 1);
    REQUIRE(glyph.imageRect.size.h == 2);
    REQUIRE(glyph.rect.position.x == 0);
    REQUIRE(glyph.rect.position.y == 0);
    REQUIRE(glyph.rect.size.w == 1);
    REQUIRE(glyph.rect.size.h == 1);
    REQUIRE(glyph.advance == 1);
    REQUIRE(glyph.isRotated);
  }
  {
    Glyph glyph{ 1u, Rect{ Point{ 1, 1 }, Size{ 1, 2 } }, Rect{ Point{ 0, 0 }, Size{ 1, 1 } }, 1, false };
    rotate(&glyph);
    REQUIRE(glyph.atlasI == 1u);
    REQUIRE(glyph.imageRect.position.x == 1);
    REQUIRE(glyph.imageRect.position.y == 1);
    REQUIRE(glyph.imageRect.size.w == 2);
    REQUIRE(glyph.imageRect.size.h == 1);
    REQUIRE(glyph.rect.position.x == 0);
    REQUIRE(glyph.rect.position.y == 0);
    REQUIRE(glyph.rect.size.w == 1);
    REQUIRE(glyph.rect.size.h == 1);
    REQUIRE(glyph.advance == 1);
    REQUIRE(glyph.isRotated);
  }
  {
    Glyph glyph{ 1u, Rect{ Point{ 1, 1 }, Size{ 2, 2 } }, Rect{ Point{ 0, 0 }, Size{ 1, 1 } }, 1, false };
    rotate(&glyph);
    REQUIRE(glyph.atlasI == 1u);
    REQUIRE(glyph.imageRect.position.x == 1);
    REQUIRE(glyph.imageRect.position.y == 1);
    REQUIRE(glyph.imageRect.size.w == 2);
    REQUIRE(glyph.imageRect.size.h == 2);
    REQUIRE(glyph.rect.position.x == 0);
    REQUIRE(glyph.rect.position.y == 0);
    REQUIRE(glyph.rect.size.w == 1);
    REQUIRE(glyph.rect.size.h == 1);
    REQUIRE(glyph.advance == 1);
    REQUIRE(glyph.isRotated);
  }
  {
    Glyph glyph{ 1u, Rect{ Point{ 1, 1 }, Size{ 2, 2 } }, Rect{ Point{ 1, 0 }, Size{ 1, 1 } }, 1, false };
    rotate(&glyph);
    REQUIRE(glyph.atlasI == 1u);
    REQUIRE(glyph.imageRect.position.x == 1);
    REQUIRE(glyph.imageRect.position.y == 1);
    REQUIRE(glyph.imageRect.size.w == 2);
    REQUIRE(glyph.imageRect.size.h == 2);
    REQUIRE(glyph.rect.position.x == 1);
    REQUIRE(glyph.rect.position.y == 0);
    REQUIRE(glyph.rect.size.w == 1);
    REQUIRE(glyph.rect.size.h == 1);
    REQUIRE(glyph.advance == 1);
    REQUIRE(glyph.isRotated);
  }
  {
    Glyph glyph{ 1u, Rect{ Point{ 1, 1 }, Size{ 2, 2 } }, Rect{ Point{ 1, 1 }, Size{ 1, 1 } }, 1, false };
    rotate(&glyph);
    REQUIRE(glyph.atlasI == 1u);
    REQUIRE(glyph.imageRect.position.x == 1);
    REQUIRE(glyph.imageRect.position.y == 1);
    REQUIRE(glyph.imageRect.size.w == 2);
    REQUIRE(glyph.imageRect.size.h == 2);
    REQUIRE(glyph.rect.position.x == 1);
    REQUIRE(glyph.rect.position.y == 1);
    REQUIRE(glyph.rect.size.w == 1);
    REQUIRE(glyph.rect.size.h == 1);
    REQUIRE(glyph.advance == 1);
    REQUIRE(glyph.isRotated);
  }
  {
    Glyph glyph{ 1u, Rect{ Point{ 1, 1 }, Size{ 2, 2 } }, Rect{ Point{ 1, 1 }, Size{ 2, 1 } }, 1, false };
    rotate(&glyph);
    REQUIRE(glyph.atlasI == 1u);
    REQUIRE(glyph.imageRect.position.x == 1);
    REQUIRE(glyph.imageRect.position.y == 1);
    REQUIRE(glyph.imageRect.size.w == 2);
    REQUIRE(glyph.imageRect.size.h == 2);
    REQUIRE(glyph.rect.position.x == 1);
    REQUIRE(glyph.rect.position.y == 1);
    REQUIRE(glyph.rect.size.w == 2);
    REQUIRE(glyph.rect.size.h == 1);
    REQUIRE(glyph.advance == 1);
    REQUIRE(glyph.isRotated);
  }
  {
    Glyph glyph{ 1u, Rect{ Point{ 1, 1 }, Size{ 2, 2 } }, Rect{ Point{ 1, 1 }, Size{ 2, 2 } }, 1, false };
    rotate(&glyph);
    REQUIRE(glyph.atlasI == 1u);
    REQUIRE(glyph.imageRect.position.x == 1);
    REQUIRE(glyph.imageRect.position.y == 1);
    REQUIRE(glyph.imageRect.size.w == 2);
    REQUIRE(glyph.imageRect.size.h == 2);
    REQUIRE(glyph.rect.position.x == 1);
    REQUIRE(glyph.rect.position.y == 1);
    REQUIRE(glyph.rect.size.w == 2);
    REQUIRE(glyph.rect.size.h == 2);
    REQUIRE(glyph.advance == 1);
    REQUIRE(glyph.isRotated);
  }
  {
    Glyph glyph{ 1u, Rect{ Point{ 1, 1 }, Size{ 2, 2 } }, Rect{ Point{ 1, 1 }, Size{ 2, 2 } }, 2, false };
    rotate(&glyph);
    REQUIRE(glyph.atlasI == 1u);
    REQUIRE(glyph.imageRect.position.x == 1);
    REQUIRE(glyph.imageRect.position.y == 1);
    REQUIRE(glyph.imageRect.size.w == 2);
    REQUIRE(glyph.imageRect.size.h == 2);
    REQUIRE(glyph.rect.position.x == 1);
    REQUIRE(glyph.rect.position.y == 1);
    REQUIRE(glyph.rect.size.w == 2);
    REQUIRE(glyph.rect.size.h == 2);
    REQUIRE(glyph.advance == 2);
    REQUIRE(glyph.isRotated);
  }
  {
    Glyph glyph{ 1u, Rect{ Point{ 1, 1 }, Size{ 2, 2 } }, Rect{ Point{ 1, 1 }, Size{ 2, 2 } }, 2, false };
    rotate(&glyph);
    REQUIRE(glyph.atlasI == 1u);
    REQUIRE(glyph.imageRect.position.x == 1);
    REQUIRE(glyph.imageRect.position.y == 1);
    REQUIRE(glyph.imageRect.size.w == 2);
    REQUIRE(glyph.imageRect.size.h == 2);
    REQUIRE(glyph.rect.position.x == 1);
    REQUIRE(glyph.rect.position.y == 1);
    REQUIRE(glyph.rect.size.w == 2);
    REQUIRE(glyph.rect.size.h == 2);
    REQUIRE(glyph.advance == 2);
    REQUIRE(glyph.isRotated);
  }
  {
    Glyph glyph{ 1u, Rect{ Point{ 1, 1 }, Size{ 2, 2 } }, Rect{ Point{ 1, 1 }, Size{ 2, 2 } }, 2, true };
    rotate(&glyph);
    REQUIRE(glyph.atlasI == 1u);
    REQUIRE(glyph.imageRect.position.x == 1);
    REQUIRE(glyph.imageRect.position.y == 1);
    REQUIRE(glyph.imageRect.size.w == 2);
    REQUIRE(glyph.imageRect.size.h == 2);
    REQUIRE(glyph.rect.position.x == 1);
    REQUIRE(glyph.rect.position.y == 1);
    REQUIRE(glyph.rect.size.w == 2);
    REQUIRE(glyph.rect.size.h == 2);
    REQUIRE(glyph.advance == 2);
    REQUIRE(!glyph.isRotated);
  }
}

}  // namespace ii887522::fontPacker

#endif
