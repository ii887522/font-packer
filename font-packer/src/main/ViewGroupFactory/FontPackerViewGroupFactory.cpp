// Copyright ii887522

#ifndef TEST

#include "FontPackerViewGroupFactory.h"
#include <viewify/viewify.h>
#include <nitro/nitro.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <vector>
#include <filesystem>
#include <stdexcept>
#include <functional>
#include "../Functions/util.h"
#include "../Struct/GlyphRow.h"
#include "../Any/constants.h"
#include "../Struct/Font.h"

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
using std::filesystem::directory_iterator;
using std::invalid_argument;
using std::function;

namespace ii887522::fontPacker {

FontPackerViewGroupFactory::FontPackerViewGroupFactory(const string& inputDirPath, const string& outputDirPath, const Size<int>& atlasSize, const vector<int>& fontSizes) :
  ViewGroupFactory{ }, atlas{ nullptr }, outputDirPath{ outputDirPath }, glyphImageRects{ Rect{ Point{ 0.f, 0.f }, static_cast<Size<float>>(atlasSize) } },
  currentPendingIndices{ &lPendingIndices }, nextPendingIndices{ &rPendingIndices }, indicesI{ 0u }, atlasI{ 0u } {
  emptyDir(outputDirPath);
  addFonts(inputDirPath, fontSizes);
  addFontMetadatas(fontSizes);
  addHasKernings();
  addImages(atlasSize);
  addKerningSizes();
  writeFontNameEnumFile(inputDirPath, outputDirPath);
  rotateImagesToMakeThemLonger();
  sort<unsigned int, vector>(&indices, [this](const unsigned int& l, const unsigned int& r) {  // NOLINT(build/include_what_you_use)
    return glyphs[l].rect.size.h < glyphs[r].rect.size.h;
  });
}

void FontPackerViewGroupFactory::addFonts(const string& inputDirPath, const vector<int>& fontSizes) {
  auto i{ 0u };
  for (const auto& entry : directory_iterator{ inputDirPath }) {
    if (!(entry.path().string().ends_with(LOWER_CASE_FONT_EXTENSION_NAME) || entry.path().string().ends_with(UPPER_CASE_FONT_EXTENSION_NAME))) continue;
    fonts.push_back(TTF_OpenFont(entry.path().string().c_str(), fontSizes[i]));
    ++i;
  }
}

void FontPackerViewGroupFactory::addFontMetadatas(const vector<int>& fontSizes) {
  auto i{ 0u };
  for (const auto font : fonts) {
    fontMetadatas.push_back(Font{ fontSizes[i], TTF_FontLineSkip(font) });
    ++i;
  }
}

void FontPackerViewGroupFactory::addHasKernings() {
  hasKernings.resize(fonts.size());
  for (auto i{ 0u }; i != hasKernings.size(); ++i) hasKernings[i] = false;
}

void FontPackerViewGroupFactory::addImages(const Size<int>& atlasSize) {
  auto i{ 0u };
  for (auto j{ 0u }; j != fonts.size(); ++j) {
    for (char ch{ static_cast<char>(CHAR_RANGE.min) }; ch <= static_cast<char>(CHAR_RANGE.max); ++ch) {
      addImage(j, ch, i, atlasSize);
      ++i;
    }
  }
}

void FontPackerViewGroupFactory::addImage(const unsigned int fontsI, const char ch, const unsigned int i, const Size<int>& atlasSize) {
  surfaces.push_back(TTF_RenderGlyph_Blended(fonts[fontsI], ch, SDL_Color{ 255u, 255u, 255u, 255u }));
  if (
    atlasSize.w < surfaces.back()->w + (GAP << 1u)  /* which means atlasSize.w < surfaces.back()->w + GAP * 2 */ ||
    atlasSize.h < surfaces.back()->h + (GAP << 1u)  /* which means atlasSize.h < surfaces.back()->h + GAP * 2 */) {
    closeFonts();
    throw invalid_argument{ "Atlas size must be big enough to fill a glyph!" };
  }
  glyphs.push_back(Glyph{ 0u, Rect{ Point{ 0, 0 }, Size{ surfaces.back()->w, surfaces.back()->h } }, getGlyphMetrics(fonts[fontsI], ch).advance });
  indices.push_back(i);
}

void FontPackerViewGroupFactory::addKerningSizes() {
  kerningSizes.resize(fonts.size());
  for (auto i{ 0u }; i != fonts.size(); ++i) {
    for (char prevCh{ static_cast<char>(CHAR_RANGE.min) }; prevCh <= static_cast<char>(CHAR_RANGE.max); ++prevCh) {
      for (char nextCh{ static_cast<char>(CHAR_RANGE.min) }; nextCh <= static_cast<char>(CHAR_RANGE.max); ++nextCh) {
        const auto kerningSize{ TTF_GetFontKerningSizeGlyphs(fonts[i], prevCh, nextCh) };
        if (kerningSize != 0) hasKernings[i] = true;
        kerningSizes[i].push_back(kerningSize);
      }
    }
  }
}

void FontPackerViewGroupFactory::rotateImagesToMakeThemLonger() {
  for (auto& glyph : glyphs) {
    if (glyph.rect.size.w < glyph.rect.size.h) rotate(&glyph);
  }
}

void FontPackerViewGroupFactory::rotateSomeImages(const vector<unsigned int>& pendingIndices, const function<bool(const unsigned int w, const unsigned int h)>& compare) {
  for (const auto i : pendingIndices) {
    if (compare(glyphs[indices[i]].rect.size.w, glyphs[indices[i]].rect.size.h)) rotate(&glyphs[indices[i]]);
  }
}

void FontPackerViewGroupFactory::linearlyLayOutGlyphs(const Size<int>& atlasSize) {
  Point<int> position{ GAP, GAP };
  auto rowH{ 0 };
  auto canReadRowH{ true };
  auto rowFirstGlyphI{ indicesI };
  for (; indicesI != indices.size(); ++indicesI) {
    if (position.x + glyphs[indices[indicesI]].rect.size.w + GAP > atlasSize.w) {
      position.x = GAP;
      position.y += rowH + GAP;
      if (position.y + glyphs[indices[indicesI]].rect.size.h + GAP > atlasSize.h) break;
      glyphRows.push_back(GlyphRow{ Range{ rowFirstGlyphI, indicesI - 1u }, glyphs[indices[indicesI - 1u]].rect.position.x + glyphs[indices[indicesI - 1u]].rect.size.w });
      rowFirstGlyphI = indicesI;
      canReadRowH = true;
    }
    if (canReadRowH) {
      rowH = glyphs[indices[indicesI]].rect.size.h;
      canReadRowH = false;
    }
    glyphs[indices[indicesI]].atlasI = atlasI;
    glyphs[indices[indicesI]].rect.position.x = position.x;
    position.x += glyphs[indices[indicesI]].rect.size.w + GAP;
  }
  glyphRows.push_back(GlyphRow{ Range{ rowFirstGlyphI, indicesI - 1u }, glyphs[indices[indicesI - 1u]].rect.position.x + glyphs[indices[indicesI - 1u]].rect.size.w });
}

void FontPackerViewGroupFactory::pushUpGlyphs() {
  auto y{ GAP };
  for (auto i{ glyphRows.front().indices.min }; i <= glyphRows.front().indices.max; ++i) {
    glyphs[indices[i]].rect.position.y = GAP;
    glyphImageRects.add(static_cast<Rect<float>>(glyphs[indices[i]].rect));
  }
  y += glyphs[indices[glyphRows.front().indices.min]].rect.size.h + GAP;
  for (auto i{ 1u }; i != glyphRows.size(); ++i) {
    auto aboveGlyphI{ glyphRows[i - 1u].indices.min };
    for (auto j{ glyphRows[i].indices.min }; j <= glyphRows[i].indices.max; ++j) {
      while (
        !isOverlapX(
          glyphs[indices[j]].rect.position.x,
          Range{ glyphs[indices[aboveGlyphI]].rect.position.x, glyphs[indices[aboveGlyphI]].rect.position.x + glyphs[indices[aboveGlyphI]].rect.size.w + GAP }))
        ++aboveGlyphI;
      glyphs[indices[j]].rect.position.y = glyphs[indices[aboveGlyphI]].rect.position.y + glyphs[indices[aboveGlyphI]].rect.size.h + GAP;
      glyphImageRects.add(static_cast<Rect<float>>(glyphs[indices[j]].rect));
    }
    y += glyphs[indices[glyphRows[i].indices.min]].rect.size.h + GAP;
  }
}

void FontPackerViewGroupFactory::addImageViewsFromGlyphRows(ViewGroup*const self, SDL_Renderer*const renderer) {
  for (auto i{ 0u }; i != glyphRows.size(); ++i) {
    for (auto j{ glyphRows[i].indices.min }; j <= glyphRows[i].indices.max; ++j) {
      self->add(
        Image::Builder{ renderer, surfaces[indices[j]], glyphs[indices[j]].rect.position, Align::LEFT, glyphs[indices[j]].isRotated ? Rotation::QUARTER_CLOCKWISE : Rotation::NONE }
          .setA(255u)
          .setDuration(1u)  // See also ii887522::viewify::Image::Builder::setDuration(const unsigned int) for more details
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
          glyphs[indices[glyphRows[glyphRowsI].indices.max]].rect.position.x + glyphs[indices[glyphRows[glyphRowsI].indices.max]].rect.size.w - 1,
          glyphs[indices[glyphRows[glyphRowsI].indices.max]].rect.position.y + glyphs[indices[glyphRows[glyphRowsI].indices.max]].rect.size.h - 1
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
  Point<int> position{ atlasSize.w - 1 - GAP, atlasSize.h - 1 - GAP };
  auto rowH{ 0 };
  auto canSetRowH{ true };
  bool canGoToNextRow;
  currentPendingIndices->resize(indices.size() - indicesI);
  for (auto i{ 0u }; i != currentPendingIndices->size(); ++i) (*currentPendingIndices)[i] = indicesI + i;
  do {
    canGoToNextRow = false;
    for (const auto i : *currentPendingIndices) {
      if (
        position.x - glyphs[indices[i]].rect.size.w - GAP < -1 || glyphImageRects.isAnyRectHit(
          Rect{
            Point{ position.x - glyphs[indices[i]].rect.size.w + 1.f - GAP, position.y - glyphs[indices[i]].rect.size.h + 1.f - GAP },
            Size{ static_cast<float>(glyphs[indices[i]].rect.size.w + GAP), static_cast<float>(glyphs[indices[i]].rect.size.h + GAP) }
          }) || position.y - glyphs[indices[i]].rect.size.h - GAP <
        glyphs[indices[glyphRows[glyphRowsI].indices.max]].rect.position.y + glyphs[indices[glyphRows[glyphRowsI].indices.max]].rect.size.h - 1
      ) {
        nextPendingIndices->push_back(i);
      } else {
        if (canSetRowH) {
          rowH = glyphs[indices[i]].rect.size.h;
          canSetRowH = false;
        }
        glyphs[indices[i]].atlasI = atlasI;
        glyphs[indices[i]].rect.position = Point{ position.x - glyphs[indices[i]].rect.size.w + 1, position.y - glyphs[indices[i]].rect.size.h + 1 };
        self->add(
          Image::Builder{ renderer, surfaces[indices[i]], glyphs[indices[i]].rect.position, Align::LEFT, glyphs[indices[i]].isRotated ? Rotation::QUARTER_CLOCKWISE : Rotation::NONE }
            .setA(255u)
            .setDuration(1u)  // See also ii887522::viewify::Image::Builder::setDuration(const unsigned int) for more details
            .build());
        position.x -= glyphs[indices[i]].rect.size.w + GAP;
        canGoToNextRow = true;
      }
    }
    position.x = atlasSize.w - 1 - GAP;
    position.y -= rowH + GAP;
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
    atlasSize.w - 1 - GAP, glyphs[indices[glyphRows[glyphRowsI].indices.max]].rect.position.y + glyphs[indices[glyphRows[glyphRowsI].indices.max]].rect.size.h - 1
  };
  auto colW{ 0 };
  auto canSetColW{ true };
  bool canGoToNextCol;
  do {
    canGoToNextCol = false;
    for (const auto i : *currentPendingIndices) {
      if (
        position.y - glyphs[indices[i]].rect.size.h - GAP < -1 || glyphImageRects.isAnyRectHit(
          Rect{
            Point{ position.x - glyphs[indices[i]].rect.size.w + 1.f - GAP, position.y - glyphs[indices[i]].rect.size.h + 1.f - GAP },
            Size{ static_cast<float>(glyphs[indices[i]].rect.size.w + GAP), static_cast<float>(glyphs[indices[i]].rect.size.h + GAP) }
          })) {
        nextPendingIndices->push_back(i);
      } else {
        if (canSetColW) {
          colW = glyphs[indices[i]].rect.size.w;
          canSetColW = false;
        }
        glyphs[indices[i]].atlasI = atlasI;
        glyphs[indices[i]].rect.position = Point{ position.x - glyphs[indices[i]].rect.size.w + 1, position.y - glyphs[indices[i]].rect.size.h + 1 };
        self->add(
          Image::Builder{ renderer, surfaces[indices[i]], glyphs[indices[i]].rect.position, Align::LEFT, glyphs[indices[i]].isRotated ? Rotation::QUARTER_CLOCKWISE : Rotation::NONE }
            .setA(255u)
            .setDuration(1u)  // See also ii887522::viewify::Image::Builder::setDuration(const unsigned int) for more details
            .build());
        position.y -= glyphs[indices[i]].rect.size.h + GAP;
        canGoToNextCol = true;
      }
    }
    position.x -= colW + GAP;
    position.y = glyphs[indices[glyphRows[glyphRowsI].indices.max]].rect.position.y + glyphs[indices[glyphRows[glyphRowsI].indices.max]].rect.size.h - 1;
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
    return glyphs[l].rect.size.h < glyphs[r].rect.size.h;
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
    return glyphs[indices[l]].rect.size.w < glyphs[indices[r]].rect.size.w;
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
  return ViewGroup{ renderer, Point{ 0, 0 }, [](ViewGroup*const, SDL_Renderer*const) {
    return vector<View*>{ };
  }, [this, renderer, size](ViewGroup*const self) {
    linearlyLayOutGlyphs(size);
    sort<GlyphRow, vector>(&glyphRows, [](const GlyphRow& l, const GlyphRow& r) {  // NOLINT(build/include_what_you_use)
      return l.width < r.width;
    });
    pushUpGlyphs();
    addImageViewsFromGlyphRows(self, renderer);
    if (indicesI == indices.size()) return Action::NONE;
    if (fillLShape(self, renderer, size) == Action::RETURN_FROM_CALLER) return Action::NONE;
    prepareForNextAtlas();
    return Action::NONE;
  }, [this, renderer, size](ViewGroup*const self) {
    snapshot(renderer, Rect{ Point{ 0, 0 }, size }, outputDirPath + "glyphs_" + to_string(atlasI) + ".png");
    self->clear();
    glyphRows.clear();
    glyphImageRects.clear();
    ++atlasI;
    return indicesI == indices.size() ? Action::QUIT : Action::NONE;
  } };
}

void FontPackerViewGroupFactory::writeKerningSizes() {
  for (auto i{ 0u }; i != fonts.size(); ++i) {
    if (hasKernings[i]) write<int, vector>(outputDirPath + "kernings_" + to_string(i) + BINARY_FILE_EXTENSION_NAME, kerningSizes[i]);
  }
}

void FontPackerViewGroupFactory::closeFonts() {
  for (const auto font : fonts) TTF_CloseFont(font);
}

FontPackerViewGroupFactory::~FontPackerViewGroupFactory() {
  write<Font, vector>(outputDirPath + "fonts" + BINARY_FILE_EXTENSION_NAME, fontMetadatas);
  write<Glyph, vector>(outputDirPath + "glyphs" + BINARY_FILE_EXTENSION_NAME, glyphs);
  writeKerningSizes();
  closeFonts();
  SDL_DestroyTexture(atlas);
}

}  // namespace ii887522::fontPacker

#endif
