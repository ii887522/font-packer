// Copyright ii887522

#ifndef FONT_PACKER_SRC_MAIN_ANY_COMMANDLINE_H_
#define FONT_PACKER_SRC_MAIN_ANY_COMMANDLINE_H_

#include <viewify/Struct/Size.h>
#include <string>
#include <vector>

using ii887522::viewify::Size;
using std::string;
using std::vector;

namespace ii887522::fontPacker {

/// <summary>Not Thread Safe</summary>
class CommandLine final {
  // remove copy semantics
  CommandLine(const CommandLine&) = delete;
  CommandLine& operator=(const CommandLine&) = delete;

  // remove move semantics
  CommandLine(CommandLine&&) = delete;
  CommandLine& operator=(CommandLine&&) = delete;

  /// <summary>It ends with either '/' or '\\'</summary>
  string inputDirPath;

  /// <summary>It ends with either '/' or '\\'</summary>
  string outputDirPath;

  /// <summary>Atlas is an image that contains multiple glyphs.</summary>
  Size<int> atlasSize;

  vector<int> fontSizes;

  void addFontSizes(int argc, char** argv);
  unsigned int getInputDirTTFFilesCount() const;
  bool isAllFontSizesPositive() const;

 public:
  explicit CommandLine(int argc, char** argv);

  /// <returns>It ends with either '/' or '\\'</returns>
  const string& getInputDirPath() const;

  /// <returns>It ends with either '/' or '\\'</returns>
  const string& getOutputDirPath() const;

  /// <summary>Atlas is an image that contains multiple glyphs.</summary>
  constexpr const Size<int> getAtlasSize() const {
    return atlasSize;
  }

  const vector<int>& getFontSizes() const;
  void validate() const;
};

}  // namespace ii887522::fontPacker

#endif  // FONT_PACKER_SRC_MAIN_ANY_COMMANDLINE_H_
