// Copyright ii887522

#ifndef FONT_PACKER_SRC_MAIN_ANY_COMMAND_LINE_H_
#define FONT_PACKER_SRC_MAIN_ANY_COMMAND_LINE_H_

#include <viewify/Struct/Size.h>
#include <string>

using ii887522::viewify::Size;
using std::string;

namespace ii887522::fontPacker {

// Not Thread Safe
class CommandLine final {
  // remove copy semantics
  CommandLine(const CommandLine&) = delete;
  CommandLine& operator=(const CommandLine&) = delete;

  // remove move semantics
  CommandLine(CommandLine&&) = delete;
  CommandLine& operator=(CommandLine&&) = delete;

  string fontFilePath;  // It ends with .ttf
  int fontSize;
  string outputDirPath;  // It ends with either '/' or '\\'
  Size<int> atlasSize;  // Atlas is an image that contains multiple glyphs.

public:
  explicit CommandLine(int argc, char** argv);

  // Return: it ends with .ttf
  const string& getFontFilePath() const;

  constexpr int getFontSize() const {
    return fontSize;
  }

  // Return: it ends with either '/' or '\\'
  const string& getOutputDirPath() const;

  // Atlas is an image that contains multiple glyphs.
  constexpr const Size<int> getAtlasSize() const {
    return atlasSize;
  }

  void validate() const;
};

}  // namespace ii887522::fontPacker

#endif  // FONT_PACKER_SRC_MAIN_ANY_COMMAND_LINE_H_
