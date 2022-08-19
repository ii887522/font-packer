// Copyright ii887522

#ifdef TEST

#include <stdexcept>
#include <cstring>
#include <filesystem>
#include <catch.hpp>
#include "../../main/Any/constants.h"
#include "../../main/Any/CommandLine.h"

using std::invalid_argument;
using std::filesystem::create_directory;
using std::filesystem::remove_all;

namespace ii887522::fontPacker {

TEST_CASE("test CommandLine.h") {
  create_directory("res/test/j/");
  SECTION("test validate() function") {
    {
      char* args[]{ new char[12u] };
      strcpy_s(args[PROGRAM_NAME_INDEX], 12u, "font-packer");
      REQUIRE_THROWS_AS((CommandLine{ sizeof args / sizeof(char*), args }.getAtlasSize()), invalid_argument);
    }
    {
      char* args[]{ new char[12u], new char[2u] };
      strcpy_s(args[PROGRAM_NAME_INDEX], 12u, "font-packer");
      strcpy_s(args[INPUT_DIRECTORY_PATH_INDEX], 2u, "a");
      REQUIRE_THROWS_AS((CommandLine{ sizeof args / sizeof(char*), args }.getAtlasSize()), invalid_argument);
    }
    {
      char* args[]{ new char[12u], new char[2u], new char[2u], new char[2u], new char[2u], new char[2u] };
      strcpy_s(args[PROGRAM_NAME_INDEX], 12u, "font-packer");
      strcpy_s(args[INPUT_DIRECTORY_PATH_INDEX], 2u, "a");
      strcpy_s(args[OUTPUT_DIRECTORY_PATH_INDEX], 2u, "a");
      strcpy_s(args[ATLAS_WIDTH_INDEX], 2u, "a");
      strcpy_s(args[ATLAS_HEIGHT_INDEX], 2u, "a");
      strcpy_s(args[FONT_SIZES_START_INDEX], 2u, "a");
      REQUIRE_THROWS_AS((CommandLine{ sizeof args / sizeof(char*), args }.getAtlasSize()), invalid_argument);
    }
    {
      char* args[]{ new char[12u], new char[2u], new char[2u], new char[2u], new char[2u], new char[2u] };
      strcpy_s(args[PROGRAM_NAME_INDEX], 12u, "font-packer");
      strcpy_s(args[INPUT_DIRECTORY_PATH_INDEX], 2u, "a");
      strcpy_s(args[OUTPUT_DIRECTORY_PATH_INDEX], 2u, "a");
      strcpy_s(args[ATLAS_WIDTH_INDEX], 2u, "0");
      strcpy_s(args[ATLAS_HEIGHT_INDEX], 2u, "a");
      strcpy_s(args[FONT_SIZES_START_INDEX], 2u, "a");
      REQUIRE_THROWS_AS((CommandLine{ sizeof args / sizeof(char*), args }.getAtlasSize()), invalid_argument);
    }
    {
      char* args[]{ new char[12u], new char[2u], new char[2u], new char[2u], new char[2u], new char[2u] };
      strcpy_s(args[PROGRAM_NAME_INDEX], 12u, "font-packer");
      strcpy_s(args[INPUT_DIRECTORY_PATH_INDEX], 2u, "a");
      strcpy_s(args[OUTPUT_DIRECTORY_PATH_INDEX], 2u, "a");
      strcpy_s(args[ATLAS_WIDTH_INDEX], 2u, "0");
      strcpy_s(args[ATLAS_HEIGHT_INDEX], 2u, "0");
      strcpy_s(args[FONT_SIZES_START_INDEX], 2u, "a");
      REQUIRE_THROWS_AS((CommandLine{ sizeof args / sizeof(char*), args }.getAtlasSize()), invalid_argument);
    }
    {
      char* args[]{ new char[12u], new char[2u], new char[2u], new char[2u], new char[2u], new char[2u] };
      strcpy_s(args[PROGRAM_NAME_INDEX], 12u, "font-packer");
      strcpy_s(args[INPUT_DIRECTORY_PATH_INDEX], 2u, "a");
      strcpy_s(args[OUTPUT_DIRECTORY_PATH_INDEX], 2u, "a");
      strcpy_s(args[ATLAS_WIDTH_INDEX], 2u, "0");
      strcpy_s(args[ATLAS_HEIGHT_INDEX], 2u, "0");
      strcpy_s(args[FONT_SIZES_START_INDEX], 2u, "a");
      REQUIRE_THROWS_AS((CommandLine{ sizeof args / sizeof(char*), args }.getAtlasSize()), invalid_argument);
    }
    {
      char* args[]{ new char[12u], new char[2u], new char[2u], new char[2u], new char[2u], new char[2u] };
      strcpy_s(args[PROGRAM_NAME_INDEX], 12u, "font-packer");
      strcpy_s(args[INPUT_DIRECTORY_PATH_INDEX], 2u, "a");
      strcpy_s(args[OUTPUT_DIRECTORY_PATH_INDEX], 2u, "a");
      strcpy_s(args[ATLAS_WIDTH_INDEX], 2u, "0");
      strcpy_s(args[ATLAS_HEIGHT_INDEX], 2u, "0");
      strcpy_s(args[FONT_SIZES_START_INDEX], 2u, "0");
      REQUIRE_THROWS_AS((CommandLine{ sizeof args / sizeof(char*), args }.validate()), invalid_argument);
    }
    {
      char* args[]{ new char[12u], new char[3u], new char[2u], new char[2u], new char[2u], new char[2u] };
      strcpy_s(args[PROGRAM_NAME_INDEX], 12u, "font-packer");
      strcpy_s(args[INPUT_DIRECTORY_PATH_INDEX], 3u, "a/");
      strcpy_s(args[OUTPUT_DIRECTORY_PATH_INDEX], 2u, "a");
      strcpy_s(args[ATLAS_WIDTH_INDEX], 2u, "0");
      strcpy_s(args[ATLAS_HEIGHT_INDEX], 2u, "0");
      strcpy_s(args[FONT_SIZES_START_INDEX], 2u, "0");
      REQUIRE_THROWS_AS((CommandLine{ sizeof args / sizeof(char*), args }.validate()), invalid_argument);
    }
    {
      char* args[]{ new char[12u], new char[3u], new char[2u], new char[2u], new char[2u], new char[2u] };
      strcpy_s(args[PROGRAM_NAME_INDEX], 12u, "font-packer");
      strcpy_s(args[INPUT_DIRECTORY_PATH_INDEX], 3u, "a\\");
      strcpy_s(args[OUTPUT_DIRECTORY_PATH_INDEX], 2u, "a");
      strcpy_s(args[ATLAS_WIDTH_INDEX], 2u, "0");
      strcpy_s(args[ATLAS_HEIGHT_INDEX], 2u, "0");
      strcpy_s(args[FONT_SIZES_START_INDEX], 2u, "0");
      REQUIRE_THROWS_AS((CommandLine{ sizeof args / sizeof(char*), args }.validate()), invalid_argument);
    }
    {
      char* args[]{ new char[12u], new char[12u], new char[2u], new char[2u], new char[2u], new char[2u] };
      strcpy_s(args[PROGRAM_NAME_INDEX], 12u, "font-packer");
      strcpy_s(args[INPUT_DIRECTORY_PATH_INDEX], 12u, "res\\test\\a\\");
      strcpy_s(args[OUTPUT_DIRECTORY_PATH_INDEX], 2u, "a");
      strcpy_s(args[ATLAS_WIDTH_INDEX], 2u, "0");
      strcpy_s(args[ATLAS_HEIGHT_INDEX], 2u, "0");
      strcpy_s(args[FONT_SIZES_START_INDEX], 2u, "0");
      REQUIRE_THROWS_AS((CommandLine{ sizeof args / sizeof(char*), args }.validate()), invalid_argument);
    }
    {
      char* args[]{ new char[12u], new char[12u], new char[3u], new char[2u], new char[2u], new char[2u] };
      strcpy_s(args[PROGRAM_NAME_INDEX], 12u, "font-packer");
      strcpy_s(args[INPUT_DIRECTORY_PATH_INDEX], 12u, "res\\test\\a\\");
      strcpy_s(args[OUTPUT_DIRECTORY_PATH_INDEX], 3u, "a/");
      strcpy_s(args[ATLAS_WIDTH_INDEX], 2u, "0");
      strcpy_s(args[ATLAS_HEIGHT_INDEX], 2u, "0");
      strcpy_s(args[FONT_SIZES_START_INDEX], 2u, "0");
      REQUIRE_THROWS_AS((CommandLine{ sizeof args / sizeof(char*), args }.validate()), invalid_argument);
    }
    {
      char* args[]{ new char[12u], new char[12u], new char[3u], new char[2u], new char[2u], new char[2u] };
      strcpy_s(args[PROGRAM_NAME_INDEX], 12u, "font-packer");
      strcpy_s(args[INPUT_DIRECTORY_PATH_INDEX], 12u, "res\\test\\a\\");
      strcpy_s(args[OUTPUT_DIRECTORY_PATH_INDEX], 3u, "a\\");
      strcpy_s(args[ATLAS_WIDTH_INDEX], 2u, "0");
      strcpy_s(args[ATLAS_HEIGHT_INDEX], 2u, "0");
      strcpy_s(args[FONT_SIZES_START_INDEX], 2u, "0");
      REQUIRE_THROWS_AS((CommandLine{ sizeof args / sizeof(char*), args }.validate()), invalid_argument);
    }
    {
      char* args[]{ new char[12u], new char[12u], new char[3u], new char[2u], new char[2u], new char[2u] };
      strcpy_s(args[PROGRAM_NAME_INDEX], 12u, "font-packer");
      strcpy_s(args[INPUT_DIRECTORY_PATH_INDEX], 12u, "res\\test\\a\\");
      strcpy_s(args[OUTPUT_DIRECTORY_PATH_INDEX], 3u, "a\\");
      strcpy_s(args[ATLAS_WIDTH_INDEX], 2u, "1");
      strcpy_s(args[ATLAS_HEIGHT_INDEX], 2u, "0");
      strcpy_s(args[FONT_SIZES_START_INDEX], 2u, "0");
      REQUIRE_THROWS_AS((CommandLine{ sizeof args / sizeof(char*), args }.validate()), invalid_argument);
    }
    {
      char* args[]{ new char[12u], new char[12u], new char[3u], new char[2u], new char[2u], new char[2u] };
      strcpy_s(args[PROGRAM_NAME_INDEX], 12u, "font-packer");
      strcpy_s(args[INPUT_DIRECTORY_PATH_INDEX], 12u, "res\\test\\a\\");
      strcpy_s(args[OUTPUT_DIRECTORY_PATH_INDEX], 3u, "a\\");
      strcpy_s(args[ATLAS_WIDTH_INDEX], 2u, "1");
      strcpy_s(args[ATLAS_HEIGHT_INDEX], 2u, "1");
      strcpy_s(args[FONT_SIZES_START_INDEX], 2u, "0");
      REQUIRE_THROWS_AS((CommandLine{ sizeof args / sizeof(char*), args }.validate()), invalid_argument);
    }
    {
      char* args[]{ new char[12u], new char[12u], new char[3u], new char[2u], new char[2u], new char[2u], new char[2u], new char[2u] };
      strcpy_s(args[PROGRAM_NAME_INDEX], 12u, "font-packer");
      strcpy_s(args[INPUT_DIRECTORY_PATH_INDEX], 12u, "res\\test\\a\\");
      strcpy_s(args[OUTPUT_DIRECTORY_PATH_INDEX], 3u, "a\\");
      strcpy_s(args[ATLAS_WIDTH_INDEX], 2u, "1");
      strcpy_s(args[ATLAS_HEIGHT_INDEX], 2u, "1");
      strcpy_s(args[FONT_SIZES_START_INDEX], 2u, "0");
      strcpy_s(args[FONT_SIZES_START_INDEX + 1u], 2u, "0");
      strcpy_s(args[FONT_SIZES_START_INDEX + 2u], 2u, "0");
      REQUIRE_THROWS_AS((CommandLine{ sizeof args / sizeof(char*), args }.validate()), invalid_argument);
    }
    {
      char* args[]{ new char[12u], new char[12u], new char[3u], new char[2u], new char[2u], new char[2u], new char[2u], new char[2u] };
      strcpy_s(args[PROGRAM_NAME_INDEX], 12u, "font-packer");
      strcpy_s(args[INPUT_DIRECTORY_PATH_INDEX], 12u, "res\\test\\a\\");
      strcpy_s(args[OUTPUT_DIRECTORY_PATH_INDEX], 3u, "a\\");
      strcpy_s(args[ATLAS_WIDTH_INDEX], 2u, "1");
      strcpy_s(args[ATLAS_HEIGHT_INDEX], 2u, "1");
      strcpy_s(args[FONT_SIZES_START_INDEX], 2u, "1");
      strcpy_s(args[FONT_SIZES_START_INDEX + 1u], 2u, "1");
      strcpy_s(args[FONT_SIZES_START_INDEX + 2u], 2u, "1");
      REQUIRE_NOTHROW(CommandLine{ sizeof args / sizeof(char*), args }.validate());
    }
    {
      char* args[]{ new char[12u], new char[12u], new char[3u], new char[2u], new char[2u], new char[2u], new char[2u], new char[2u] };
      strcpy_s(args[PROGRAM_NAME_INDEX], 12u, "font-packer");
      strcpy_s(args[INPUT_DIRECTORY_PATH_INDEX], 12u, "res\\test\\j\\");
      strcpy_s(args[OUTPUT_DIRECTORY_PATH_INDEX], 3u, "a\\");
      strcpy_s(args[ATLAS_WIDTH_INDEX], 2u, "1");
      strcpy_s(args[ATLAS_HEIGHT_INDEX], 2u, "1");
      REQUIRE_THROWS_AS((CommandLine{ sizeof args / sizeof(char*), args }.validate()), invalid_argument);
    }
    {
      char* args[]{ new char[12u], new char[12u], new char[3u], new char[2u], new char[2u], new char[2u], new char[2u], new char[2u] };
      strcpy_s(args[PROGRAM_NAME_INDEX], 12u, "font-packer");
      strcpy_s(args[INPUT_DIRECTORY_PATH_INDEX], 12u, "res\\test\\c\\");
      strcpy_s(args[OUTPUT_DIRECTORY_PATH_INDEX], 3u, "a\\");
      strcpy_s(args[ATLAS_WIDTH_INDEX], 2u, "1");
      strcpy_s(args[ATLAS_HEIGHT_INDEX], 2u, "1");
      REQUIRE_THROWS_AS((CommandLine{ sizeof args / sizeof(char*), args }.validate()), invalid_argument);
    }
    {
      char* args[]{ new char[12u], new char[12u], new char[3u], new char[2u], new char[2u], new char[2u] };
      strcpy_s(args[PROGRAM_NAME_INDEX], 12u, "font-packer");
      strcpy_s(args[INPUT_DIRECTORY_PATH_INDEX], 12u, "res\\test\\d\\");
      strcpy_s(args[OUTPUT_DIRECTORY_PATH_INDEX], 3u, "a\\");
      strcpy_s(args[ATLAS_WIDTH_INDEX], 2u, "1");
      strcpy_s(args[ATLAS_HEIGHT_INDEX], 2u, "1");
      strcpy_s(args[FONT_SIZES_START_INDEX], 2u, "1");
      REQUIRE_NOTHROW(CommandLine{ sizeof args / sizeof(char*), args }.validate());
    }
    {
      char* args[]{ new char[12u], new char[12u], new char[3u], new char[2u], new char[2u], new char[2u] };
      strcpy_s(args[PROGRAM_NAME_INDEX], 12u, "font-packer");
      strcpy_s(args[INPUT_DIRECTORY_PATH_INDEX], 12u, "res\\test\\e\\");
      strcpy_s(args[OUTPUT_DIRECTORY_PATH_INDEX], 3u, "a\\");
      strcpy_s(args[ATLAS_WIDTH_INDEX], 2u, "1");
      strcpy_s(args[ATLAS_HEIGHT_INDEX], 2u, "1");
      strcpy_s(args[FONT_SIZES_START_INDEX], 2u, "1");
      REQUIRE_NOTHROW(CommandLine{ sizeof args / sizeof(char*), args }.validate());
    }
    {
      char* args[]{ new char[12u], new char[12u], new char[3u], new char[2u], new char[2u] };
      strcpy_s(args[PROGRAM_NAME_INDEX], 12u, "font-packer");
      strcpy_s(args[INPUT_DIRECTORY_PATH_INDEX], 12u, "res\\test\\f\\");
      strcpy_s(args[OUTPUT_DIRECTORY_PATH_INDEX], 3u, "a\\");
      strcpy_s(args[ATLAS_WIDTH_INDEX], 2u, "1");
      strcpy_s(args[ATLAS_HEIGHT_INDEX], 2u, "1");
      REQUIRE_THROWS_AS((CommandLine{ sizeof args / sizeof(char*), args }.validate()), invalid_argument);
    }
    {
      char* args[]{ new char[12u], new char[12u], new char[3u], new char[2u], new char[2u], new char[2u], new char[2u] };
      strcpy_s(args[PROGRAM_NAME_INDEX], 12u, "font-packer");
      strcpy_s(args[INPUT_DIRECTORY_PATH_INDEX], 12u, "res\\test\\g\\");
      strcpy_s(args[OUTPUT_DIRECTORY_PATH_INDEX], 3u, "a\\");
      strcpy_s(args[ATLAS_WIDTH_INDEX], 2u, "1");
      strcpy_s(args[ATLAS_HEIGHT_INDEX], 2u, "1");
      strcpy_s(args[FONT_SIZES_START_INDEX], 2u, "1");
      strcpy_s(args[FONT_SIZES_START_INDEX + 1u], 2u, "1");
      REQUIRE_NOTHROW(CommandLine{ sizeof args / sizeof(char*), args }.validate());
    }
    {
      char* args[]{ new char[12u], new char[12u], new char[3u], new char[2u], new char[2u], new char[2u], new char[2u] };
      strcpy_s(args[PROGRAM_NAME_INDEX], 12u, "font-packer");
      strcpy_s(args[INPUT_DIRECTORY_PATH_INDEX], 12u, "res\\test\\h\\");
      strcpy_s(args[OUTPUT_DIRECTORY_PATH_INDEX], 3u, "a\\");
      strcpy_s(args[ATLAS_WIDTH_INDEX], 2u, "1");
      strcpy_s(args[ATLAS_HEIGHT_INDEX], 2u, "1");
      strcpy_s(args[FONT_SIZES_START_INDEX], 2u, "1");
      strcpy_s(args[FONT_SIZES_START_INDEX + 1u], 2u, "1");
      REQUIRE_NOTHROW(CommandLine{ sizeof args / sizeof(char*), args }.validate());
    }
    {
      char* args[]{ new char[12u], new char[12u], new char[3u], new char[2u], new char[2u], new char[2u] };
      strcpy_s(args[PROGRAM_NAME_INDEX], 12u, "font-packer");
      strcpy_s(args[INPUT_DIRECTORY_PATH_INDEX], 12u, "res\\test\\i\\");
      strcpy_s(args[OUTPUT_DIRECTORY_PATH_INDEX], 3u, "a\\");
      strcpy_s(args[ATLAS_WIDTH_INDEX], 2u, "1");
      strcpy_s(args[ATLAS_HEIGHT_INDEX], 2u, "1");
      strcpy_s(args[FONT_SIZES_START_INDEX], 2u, "1");
      REQUIRE_NOTHROW(CommandLine{ sizeof args / sizeof(char*), args }.validate());
    }
  }
  remove_all("res/test/j/");
}

}  // namespace ii887522::fontPacker

#endif
