// Copyright ii887522

#ifdef TEST

#include "util.test.h"  // NOLINT(build/include_subdir)
#include <viewify/Struct/Rect.h>
#include <viewify/Struct/Point.h>
#include <viewify/Struct/Size.h>
#include <cassert>
#include "../../main/Functions/util.h"

using ii887522::viewify::Rect;
using ii887522::viewify::Point;
using ii887522::viewify::Size;

namespace ii887522::fontPacker {

static void testRotate() {
  {
    Glyph glyph{ 0u, Rect{ Point{ 0, 0 }, Size{ 1, 1 } }, Rect{ Point{ 0, 0 }, Size{ 1, 1 } }, 1, 'a', false };
    rotate(&glyph);
    assert(glyph.atlasIndex == 0u);
    assert(glyph.imageRect.position.x == 0);
    assert(glyph.imageRect.position.y == 0);
    assert(glyph.imageRect.size.w == 1);
    assert(glyph.imageRect.size.h == 1);
    assert(glyph.rect.position.x == 0);
    assert(glyph.rect.position.y == 0);
    assert(glyph.rect.size.w == 1);
    assert(glyph.rect.size.h == 1);
    assert(glyph.advance == 1);
    assert(glyph.ch == 'a');
    assert(glyph.isRotated);
  }
  {
    Glyph glyph{ 1u, Rect{ Point{ 0, 0 }, Size{ 1, 1 } }, Rect{ Point{ 0, 0 }, Size{ 1, 1 } }, 1, 'a', false };
    rotate(&glyph);
    assert(glyph.atlasIndex == 1u);
    assert(glyph.imageRect.position.x == 0);
    assert(glyph.imageRect.position.y == 0);
    assert(glyph.imageRect.size.w == 1);
    assert(glyph.imageRect.size.h == 1);
    assert(glyph.rect.position.x == 0);
    assert(glyph.rect.position.y == 0);
    assert(glyph.rect.size.w == 1);
    assert(glyph.rect.size.h == 1);
    assert(glyph.advance == 1);
    assert(glyph.ch == 'a');
    assert(glyph.isRotated);
  }
  {
    Glyph glyph{ 1u, Rect{ Point{ 1, 0 }, Size{ 1, 1 } }, Rect{ Point{ 0, 0 }, Size{ 1, 1 } }, 1, 'a', false };
    rotate(&glyph);
    assert(glyph.atlasIndex == 1u);
    assert(glyph.imageRect.position.x == 1);
    assert(glyph.imageRect.position.y == 0);
    assert(glyph.imageRect.size.w == 1);
    assert(glyph.imageRect.size.h == 1);
    assert(glyph.rect.position.x == 0);
    assert(glyph.rect.position.y == 0);
    assert(glyph.rect.size.w == 1);
    assert(glyph.rect.size.h == 1);
    assert(glyph.advance == 1);
    assert(glyph.ch == 'a');
    assert(glyph.isRotated);
  }
  {
    Glyph glyph{ 1u, Rect{ Point{ 1, 1 }, Size{ 1, 1 } }, Rect{ Point{ 0, 0 }, Size{ 1, 1 } }, 1, 'a', false };
    rotate(&glyph);
    assert(glyph.atlasIndex == 1u);
    assert(glyph.imageRect.position.x == 1);
    assert(glyph.imageRect.position.y == 1);
    assert(glyph.imageRect.size.w == 1);
    assert(glyph.imageRect.size.h == 1);
    assert(glyph.rect.position.x == 0);
    assert(glyph.rect.position.y == 0);
    assert(glyph.rect.size.w == 1);
    assert(glyph.rect.size.h == 1);
    assert(glyph.advance == 1);
    assert(glyph.ch == 'a');
    assert(glyph.isRotated);
  }
  {
    Glyph glyph{ 1u, Rect{ Point{ 1, 1 }, Size{ 2, 1 } }, Rect{ Point{ 0, 0 }, Size{ 1, 1 } }, 1, 'a', false };
    rotate(&glyph);
    assert(glyph.atlasIndex == 1u);
    assert(glyph.imageRect.position.x == 1);
    assert(glyph.imageRect.position.y == 1);
    assert(glyph.imageRect.size.w == 1);
    assert(glyph.imageRect.size.h == 2);
    assert(glyph.rect.position.x == 0);
    assert(glyph.rect.position.y == 0);
    assert(glyph.rect.size.w == 1);
    assert(glyph.rect.size.h == 1);
    assert(glyph.advance == 1);
    assert(glyph.ch == 'a');
    assert(glyph.isRotated);
  }
  {
    Glyph glyph{ 1u, Rect{ Point{ 1, 1 }, Size{ 1, 2 } }, Rect{ Point{ 0, 0 }, Size{ 1, 1 } }, 1, 'a', false };
    rotate(&glyph);
    assert(glyph.atlasIndex == 1u);
    assert(glyph.imageRect.position.x == 1);
    assert(glyph.imageRect.position.y == 1);
    assert(glyph.imageRect.size.w == 2);
    assert(glyph.imageRect.size.h == 1);
    assert(glyph.rect.position.x == 0);
    assert(glyph.rect.position.y == 0);
    assert(glyph.rect.size.w == 1);
    assert(glyph.rect.size.h == 1);
    assert(glyph.advance == 1);
    assert(glyph.ch == 'a');
    assert(glyph.isRotated);
  }
  {
    Glyph glyph{ 1u, Rect{ Point{ 1, 1 }, Size{ 2, 2 } }, Rect{ Point{ 0, 0 }, Size{ 1, 1 } }, 1, 'a', false };
    rotate(&glyph);
    assert(glyph.atlasIndex == 1u);
    assert(glyph.imageRect.position.x == 1);
    assert(glyph.imageRect.position.y == 1);
    assert(glyph.imageRect.size.w == 2);
    assert(glyph.imageRect.size.h == 2);
    assert(glyph.rect.position.x == 0);
    assert(glyph.rect.position.y == 0);
    assert(glyph.rect.size.w == 1);
    assert(glyph.rect.size.h == 1);
    assert(glyph.advance == 1);
    assert(glyph.ch == 'a');
    assert(glyph.isRotated);
  }
  {
    Glyph glyph{ 1u, Rect{ Point{ 1, 1 }, Size{ 2, 2 } }, Rect{ Point{ 1, 0 }, Size{ 1, 1 } }, 1, 'a', false };
    rotate(&glyph);
    assert(glyph.atlasIndex == 1u);
    assert(glyph.imageRect.position.x == 1);
    assert(glyph.imageRect.position.y == 1);
    assert(glyph.imageRect.size.w == 2);
    assert(glyph.imageRect.size.h == 2);
    assert(glyph.rect.position.x == 1);
    assert(glyph.rect.position.y == 0);
    assert(glyph.rect.size.w == 1);
    assert(glyph.rect.size.h == 1);
    assert(glyph.advance == 1);
    assert(glyph.ch == 'a');
    assert(glyph.isRotated);
  }
  {
    Glyph glyph{ 1u, Rect{ Point{ 1, 1 }, Size{ 2, 2 } }, Rect{ Point{ 1, 1 }, Size{ 1, 1 } }, 1, 'a', false };
    rotate(&glyph);
    assert(glyph.atlasIndex == 1u);
    assert(glyph.imageRect.position.x == 1);
    assert(glyph.imageRect.position.y == 1);
    assert(glyph.imageRect.size.w == 2);
    assert(glyph.imageRect.size.h == 2);
    assert(glyph.rect.position.x == 1);
    assert(glyph.rect.position.y == 1);
    assert(glyph.rect.size.w == 1);
    assert(glyph.rect.size.h == 1);
    assert(glyph.advance == 1);
    assert(glyph.ch == 'a');
    assert(glyph.isRotated);
  }
  {
    Glyph glyph{ 1u, Rect{ Point{ 1, 1 }, Size{ 2, 2 } }, Rect{ Point{ 1, 1 }, Size{ 2, 1 } }, 1, 'a', false };
    rotate(&glyph);
    assert(glyph.atlasIndex == 1u);
    assert(glyph.imageRect.position.x == 1);
    assert(glyph.imageRect.position.y == 1);
    assert(glyph.imageRect.size.w == 2);
    assert(glyph.imageRect.size.h == 2);
    assert(glyph.rect.position.x == 1);
    assert(glyph.rect.position.y == 1);
    assert(glyph.rect.size.w == 2);
    assert(glyph.rect.size.h == 1);
    assert(glyph.advance == 1);
    assert(glyph.ch == 'a');
    assert(glyph.isRotated);
  }
  {
    Glyph glyph{ 1u, Rect{ Point{ 1, 1 }, Size{ 2, 2 } }, Rect{ Point{ 1, 1 }, Size{ 2, 2 } }, 1, 'a', false };
    rotate(&glyph);
    assert(glyph.atlasIndex == 1u);
    assert(glyph.imageRect.position.x == 1);
    assert(glyph.imageRect.position.y == 1);
    assert(glyph.imageRect.size.w == 2);
    assert(glyph.imageRect.size.h == 2);
    assert(glyph.rect.position.x == 1);
    assert(glyph.rect.position.y == 1);
    assert(glyph.rect.size.w == 2);
    assert(glyph.rect.size.h == 2);
    assert(glyph.advance == 1);
    assert(glyph.ch == 'a');
    assert(glyph.isRotated);
  }
  {
    Glyph glyph{ 1u, Rect{ Point{ 1, 1 }, Size{ 2, 2 } }, Rect{ Point{ 1, 1 }, Size{ 2, 2 } }, 2, 'a', false };
    rotate(&glyph);
    assert(glyph.atlasIndex == 1u);
    assert(glyph.imageRect.position.x == 1);
    assert(glyph.imageRect.position.y == 1);
    assert(glyph.imageRect.size.w == 2);
    assert(glyph.imageRect.size.h == 2);
    assert(glyph.rect.position.x == 1);
    assert(glyph.rect.position.y == 1);
    assert(glyph.rect.size.w == 2);
    assert(glyph.rect.size.h == 2);
    assert(glyph.advance == 2);
    assert(glyph.ch == 'a');
    assert(glyph.isRotated);
  }
  {
    Glyph glyph{ 1u, Rect{ Point{ 1, 1 }, Size{ 2, 2 } }, Rect{ Point{ 1, 1 }, Size{ 2, 2 } }, 2, 'b', false };
    rotate(&glyph);
    assert(glyph.atlasIndex == 1u);
    assert(glyph.imageRect.position.x == 1);
    assert(glyph.imageRect.position.y == 1);
    assert(glyph.imageRect.size.w == 2);
    assert(glyph.imageRect.size.h == 2);
    assert(glyph.rect.position.x == 1);
    assert(glyph.rect.position.y == 1);
    assert(glyph.rect.size.w == 2);
    assert(glyph.rect.size.h == 2);
    assert(glyph.advance == 2);
    assert(glyph.ch == 'b');
    assert(glyph.isRotated);
  }
  {
    Glyph glyph{ 1u, Rect{ Point{ 1, 1 }, Size{ 2, 2 } }, Rect{ Point{ 1, 1 }, Size{ 2, 2 } }, 2, 'b', true };
    rotate(&glyph);
    assert(glyph.atlasIndex == 1u);
    assert(glyph.imageRect.position.x == 1);
    assert(glyph.imageRect.position.y == 1);
    assert(glyph.imageRect.size.w == 2);
    assert(glyph.imageRect.size.h == 2);
    assert(glyph.rect.position.x == 1);
    assert(glyph.rect.position.y == 1);
    assert(glyph.rect.size.w == 2);
    assert(glyph.rect.size.h == 2);
    assert(glyph.advance == 2);
    assert(glyph.ch == 'b');
    assert(!glyph.isRotated);
  }
}

void testUtil() {
  testRotate();
}

}  // namespace ii887522::fontPacker

#endif
