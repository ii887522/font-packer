// Copyright ii887522

#ifdef TEST

#include <cstring>
#include <catch.hpp>
#include "../../main/Any/constants.h"
#include "../../main/Functions/cli_ext.h"

namespace ii887522::fontPacker {

TEST_CASE("test isFontSizesUint() function") {
  {
    char* args[]{ new char[12u], new char[12u], new char[12u], new char[2u], new char[2u], new char[2u] };
    strcpy_s(args[PROGRAM_NAME_INDEX], 12u, "font-packer");
    strcpy_s(args[INPUT_DIRECTORY_PATH_INDEX], 12u, "res/test/a/");
    strcpy_s(args[OUTPUT_DIRECTORY_PATH_INDEX], 12u, "res/test/b/");
    strcpy_s(args[ATLAS_WIDTH_INDEX], 2u, "1");
    strcpy_s(args[ATLAS_HEIGHT_INDEX], 2u, "1");
    strcpy_s(args[FONT_SIZES_START_INDEX], 2u, "a");
    REQUIRE_FALSE(isFontSizesUint(sizeof args / sizeof(char*), args));
  }
  {
    char* args[]{ new char[12u], new char[12u], new char[12u], new char[2u], new char[2u], new char[2u] };
    strcpy_s(args[PROGRAM_NAME_INDEX], 12u, "font-packer");
    strcpy_s(args[INPUT_DIRECTORY_PATH_INDEX], 12u, "res/test/a/");
    strcpy_s(args[OUTPUT_DIRECTORY_PATH_INDEX], 12u, "res/test/b/");
    strcpy_s(args[ATLAS_WIDTH_INDEX], 2u, "1");
    strcpy_s(args[ATLAS_HEIGHT_INDEX], 2u, "1");
    strcpy_s(args[FONT_SIZES_START_INDEX], 2u, "1");
    REQUIRE(isFontSizesUint(sizeof args / sizeof(char*), args));
  }
  {
    char* args[]{ new char[12u], new char[12u], new char[12u], new char[2u], new char[2u], new char[2u], new char[2u] };
    strcpy_s(args[PROGRAM_NAME_INDEX], 12u, "font-packer");
    strcpy_s(args[INPUT_DIRECTORY_PATH_INDEX], 12u, "res/test/a/");
    strcpy_s(args[OUTPUT_DIRECTORY_PATH_INDEX], 12u, "res/test/b/");
    strcpy_s(args[ATLAS_WIDTH_INDEX], 2u, "1");
    strcpy_s(args[ATLAS_HEIGHT_INDEX], 2u, "1");
    strcpy_s(args[FONT_SIZES_START_INDEX], 2u, "1");
    strcpy_s(args[FONT_SIZES_START_INDEX + 1u], 2u, "a");
    REQUIRE_FALSE(isFontSizesUint(sizeof args / sizeof(char*), args));
  }
  {
    char* args[]{ new char[12u], new char[12u], new char[12u], new char[2u], new char[2u], new char[2u], new char[2u] };
    strcpy_s(args[PROGRAM_NAME_INDEX], 12u, "font-packer");
    strcpy_s(args[INPUT_DIRECTORY_PATH_INDEX], 12u, "res/test/a/");
    strcpy_s(args[OUTPUT_DIRECTORY_PATH_INDEX], 12u, "res/test/b/");
    strcpy_s(args[ATLAS_WIDTH_INDEX], 2u, "1");
    strcpy_s(args[ATLAS_HEIGHT_INDEX], 2u, "1");
    strcpy_s(args[FONT_SIZES_START_INDEX], 2u, "a");
    strcpy_s(args[FONT_SIZES_START_INDEX + 1u], 2u, "1");
    REQUIRE_FALSE(isFontSizesUint(sizeof args / sizeof(char*), args));
  }
  {
    char* args[]{ new char[12u], new char[12u], new char[12u], new char[2u], new char[2u], new char[2u], new char[2u] };
    strcpy_s(args[PROGRAM_NAME_INDEX], 12u, "font-packer");
    strcpy_s(args[INPUT_DIRECTORY_PATH_INDEX], 12u, "res/test/a/");
    strcpy_s(args[OUTPUT_DIRECTORY_PATH_INDEX], 12u, "res/test/b/");
    strcpy_s(args[ATLAS_WIDTH_INDEX], 2u, "1");
    strcpy_s(args[ATLAS_HEIGHT_INDEX], 2u, "1");
    strcpy_s(args[FONT_SIZES_START_INDEX], 2u, "1");
    strcpy_s(args[FONT_SIZES_START_INDEX + 1u], 2u, "1");
    REQUIRE(isFontSizesUint(sizeof args / sizeof(char*), args));
  }
  {
    char* args[]{ new char[12u], new char[12u], new char[12u], new char[2u], new char[2u], new char[2u], new char[2u], new char[2u] };
    strcpy_s(args[PROGRAM_NAME_INDEX], 12u, "font-packer");
    strcpy_s(args[INPUT_DIRECTORY_PATH_INDEX], 12u, "res/test/a/");
    strcpy_s(args[OUTPUT_DIRECTORY_PATH_INDEX], 12u, "res/test/b/");
    strcpy_s(args[ATLAS_WIDTH_INDEX], 2u, "1");
    strcpy_s(args[ATLAS_HEIGHT_INDEX], 2u, "1");
    strcpy_s(args[FONT_SIZES_START_INDEX], 2u, "1");
    strcpy_s(args[FONT_SIZES_START_INDEX + 1u], 2u, "1");
    strcpy_s(args[FONT_SIZES_START_INDEX + 2u], 2u, "a");
    REQUIRE_FALSE(isFontSizesUint(sizeof args / sizeof(char*), args));
  }
  {
    char* args[]{ new char[12u], new char[12u], new char[12u], new char[2u], new char[2u], new char[2u], new char[2u], new char[2u] };
    strcpy_s(args[PROGRAM_NAME_INDEX], 12u, "font-packer");
    strcpy_s(args[INPUT_DIRECTORY_PATH_INDEX], 12u, "res/test/a/");
    strcpy_s(args[OUTPUT_DIRECTORY_PATH_INDEX], 12u, "res/test/b/");
    strcpy_s(args[ATLAS_WIDTH_INDEX], 2u, "1");
    strcpy_s(args[ATLAS_HEIGHT_INDEX], 2u, "1");
    strcpy_s(args[FONT_SIZES_START_INDEX], 2u, "1");
    strcpy_s(args[FONT_SIZES_START_INDEX + 1u], 2u, "1");
    strcpy_s(args[FONT_SIZES_START_INDEX + 2u], 2u, "1");
    REQUIRE(isFontSizesUint(sizeof args / sizeof(char*), args));
  }
}

}  // namespace ii887522::fontPacker

#endif
