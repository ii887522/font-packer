// Copyright ii887522

#ifndef FONT_PACKER_SRC_MAIN_VIEWGROUPFACTORY_FONTPACKERVIEWGROUPFACTORY_H_
#define FONT_PACKER_SRC_MAIN_VIEWGROUPFACTORY_FONTPACKERVIEWGROUPFACTORY_H_

#ifndef TEST

#include <viewify/viewify.h>
#include <nitro/nitro.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <vector>
#include <functional>
#include "../Struct/Glyph.h"
#include "../Struct/GlyphRow.h"
#include "../Struct/Font.h"

using ii887522::viewify::ViewGroupFactory;
using ii887522::viewify::ViewGroup;
using ii887522::viewify::Size;
using ii887522::viewify::QuadTree;
using ii887522::viewify::Action;
using ii887522::nitro::Range;
using std::string;
using std::vector;
using std::function;

namespace ii887522::fontPacker {

constexpr auto GAP{ 0 };
constexpr Range CHAR_RANGE{ 32, 126 };
constexpr auto BINARY_FILE_EXTENSION_NAME{ ".dat" };

/// <summary>
///   <para>Font Packer is a CLI tool used to generate glyph atlases for graphics applications such as GUI, video games and so on to improve performance of these applications.</para>
///   <para>Atlas is an image that contains multiple glyphs.</para>
///   <para>Not Thread Safe: it must only be used in main thread</para>
///   <para>See also viewify/View/ViewGroup.h for more details</para>
///   <para>See also ../Struct/Glyph.h for more details</para>
/// </summary>
class FontPackerViewGroupFactory final : public ViewGroupFactory {
  // remove copy semantics
  FontPackerViewGroupFactory(const FontPackerViewGroupFactory&) = delete;
  FontPackerViewGroupFactory& operator=(const FontPackerViewGroupFactory&) = delete;

  // remove move semantics
  FontPackerViewGroupFactory(FontPackerViewGroupFactory&&) = delete;
  FontPackerViewGroupFactory& operator=(FontPackerViewGroupFactory&&) = delete;

  SDL_Texture* atlas;

  /// <summary>It ends with either '/' or '\\'</summary>
  const string outputDirPath;

  vector<TTF_Font*> fonts;
  vector<Font> fontMetadatas;

  /// <summary>Kerning is the process of adjusting the glyph position to reduce spaces between characters to produce a nice looking text.</summary>
  vector<bool> hasKernings;

  /// <summary>See also ../Struct/Glyph.h for more details</summary>
  vector<Glyph> glyphs;

  vector<SDL_Surface*> surfaces;
  vector<unsigned int> indices;

  /// <summary>Kerning is the process of adjusting the glyph position to reduce spaces between characters to produce a nice looking text.</summary>
  vector<vector<int>> kerningSizes;

  /// <summary>See also ../Struct/Glyph.h for more details</summary>
  vector<GlyphRow> glyphRows;

  /// <summary>See also ../Struct/Glyph.h for more details</summary>
  QuadTree glyphImageRects;

  vector<unsigned int> lPendingIndices;
  vector<unsigned int> rPendingIndices;
  vector<unsigned int>* currentPendingIndices;
  vector<unsigned int>* nextPendingIndices;
  unsigned int indicesI;

  /// <summary>
  ///   <para>Atlas is an image that contains multiple glyphs.</para>
  ///   <para>See also ../Struct/Glyph.h for more details</para>
  /// </summary>
  unsigned int atlasI;

  /// <summary>It must only be called 1 time.</summary>
  /// <param name="inputDirPath">It must exists and ends with either '/' or '\\'</param>
  void addFonts(const string& inputDirPath, const vector<int>& fontSizes);

  /// <summary>It must only be called 1 time.</summary>
  void addFontMetadatas(const vector<int>& fontSizes);

  /// <summary>
  ///   <para>Kerning is the process of adjusting the glyph position to reduce spaces between characters to produce a nice looking text.</para>
  ///   <para>It must only be called 1 time.</para>
  /// </summary>
  void addHasKernings();

  /// <summary>
  ///   <para>Atlas is an image that contains multiple glyphs.</para>
  ///   <para>It must only be called 1 time.</para>
  ///   <para>See also ../Struct/Glyph.h for more details</para>
  /// </summary>
  void addImages(const Size<int>& atlasSize);

  /// <summary>
  ///   <para>Atlas is an image that contains multiple glyphs.</para>
  ///   <para>See also ../Struct/Glyph.h for more details</para>
  /// </summary>
  void addImage(const unsigned int fontsI, const char ch, const unsigned int i, const Size<int>& atlasSize);

  /// <summary>
  ///   <para>Kerning is the process of adjusting the glyph position to reduce spaces between characters to produce a nice looking text.</para>
  ///   <para>It must only be called 1 time.</para>
  /// </summary>
  void addKerningSizes();

  /// <summary>It must only be called 1 time.</summary>
  void rotateImagesToMakeThemLonger();

  /// <param name="compare">It returns true if the image needs to be rotated</param>
  void rotateSomeImages(const vector<unsigned int>& pendingIndices, const function<bool(const unsigned int w, const unsigned int h)>& compare);

  /// <summary>
  ///   <para>Atlas is an image that contains multiple glyphs.</para>
  ///   <para>See also ../Struct/Glyph.h for more details</para>
  /// </summary>
  void linearlyLayOutGlyphs(const Size<int>& atlasSize);

  /// <summary>See also ../Struct/Glyph.h for more details</summary>
  void pushUpGlyphs();

  /// <summary>
  ///   <para>See also viewify/View/ViewGroup.h for more details</para>
  ///   <para>See also ../Struct/Glyph.h for more details</para>
  /// </summary>
  /// <param name="self">It must not be assigned to nullptr or integer</param>
  /// <param name="renderer">It must not be assigned to nullptr or integer</param>
  void addImageViewsFromGlyphRows(ViewGroup*const self, SDL_Renderer*const renderer);

  /// <summary>
  ///   <para>Atlas is an image that contains multiple glyphs.</para>
  ///   <para>See also ../Struct/Glyph.h for more details</para>
  /// </summary>
  unsigned int getNearestGlyphRowToAtlasBottomRightCornerI(const Size<int>& atlasSize) const;

  /// <summary>
  ///   <para>Atlas is an image that contains multiple glyphs.</para>
  ///   <para>See also viewify/Any/View.h for more details</para>
  ///   <para>See also ../Struct/Glyph.h for more details</para>
  /// </summary>
  /// <param name="self">It must not be assigned to nullptr or integer</param>
  /// <param name="renderer">It must not be assigned to nullptr or integer</param>
  /// <param name="glyphRowsI">The atlas bottom region that below the glyph row referenced by this</param>
  Action linearlyFillAtlasBottom(ViewGroup*const self, SDL_Renderer*const renderer, const Size<int>& atlasSize, const unsigned int glyphRowsI);

  /// <summary>
  ///   <para>Atlas is an image that contains multiple glyphs.</para>
  ///   <para>See also viewify/Any/View.h for more details</para>
  ///   <para>See also ../Struct/Glyph.h for more details</para>
  /// </summary>
  /// <param name="self">It must not be assigned to nullptr or integer</param>
  /// <param name="renderer">It must not be assigned to nullptr or integer</param>
  /// <param name="glyphRowsI">The atlas bottom region that below the glyph row referenced by this</param>
  Action linearlyFillAtlasRight(ViewGroup*const self, SDL_Renderer*const renderer, const Size<int>& atlasSize, const unsigned int glyphRowsI);

  vector<unsigned int> getIndicesReferencedByPendingIndices() const;

  /// <summary>
  ///   <para>Atlas is an image that contains multiple glyphs.</para>
  ///   <para>See also ../Struct/Glyph.h for more details</para>
  /// </summary>
  void prepareForNextAtlas();

  /// <summary>
  ///   <para>L Shape represents the atlas bottom region and right region where they are not allocated to any glyphs.</para>
  ///   <para>Atlas is an image that contains multiple glyphs.</para>
  ///   <para>See also viewify/Any/View.h for more details</para>
  ///   <para>See also ../Struct/Glyph.h for more details</para>
  /// </summary>
  /// <param name="self">It must not be assigned to nullptr or integer</param>
  /// <param name="renderer">It must not be assigned to nullptr or integer</param>
  Action fillLShape(ViewGroup*const self, SDL_Renderer*const renderer, const Size<int>& atlasSize);

  /// <summary>
  ///   <para>Kerning is the process of adjusting the glyph position to reduce spaces between characters to produce a nice looking text.</para>
  ///   <para>It must only be called 1 time.</para>
  /// </summary>
  void writeKerningSizes();

  /// <summary>It must only be called 1 time.</summary>
  void closeFonts();

 public:
  /// <summary>
  ///   <para>Atlas is an image that contains multiple glyphs.</para>
  ///   <para>See also viewify/View/ViewGroup.h for more details</para>
  ///   <para>See also ../Struct/Glyph.h for more details</para>
  /// </summary>
  /// <param name="inputDirPath">It must exists and ends with either '/' or '\\'</param>
  /// <param name="outputDirPath">It must ends with either '/' or '\\'</param>
  explicit FontPackerViewGroupFactory(const string& inputDirPath, const string& outputDirPath, const Size<int>& atlasSize, const vector<int>& fontSizes);

  /// <summary>See also viewify/View/ViewGroup.h for more details.</summary>
  /// <param name="renderer">It must not be assigned to nullptr or integer</param>
  ViewGroup make(SDL_Renderer*const renderer, const Size<int>&) override;

  /// <summary>See also viewify/View/ViewGroup.h for more details</summary>
  ~FontPackerViewGroupFactory();
};

}  // namespace ii887522::fontPacker

#endif
#endif  // FONT_PACKER_SRC_MAIN_VIEWGROUPFACTORY_FONTPACKERVIEWGROUPFACTORY_H_
