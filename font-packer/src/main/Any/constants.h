// Copyright ii887522

#ifndef FONT_PACKER_SRC_MAIN_ANY_CONSTANTS_H_
#define FONT_PACKER_SRC_MAIN_ANY_CONSTANTS_H_

namespace ii887522::fontPacker {

constexpr auto MIN_COMMAND_LINE_ARGS_REQUIRED{ 5u };
constexpr auto PROGRAM_NAME_INDEX{ 0u };
constexpr auto INPUT_DIRECTORY_PATH_INDEX{ 1u };
constexpr auto OUTPUT_DIRECTORY_PATH_INDEX{ 2u };
constexpr auto ATLAS_WIDTH_INDEX{ 3u };
constexpr auto ATLAS_HEIGHT_INDEX{ 4u };
constexpr auto FONT_SIZES_START_INDEX{ 5u };
constexpr auto LOWER_CASE_FONT_EXTENSION_NAME{ ".ttf" };
constexpr auto UPPER_CASE_FONT_EXTENSION_NAME{ ".TTF" };

}  // namespace ii887522::fontPacker

#endif  // FONT_PACKER_SRC_MAIN_ANY_CONSTANTS_H_
