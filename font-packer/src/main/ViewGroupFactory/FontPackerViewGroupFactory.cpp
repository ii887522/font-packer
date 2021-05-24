// Copyright ii887522

#ifndef TEST

#include "FontPackerViewGroupFactory.h"
#include <viewify/Factory/ViewGroupFactory.h>
#include <viewify/View/ViewGroup.h>
#include <viewify/Struct/Size.h>
#include <viewify/Struct/Point.h>
#include <viewify/Any/View.h>
#include <viewify/Any/Enums.h>
#include <viewify/Struct/Rect.h>
#include <viewify/View/Image.h>
#include <nitro/Functions/fs_ext.h>
#include <nitro/Struct/Range.h>
#include <viewify/Functions/math_ext.h>
#include <nitro/Functions/util.h>
#include <viewify/Functions/sdl_ext.h>
#include <nitro/Functions/string_ext.h>
#include <viewify/Functions/ttf_ext.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <vector>
#include "../Struct/Kerning.h"
#include "../Functions/util.h"
#include "../Struct/GlyphRow.h"

using ii887522::viewify::ViewGroup;
using ii887522::viewify::Size;
using ii887522::viewify::Point;
using ii887522::viewify::View;
using ii887522::viewify::Action;
using ii887522::viewify::Rotation;
using ii887522::viewify::Align;
using ii887522::viewify::Rect;
using ii887522::viewify::Image;
using ii887522::viewify::distanceSqr;
using ii887522::viewify::snapshot;
using ii887522::viewify::getGlyphMetrics;
using ii887522::nitro::emptyDir;
using ii887522::nitro::Range;
using ii887522::nitro::isOverlapX;
using ii887522::nitro::sort;
using ii887522::nitro::getFileName;
using ii887522::nitro::write;
using std::string;
using std::vector;
using std::to_string;

namespace ii887522::fontPacker {

FontPackerViewGroupFactory::FontPackerViewGroupFactory(const string& inputDirPath, const string& outputDirPath, const Size<int>& atlasSize, const vector<int>& fontSizes) :
  ViewGroupFactory{ }, atlas{ nullptr }, fontFilePath{ fontFilePath }, fontSize{ fontSize }, outputDirPath{ outputDirPath }, font{ TTF_OpenFont(fontFilePath.c_str(), fontSize) },
  glyphImageRects{ Rect{ Point{ 0.f, 0.f }, static_cast<Size<float>>(atlasSize) } }, currentPendingIndices{ &lPendingIndices }, nextPendingIndices{ &rPendingIndices }, gap{ 0 },
  indicesI{ 0u }, atlasIndex{ 0u } {
  emptyDir(outputDirPath);
  addImages();
  rotateImagesToMakeThemLonger();
  sort<unsigned int, vector>(&indices, [this](const unsigned int& l, const unsigned int& r) {  // NOLINT(build/include_what_you_use)
    return glyphs[l].imageRect.size.h < glyphs[r].imageRect.size.h;
  });
}

void FontPackerViewGroupFactory::addImages() {
  for (char ch{ 32 }; ch != 127; ++ch) addImage(ch, ch - 32);
}

void FontPackerViewGroupFactory::addImage(const char ch, const unsigned int index) {
  surfaces.push_back(TTF_RenderGlyph_Blended(font, ch, SDL_Color{ 255u, 255u, 255u, 255u }));
  const auto glyphMetrics{ getGlyphMetrics(font, ch) };
  glyphs.push_back(
    Glyph{
      0u, Rect{ Point{ 0, 0 }, Size{ surfaces.back()->w, surfaces.back()->h } }, Rect{
        Point{ glyphMetrics.box.xRange.min, TTF_FontAscent(font) - glyphMetrics.box.yRange.max },
        Size{ glyphMetrics.box.xRange.max - glyphMetrics.box.xRange.min, glyphMetrics.box.yRange.max - glyphMetrics.box.yRange.min }
      }, glyphMetrics.advance, ch
    });
  addKernings(ch);
  indices.push_back(index);
}

void FontPackerViewGroupFactory::addKernings(const char prevCh) {
  for (char nextCh{ 32 }; nextCh != 127; ++nextCh) kernings.push_back(Kerning{ TTF_GetFontKerningSizeGlyphs(font, prevCh, nextCh), prevCh, nextCh });
}

void FontPackerViewGroupFactory::rotateImagesToMakeThemLonger() {
  for (auto& glyph : glyphs) {
    if (glyph.imageRect.size.w < glyph.imageRect.size.h) rotate(&glyph);
  }
}

void FontPackerViewGroupFactory::rotateSomeImages(const vector<unsigned int>& pendingIndices, const function<bool(const unsigned int, const unsigned int)>& compare) {
  for (const auto i : pendingIndices) {
    if (compare(glyphs[indices[i]].imageRect.size.w, glyphs[indices[i]].imageRect.size.h)) rotate(&glyphs[indices[i]]);
  }
}

void FontPackerViewGroupFactory::linearlyLayOutGlyphs(const Size<int>& atlasSize) {
  Point<int> position{ gap, gap };
  auto rowH{ 0 };
  auto canReadRowH{ true };
  auto rowFirstGlyphI{ indicesI };
  for (; indicesI != indices.size(); ++indicesI) {
    if (position.x + glyphs[indices[indicesI]].imageRect.size.w + gap > atlasSize.w) {
      position.x = gap;
      position.y += rowH + gap;
      if (position.y + glyphs[indices[indicesI]].imageRect.size.h + gap > atlasSize.h) break;
      glyphRows.push_back(GlyphRow{ Range{ rowFirstGlyphI, indicesI - 1u }, glyphs[indices[indicesI - 1u]].imageRect.position.x + glyphs[indices[indicesI - 1u]].imageRect.size.w });
      rowFirstGlyphI = indicesI;
      canReadRowH = true;
    }
    if (canReadRowH) {
      rowH = glyphs[indices[indicesI]].imageRect.size.h;
      canReadRowH = false;
    }
    glyphs[indices[indicesI]].atlasIndex = atlasIndex;
    glyphs[indices[indicesI]].imageRect.position.x = position.x;
    position.x += glyphs[indices[indicesI]].imageRect.size.w + gap;
  }
  glyphRows.push_back(GlyphRow{ Range{ rowFirstGlyphI, indicesI - 1u }, glyphs[indices[indicesI - 1u]].imageRect.position.x + glyphs[indices[indicesI - 1u]].imageRect.size.w });
}

void FontPackerViewGroupFactory::pushUpGlyphs() {
  auto y{ gap };
  for (auto i{ glyphRows.front().indices.min }; i <= glyphRows.front().indices.max; ++i) {
    glyphs[indices[i]].imageRect.position.y = gap;
    glyphImageRects.add(static_cast<Rect<float>>(glyphs[indices[i]].imageRect));
  }
  y += glyphs[indices[glyphRows.front().indices.min]].imageRect.size.h + gap;
  for (auto i{ 1u }; i != glyphRows.size(); ++i) {
    auto aboveGlyphI{ glyphRows[i - 1u].indices.min };
    for (auto j{ glyphRows[i].indices.min }; j <= glyphRows[i].indices.max; ++j) {
      while (
        !isOverlapX(
          glyphs[indices[j]].imageRect.position.x,
          Range{ glyphs[indices[aboveGlyphI]].imageRect.position.x, glyphs[indices[aboveGlyphI]].imageRect.position.x + glyphs[indices[aboveGlyphI]].imageRect.size.w + gap }))
        ++aboveGlyphI;
      glyphs[indices[j]].imageRect.position.y = glyphs[indices[aboveGlyphI]].imageRect.position.y + glyphs[indices[aboveGlyphI]].imageRect.size.h + gap;
      glyphImageRects.add(static_cast<Rect<float>>(glyphs[indices[j]].imageRect));
    }
    y += glyphs[indices[glyphRows[i].indices.min]].imageRect.size.h + gap;
  }
}

void FontPackerViewGroupFactory::addImageViewsFromGlyphRows(ViewGroup*const self, SDL_Renderer*const renderer) {
  for (auto i{ 0u }; i != glyphRows.size(); ++i) {
    for (auto j{ glyphRows[i].indices.min }; j <= glyphRows[i].indices.max; ++j) {
      self->add(
        Image::Builder{ renderer, surfaces[indices[j]], glyphs[indices[j]].imageRect.position, Align::LEFT, glyphs[indices[j]].isRotated ? Rotation::QUARTER_CLOCKWISE : Rotation::NONE }
          .setA(255u)
          .setDuration(1u)
          .build());
    }
  }
}

unsigned int FontPackerViewGroupFactory::getNearestGlyphRowToAtlasBottomRightCornerI(const Size<int>& atlasSize) const {
  auto lastDistanceSqr{ INT_MAX };
  auto glyphRowsI{ static_cast<int>(glyphRows.size() - 1u) };
  for (; glyphRowsI >= 0; --glyphRowsI) {
    const auto nowDistanceSqr{
      distanceSqr(
        Point{
          glyphs[indices[glyphRows[glyphRowsI].indices.max]].imageRect.position.x + glyphs[indices[glyphRows[glyphRowsI].indices.max]].imageRect.size.w - 1,
          glyphs[indices[glyphRows[glyphRowsI].indices.max]].imageRect.position.y + glyphs[indices[glyphRows[glyphRowsI].indices.max]].imageRect.size.h - 1
        }, Point{ atlasSize.w, atlasSize.h }
      )
    };
    if (nowDistanceSqr < lastDistanceSqr) lastDistanceSqr = nowDistanceSqr;
    else
      break;
  }
  return glyphRowsI + 1u;
}

Action FontPackerViewGroupFactory::linearlyFillAtlasBottom(ViewGroup*const self, SDL_Renderer*const renderer, const Size<int>& atlasSize, const unsigned int glyphRowsI) {
  Point<int> position{ atlasSize.w - 1 - gap, atlasSize.h - 1 - gap };
  auto rowH{ 0 };
  auto canSetRowH{ true };
  bool canGoToNextRow;
  currentPendingIndices->resize(indices.size() - indicesI);
  for (auto i{ 0u }; i != currentPendingIndices->size(); ++i) (*currentPendingIndices)[i] = indicesI + i;
  do {
    canGoToNextRow = false;
    for (const auto i : *currentPendingIndices) {
      if (
        position.x - glyphs[indices[i]].imageRect.size.w - gap < -1 || glyphImageRects.isAnyRectHit(
          Rect{
            Point{ position.x - glyphs[indices[i]].imageRect.size.w + 1.f - gap, position.y - glyphs[indices[i]].imageRect.size.h + 1.f - gap },
            Size{ static_cast<float>(glyphs[indices[i]].imageRect.size.w + gap), static_cast<float>(glyphs[indices[i]].imageRect.size.h + gap) }
          }) || position.y - glyphs[indices[i]].imageRect.size.h - gap <
        glyphs[indices[glyphRows[glyphRowsI].indices.max]].imageRect.position.y + glyphs[indices[glyphRows[glyphRowsI].indices.max]].imageRect.size.h - 1
      ) {
        nextPendingIndices->push_back(i);
      } else {
        if (canSetRowH) {
          rowH = glyphs[indices[i]].imageRect.size.h;
          canSetRowH = false;
        }
        glyphs[indices[i]].atlasIndex = atlasIndex;
        glyphs[indices[i]].imageRect.position = Point{ position.x - glyphs[indices[i]].imageRect.size.w + 1, position.y - glyphs[indices[i]].imageRect.size.h + 1 };
        self->add(
          Image::Builder{ renderer, surfaces[indices[i]], glyphs[indices[i]].imageRect.position, Align::LEFT, glyphs[indices[i]].isRotated ? Rotation::QUARTER_CLOCKWISE : Rotation::NONE }
            .setA(255u)
            .setDuration(1u)
            .build());
        position.x -= glyphs[indices[i]].imageRect.size.w + gap;
        canGoToNextRow = true;
      }
    }
    position.x = atlasSize.w - 1 - gap;
    position.y -= rowH + gap;
    canSetRowH = true;
    currentPendingIndices->clear();
    ii887522::nitro::swap(currentPendingIndices, nextPendingIndices);
    if (currentPendingIndices->empty()) {
      indicesI = static_cast<unsigned int>(indices.size());
      return Action::RETURN_FROM_CALLER;
    }
  } while (canGoToNextRow);
  return Action::NONE;
}

Action FontPackerViewGroupFactory::linearlyFillAtlasRight(ViewGroup*const self, SDL_Renderer*const renderer, const Size<int>& atlasSize, const unsigned int glyphRowsI) {
  Point<int> position{
    atlasSize.w - 1 - gap, glyphs[indices[glyphRows[glyphRowsI].indices.max]].imageRect.position.y + glyphs[indices[glyphRows[glyphRowsI].indices.max]].imageRect.size.h - 1
  };
  auto colW{ 0 };
  auto canSetColW{ true };
  bool canGoToNextCol;
  do {
    canGoToNextCol = false;
    for (const auto i : *currentPendingIndices) {
      if (
        position.y - glyphs[indices[i]].imageRect.size.h - gap < -1 || glyphImageRects.isAnyRectHit(
          Rect{
            Point{ position.x - glyphs[indices[i]].imageRect.size.w + 1.f - gap, position.y - glyphs[indices[i]].imageRect.size.h + 1.f - gap },
            Size{ static_cast<float>(glyphs[indices[i]].imageRect.size.w + gap), static_cast<float>(glyphs[indices[i]].imageRect.size.h + gap) }
          })) {
        nextPendingIndices->push_back(i);
      } else {
        if (canSetColW) {
          colW = glyphs[indices[i]].imageRect.size.w;
          canSetColW = false;
        }
        glyphs[indices[i]].atlasIndex = atlasIndex;
        glyphs[indices[i]].imageRect.position = Point{ position.x - glyphs[indices[i]].imageRect.size.w + 1, position.y - glyphs[indices[i]].imageRect.size.h + 1 };
        self->add(
          Image::Builder{ renderer, surfaces[indices[i]], glyphs[indices[i]].imageRect.position, Align::LEFT, glyphs[indices[i]].isRotated ? Rotation::QUARTER_CLOCKWISE : Rotation::NONE }
            .setA(255u)
            .setDuration(1u)
            .build());
        position.y -= glyphs[indices[i]].imageRect.size.h + gap;
        canGoToNextCol = true;
      }
    }
    position.x -= colW + gap;
    position.y = glyphs[indices[glyphRows[glyphRowsI].indices.max]].imageRect.position.y + glyphs[indices[glyphRows[glyphRowsI].indices.max]].imageRect.size.h - 1;
    canSetColW = true;
    currentPendingIndices->clear();
    ii887522::nitro::swap(currentPendingIndices, nextPendingIndices);  // NOLINT(build/include_what_you_use)
    if (currentPendingIndices->empty()) {
      indicesI = static_cast<unsigned int>(indices.size());
      return Action::RETURN_FROM_CALLER;
    }
  } while (canGoToNextCol);
  return Action::NONE;
}

vector<unsigned int> FontPackerViewGroupFactory::getIndicesReferencedByPendingIndices() const {
  vector<unsigned int> result(currentPendingIndices->size());
  for (auto i{ 0u }; i != currentPendingIndices->size(); ++i) result[i] = indices[(*currentPendingIndices)[i]];
  return result;
}

void FontPackerViewGroupFactory::prepareForNextAtlas() {
  auto aux{ getIndicesReferencedByPendingIndices() };
  sort<unsigned int, vector>(&aux, [this](const unsigned int l, const unsigned int r) {
    return glyphs[l].imageRect.size.h < glyphs[r].imageRect.size.h;
  });
  indices.resize(aux.size());
  memcpy(indices.data(), aux.data(), aux.size() * sizeof(unsigned int));
  indicesI = 0u;
}

Action FontPackerViewGroupFactory::fillLShape(ViewGroup*const self, SDL_Renderer*const renderer, const Size<int>& atlasSize) {
  const auto glyphRowsI{ getNearestGlyphRowToAtlasBottomRightCornerI(atlasSize) };
  if (linearlyFillAtlasBottom(self, renderer, atlasSize, glyphRowsI) == Action::RETURN_FROM_CALLER) return Action::RETURN_FROM_CALLER;
  rotateSomeImages(*currentPendingIndices, [](const unsigned int w, const unsigned int h) {
    return w > h;
  });
  sort<unsigned int, vector>(currentPendingIndices, [this](const unsigned int& l, const unsigned int& r) {
    return glyphs[indices[l]].imageRect.size.w < glyphs[indices[r]].imageRect.size.w;
  });
  if (linearlyFillAtlasRight(self, renderer, atlasSize, glyphRowsI) == Action::RETURN_FROM_CALLER) return Action::RETURN_FROM_CALLER;
  rotateSomeImages(*currentPendingIndices, [](const unsigned int w, const unsigned int h) {
    return w < h;
  });
  return Action::NONE;
}

ViewGroup FontPackerViewGroupFactory::make(SDL_Renderer*const renderer, const Size<int>& size) {
  atlas = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, size.w, size.h);
  SDL_SetRenderTarget(renderer, atlas);
  return ViewGroup{ renderer, Point{ 0, 0 }, [](ViewGroup&, SDL_Renderer*const) {
    return vector<View*>{ };
  }, [this, renderer, size](ViewGroup& self) {
    linearlyLayOutGlyphs(size);
    sort<GlyphRow, vector>(&glyphRows, [](const GlyphRow& l, const GlyphRow& r) {  // NOLINT(build/include_what_you_use)
      return l.width < r.width;
    });
    pushUpGlyphs();
    addImageViewsFromGlyphRows(&self, renderer);
    if (indicesI == indices.size()) return Action::NONE;
    if (fillLShape(&self, renderer, size) == Action::RETURN_FROM_CALLER) return Action::NONE;
    prepareForNextAtlas();
    return Action::NONE;
  }, [this, renderer, size](ViewGroup& self) {
    snapshot(renderer, Rect{ Point{ 0, 0 }, size }, outputDirPath + getFileName(fontFilePath) + "_" + to_string(fontSize) + "_" + to_string(atlasIndex) + ".png");
    self.clear();
    glyphRows.clear();
    glyphImageRects.clear();
    ++atlasIndex;
    return indicesI == indices.size() ? Action::QUIT : Action::NONE;
  } };
}

FontPackerViewGroupFactory::~FontPackerViewGroupFactory() {
  write<Glyph, vector>(outputDirPath + getFileName(fontFilePath) + "_" + to_string(fontSize) + "_glyphs.dat", glyphs);
  write<Kerning, vector>(outputDirPath + getFileName(fontFilePath) + "_" + to_string(fontSize) + "_kernings.dat", kernings);
  TTF_CloseFont(font);
  SDL_DestroyTexture(atlas);
}

}  // namespace ii887522::fontPacker

#endif
