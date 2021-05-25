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

// Not Thread Safe
class CommandLine final {
  // remove copy semantics
  CommandLine(const CommandLine&) = delete;
  CommandLine& operator=(const CommandLine&) = delete;

  // remove move semantics
  CommandLine(CommandLine&&) = delete;
  CommandLine& operator=(CommandLine&&) = delete;

  string inputDirPath;  // It ends with either '/' or '\\'
  string outputDirPath;  // It ends with either '/' or '\\'
  Size<int> atlasSize;  // Atlas is an image that contains multiple glyphs.
  vector<int> fontSizes;

  void addFontSizes(int argc, char** argv);
  unsigned int getInputDirTTFFilesCount() const;
  bool isAllFontSizesPositive() const;

 public:
  explicit CommandLine(int argc, char** argv);

  // Return: it ends with either '/' or '\\'
  const string& getInputDirPath() const;

  // Return: it ends with either '/' or '\\'
  const string& getOutputDirPath() const;

  // Atlas is an image that contains multiple glyphs.
  constexpr const Size<int> getAtlasSize() const {
    return atlasSize;
  }

  const vector<int>& getFontSizes() const;
  void validate() const;
};

}  // namespace ii887522::fontPacker

#endif  // FONT_PACKER_SRC_MAIN_ANY_COMMANDLINE_H_
