// Copyright ii887522

#ifndef FONT_PACKER_SRC_MAIN_VIEWGROUPFACTORY_FONTPACKERVIEWGROUPFACTORY_H_
#define FONT_PACKER_SRC_MAIN_VIEWGROUPFACTORY_FONTPACKERVIEWGROUPFACTORY_H_

#ifndef TEST

#include <viewify/Factory/ViewGroupFactory.h>
#include <viewify/View/ViewGroup.h>
#include <viewify/Struct/Size.h>
#include <viewify/Any/QuadTree.h>
#include <viewify/Any/Enums.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <vector>
#include <functional>
#include "../Struct/Glyph.h"
#include "../Struct/Kerning.h"
#include "../Struct/GlyphRow.h"

using ii887522::viewify::ViewGroupFactory;
using ii887522::viewify::ViewGroup;
using ii887522::viewify::Size;
using ii887522::viewify::QuadTree;
using ii887522::viewify::Action;
using std::string;
using std::vector;
using std::function;

namespace ii887522::fontPacker {

// Font Packer is a CLI tool used to generate glyph atlases for graphics applications such as GUI, video games and so on to improve performance of these applications.
// Atlas is an image that contains multiple glyphs.
//
// Not Thread Safe: it must only be used in main thread
// See also viewify/View/ViewGroup.h for more details
// See also ../Struct/Glyph.h for more details
class FontPackerViewGroupFactory final : public ViewGroupFactory {
  // remove copy semantics
  FontPackerViewGroupFactory(const FontPackerViewGroupFactory&) = delete;
  FontPackerViewGroupFactory& operator=(const FontPackerViewGroupFactory&) = delete;

  // remove move semantics
  FontPackerViewGroupFactory(FontPackerViewGroupFactory&&) = delete;
  FontPackerViewGroupFactory& operator=(FontPackerViewGroupFactory&&) = delete;

  SDL_Texture* atlas;
  const string outputDirPath;  // It ends with either '/' or '\\'
  vector<TTF_Font*> fonts;
  vector<bool> hasKernings;
  vector<Glyph> glyphs;  // See also ../Struct/Glyph.h for more details
  vector<SDL_Surface*> surfaces;
  vector<unsigned int> indices;
  vector<vector<Kerning>> kernings;  // See also ../Struct/Kerning.h for more details
  vector<GlyphRow> glyphRows;  // See also ../Struct/Glyph.h for more details
  QuadTree glyphImageRects;  // See also ../Struct/Glyph.h for more details
  vector<unsigned int> lPendingIndices;
  vector<unsigned int> rPendingIndices;
  vector<unsigned int>* currentPendingIndices;
  vector<unsigned int>* nextPendingIndices;
  const int gap;
  unsigned int indicesI;

  // Atlas is an image that contains multiple glyphs.
  // See also ../Struct/Glyph.h for more details
  unsigned int atlasIndex;

  // It must only be called 1 time.
  // Param inputDirPath: it must exists and ends with either '/' or '\\'
  void addFonts(const string& inputDirPath, const vector<int>& fontSizes);

  // It must only be called 1 time.
  // See also ../Struct/Kerning.h for more details
  void addHasKernings();

  // Atlas is an image that contains multiple glyphs. It must only be called 1 time.
  // See also ../Struct/Glyph.h for more details
  void addImages(const Size<int>& atlasSize);

  // Atlas is an image that contains multiple glyphs.
  // See also ../Struct/Glyph.h for more details
  void addImage(const unsigned int fontsIndex, const char ch, const unsigned int index, const Size<int>& atlasSize);

  // It must only be called 1 time.
  // See also ../Struct/Kerning.h for more details
  void addKernings();

  // It must only be called 1 time.
  void rotateImagesToMakeThemLonger();

  // Param compare: it returns true if the image needs to be rotated
  void rotateSomeImages(const vector<unsigned int>& pendingIndices, const function<bool(const unsigned int, const unsigned int)>& compare);

  // Atlas is an image that contains multiple glyphs.
  // See also ../Struct/Glyph.h for more details
  void linearlyLayOutGlyphs(const Size<int>& atlasSize);

  // See also ../Struct/Glyph.h for more details
  void pushUpGlyphs();

  // Param self: it must not be assigned to nullptr or integer
  // Param renderer: it must not be assigned to nullptr or integer
  // See also viewify/View/ViewGroup.h for more details
  // See also ../Struct/Glyph.h for more details
  void addImageViewsFromGlyphRows(ViewGroup*const self, SDL_Renderer*const renderer);

  // Atlas is an image that contains multiple glyphs.
  // See also ../Struct/Glyph.h for more details
  unsigned int getNearestGlyphRowToAtlasBottomRightCornerI(const Size<int>& atlasSize) const;

  // Atlas is an image that contains multiple glyphs.
  //
  // Param self: it must not be assigned to nullptr or integer
  // Param renderer: it must not be assigned to nullptr or integer
  // Param glyphRowsI: the atlas bottom region that below the glyph row referenced by this
  // See also viewify/Any/View.h for more details
  // See also ../Struct/Glyph.h for more details
  Action linearlyFillAtlasBottom(ViewGroup*const self, SDL_Renderer*const renderer, const Size<int>& atlasSize, const unsigned int glyphRowsI);

  // Atlas is an image that contains multiple glyphs.
  //
  // Param self: it must not be assigned to nullptr or integer
  // Param renderer: it must not be assigned to nullptr or integer
  // Param glyphRowsI: the atlas bottom region that below the glyph row referenced by this
  // See also viewify/Any/View.h for more details
  // See also ../Struct/Glyph.h for more details
  Action linearlyFillAtlasRight(ViewGroup*const self, SDL_Renderer*const renderer, const Size<int>& atlasSize, const unsigned int glyphRowsI);

  vector<unsigned int> getIndicesReferencedByPendingIndices() const;

  // Atlas is an image that contains multiple glyphs.
  // See also ../Struct/Glyph.h for more details
  void prepareForNextAtlas();

  // L Shape represents the atlas bottom region and right region where they are not allocated to any glyphs.
  // Atlas is an image that contains multiple glyphs.
  //
  // Param self: it must not be assigned to nullptr or integer
  // Param renderer: it must not be assigned to nullptr or integer
  // See also viewify/Any/View.h for more details
  // See also ../Struct/Glyph.h for more details
  Action fillLShape(ViewGroup*const self, SDL_Renderer*const renderer, const Size<int>& atlasSize);

  // It must only be called 1 time.
  // See also ../Struct/Kerning.h for more details
  void writeKernings();

  // It must only be called 1 time.
  void closeFonts();

 public:
  // Atlas is an image that contains multiple glyphs.
  //
  // Param inputDirPath: it must exists and ends with either '/' or '\\'
  // Param outputDirPath: it must ends with either '/' or '\\'
  // See also viewify/View/ViewGroup.h for more details
  // See also ../Struct/Glyph.h for more details
  explicit FontPackerViewGroupFactory(const string& inputDirPath, const string& outputDirPath, const Size<int>& atlasSize, const vector<int>& fontSizes);

  // Param renderer: it must not be assigned to nullptr or integer
  // See also viewify/View/ViewGroup.h for more details
  ViewGroup make(SDL_Renderer*const renderer, const Size<int>&) override;

  // See also viewify/View/ViewGroup.h for more details
  ~FontPackerViewGroupFactory();
};

}  // namespace ii887522::fontPacker

#endif
#endif  // FONT_PACKER_SRC_MAIN_VIEWGROUPFACTORY_FONTPACKERVIEWGROUPFACTORY_H_
