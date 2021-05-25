// Copyright ii887522

#ifdef TEST

#include "cli_ext.test.h"  // NOLINT(build/include_subdir)
#include <cassert>
#include <cstring>
#include "../../main/Any/constants.h"
#include "../../main/Functions/cli_ext.h"

namespace ii887522::fontPacker {

static void testIsFontSizesUint() {
  {
    char* args[]{ new char[12u], new char[12u], new char[12u], new char[2u], new char[2u], new char[2u] };
    strcpy_s(args[PROGRAM_NAME_INDEX], 12u, "font-packer");
    strcpy_s(args[INPUT_DIRECTORY_PATH_INDEX], 12u, "res/test/a/");
    strcpy_s(args[OUTPUT_DIRECTORY_PATH_INDEX], 12u, "res/test/b/");
    strcpy_s(args[ATLAS_WIDTH_INDEX], 2u, "1");
    strcpy_s(args[ATLAS_HEIGHT_INDEX], 2u, "1");
    strcpy_s(args[FONT_SIZES_START_INDEX], 2u, "a");
    assert(!isFontSizesUint(sizeof args / sizeof(char*), args));
  }
  {
    char* args[]{ new char[12u], new char[12u], new char[12u], new char[2u], new char[2u], new char[2u] };
    strcpy_s(args[PROGRAM_NAME_INDEX], 12u, "font-packer");
    strcpy_s(args[INPUT_DIRECTORY_PATH_INDEX], 12u, "res/test/a/");
    strcpy_s(args[OUTPUT_DIRECTORY_PATH_INDEX], 12u, "res/test/b/");
    strcpy_s(args[ATLAS_WIDTH_INDEX], 2u, "1");
    strcpy_s(args[ATLAS_HEIGHT_INDEX], 2u, "1");
    strcpy_s(args[FONT_SIZES_START_INDEX], 2u, "1");
    assert(isFontSizesUint(sizeof args / sizeof(char*), args));
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
    assert(!isFontSizesUint(sizeof args / sizeof(char*), args));
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
    assert(!isFontSizesUint(sizeof args / sizeof(char*), args));
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
    assert(isFontSizesUint(sizeof args / sizeof(char*), args));
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
    assert(!isFontSizesUint(sizeof args / sizeof(char*), args));
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
    assert(isFontSizesUint(sizeof args / sizeof(char*), args));
  }
}

void testCliExt() {
  testIsFontSizesUint();
}

}  // namespace ii887522::fontPacker

#endif
