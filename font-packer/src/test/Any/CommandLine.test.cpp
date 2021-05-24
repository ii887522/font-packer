// Copyright ii887522

#ifdef TEST

#include "CommandLine.test.h"
#include <cassert>
#include <stdexcept>
#include <cstring>
#include "../../main/Any/constants.h"
#include "../../main/Any/CommandLine.h"

using std::invalid_argument;

namespace ii887522::fontPacker {

static void testValidate() {
  try {
    char* args[]{ new char[12u] };
    strcpy_s(args[PROGRAM_NAME_INDEX], 12u, "font-packer");
    CommandLine{ sizeof args / sizeof(char*), args }.getAtlasSize();
  } catch (const invalid_argument&) {
    try {
      char* args[]{ new char[12u], new char[2u] };
      strcpy_s(args[PROGRAM_NAME_INDEX], 12u, "font-packer");
      strcpy_s(args[INPUT_DIRECTORY_PATH_INDEX], 2u, "a");
      CommandLine{ sizeof args / sizeof(char*), args }.getAtlasSize();
    } catch (const invalid_argument&) {
      try {
        char* args[]{ new char[12u], new char[2u], new char[2u], new char[2u], new char[2u], new char[2u] };
        strcpy_s(args[PROGRAM_NAME_INDEX], 12u, "font-packer");
        strcpy_s(args[INPUT_DIRECTORY_PATH_INDEX], 2u, "a");
        strcpy_s(args[OUTPUT_DIRECTORY_PATH_INDEX], 2u, "a");
        strcpy_s(args[ATLAS_WIDTH_INDEX], 2u, "a");
        strcpy_s(args[ATLAS_HEIGHT_INDEX], 2u, "a");
        strcpy_s(args[FONT_SIZES_START_INDEX], 2u, "a");
        CommandLine{ sizeof args / sizeof(char*), args }.getAtlasSize();
      } catch (const invalid_argument&) {
        try {
          char* args[]{ new char[12u], new char[2u], new char[2u], new char[2u], new char[2u], new char[2u] };
          strcpy_s(args[PROGRAM_NAME_INDEX], 12u, "font-packer");
          strcpy_s(args[INPUT_DIRECTORY_PATH_INDEX], 2u, "a");
          strcpy_s(args[OUTPUT_DIRECTORY_PATH_INDEX], 2u, "a");
          strcpy_s(args[ATLAS_WIDTH_INDEX], 2u, "0");
          strcpy_s(args[ATLAS_HEIGHT_INDEX], 2u, "a");
          strcpy_s(args[FONT_SIZES_START_INDEX], 2u, "a");
          CommandLine{ sizeof args / sizeof(char*), args }.getAtlasSize();
        } catch (const invalid_argument&) {
          try {
            char* args[]{ new char[12u], new char[2u], new char[2u], new char[2u], new char[2u], new char[2u] };
            strcpy_s(args[PROGRAM_NAME_INDEX], 12u, "font-packer");
            strcpy_s(args[INPUT_DIRECTORY_PATH_INDEX], 2u, "a");
            strcpy_s(args[OUTPUT_DIRECTORY_PATH_INDEX], 2u, "a");
            strcpy_s(args[ATLAS_WIDTH_INDEX], 2u, "0");
            strcpy_s(args[ATLAS_HEIGHT_INDEX], 2u, "0");
            strcpy_s(args[FONT_SIZES_START_INDEX], 2u, "a");
            CommandLine{ sizeof args / sizeof(char*), args }.getAtlasSize();
          } catch (const invalid_argument&) {
            try {
              char* args[]{ new char[12u], new char[2u], new char[2u], new char[2u], new char[2u], new char[2u] };
              strcpy_s(args[PROGRAM_NAME_INDEX], 12u, "font-packer");
              strcpy_s(args[INPUT_DIRECTORY_PATH_INDEX], 2u, "a");
              strcpy_s(args[OUTPUT_DIRECTORY_PATH_INDEX], 2u, "a");
              strcpy_s(args[ATLAS_WIDTH_INDEX], 2u, "0");
              strcpy_s(args[ATLAS_HEIGHT_INDEX], 2u, "0");
              strcpy_s(args[FONT_SIZES_START_INDEX], 2u, "a");
              CommandLine{ sizeof args / sizeof(char*), args }.getAtlasSize();
            } catch (const invalid_argument&) {
              try {
                char* args[]{ new char[12u], new char[2u], new char[2u], new char[2u], new char[2u], new char[2u] };
                strcpy_s(args[PROGRAM_NAME_INDEX], 12u, "font-packer");
                strcpy_s(args[INPUT_DIRECTORY_PATH_INDEX], 2u, "a");
                strcpy_s(args[OUTPUT_DIRECTORY_PATH_INDEX], 2u, "a");
                strcpy_s(args[ATLAS_WIDTH_INDEX], 2u, "0");
                strcpy_s(args[ATLAS_HEIGHT_INDEX], 2u, "0");
                strcpy_s(args[FONT_SIZES_START_INDEX], 2u, "0");
                CommandLine{ sizeof args / sizeof(char*), args }.validate();
              } catch (const invalid_argument&) {
                try {
                  char* args[]{ new char[12u], new char[3u], new char[2u], new char[2u], new char[2u], new char[2u] };
                  strcpy_s(args[PROGRAM_NAME_INDEX], 12u, "font-packer");
                  strcpy_s(args[INPUT_DIRECTORY_PATH_INDEX], 3u, "a/");
                  strcpy_s(args[OUTPUT_DIRECTORY_PATH_INDEX], 2u, "a");
                  strcpy_s(args[ATLAS_WIDTH_INDEX], 2u, "0");
                  strcpy_s(args[ATLAS_HEIGHT_INDEX], 2u, "0");
                  strcpy_s(args[FONT_SIZES_START_INDEX], 2u, "0");
                  CommandLine{ sizeof args / sizeof(char*), args }.validate();
                } catch (const invalid_argument&) {
                  try {
                    char* args[]{ new char[12u], new char[3u], new char[2u], new char[2u], new char[2u], new char[2u] };
                    strcpy_s(args[PROGRAM_NAME_INDEX], 12u, "font-packer");
                    strcpy_s(args[INPUT_DIRECTORY_PATH_INDEX], 3u, "a\\");
                    strcpy_s(args[OUTPUT_DIRECTORY_PATH_INDEX], 2u, "a");
                    strcpy_s(args[ATLAS_WIDTH_INDEX], 2u, "0");
                    strcpy_s(args[ATLAS_HEIGHT_INDEX], 2u, "0");
                    strcpy_s(args[FONT_SIZES_START_INDEX], 2u, "0");
                    CommandLine{ sizeof args / sizeof(char*), args }.validate();
                  } catch (const invalid_argument&) {
                    try {
                      char* args[]{ new char[12u], new char[12u], new char[2u], new char[2u], new char[2u], new char[2u] };
                      strcpy_s(args[PROGRAM_NAME_INDEX], 12u, "font-packer");
                      strcpy_s(args[INPUT_DIRECTORY_PATH_INDEX], 12u, "res\\test\\a\\");
                      strcpy_s(args[OUTPUT_DIRECTORY_PATH_INDEX], 2u, "a");
                      strcpy_s(args[ATLAS_WIDTH_INDEX], 2u, "0");
                      strcpy_s(args[ATLAS_HEIGHT_INDEX], 2u, "0");
                      strcpy_s(args[FONT_SIZES_START_INDEX], 2u, "0");
                      CommandLine{ sizeof args / sizeof(char*), args }.validate();
                    } catch (const invalid_argument&) {
                      try {
                        char* args[]{ new char[12u], new char[12u], new char[3u], new char[2u], new char[2u], new char[2u] };
                        strcpy_s(args[PROGRAM_NAME_INDEX], 12u, "font-packer");
                        strcpy_s(args[INPUT_DIRECTORY_PATH_INDEX], 12u, "res\\test\\a\\");
                        strcpy_s(args[OUTPUT_DIRECTORY_PATH_INDEX], 3u, "a/");
                        strcpy_s(args[ATLAS_WIDTH_INDEX], 2u, "0");
                        strcpy_s(args[ATLAS_HEIGHT_INDEX], 2u, "0");
                        strcpy_s(args[FONT_SIZES_START_INDEX], 2u, "0");
                        CommandLine{ sizeof args / sizeof(char*), args }.validate();
                      } catch (const invalid_argument&) {
                        try {
                          char* args[]{ new char[12u], new char[12u], new char[3u], new char[2u], new char[2u], new char[2u] };
                          strcpy_s(args[PROGRAM_NAME_INDEX], 12u, "font-packer");
                          strcpy_s(args[INPUT_DIRECTORY_PATH_INDEX], 12u, "res\\test\\a\\");
                          strcpy_s(args[OUTPUT_DIRECTORY_PATH_INDEX], 3u, "a\\");
                          strcpy_s(args[ATLAS_WIDTH_INDEX], 2u, "0");
                          strcpy_s(args[ATLAS_HEIGHT_INDEX], 2u, "0");
                          strcpy_s(args[FONT_SIZES_START_INDEX], 2u, "0");
                          CommandLine{ sizeof args / sizeof(char*), args }.validate();
                        } catch (const invalid_argument&) {
                          try {
                            char* args[]{ new char[12u], new char[12u], new char[3u], new char[2u], new char[2u], new char[2u] };
                            strcpy_s(args[PROGRAM_NAME_INDEX], 12u, "font-packer");
                            strcpy_s(args[INPUT_DIRECTORY_PATH_INDEX], 12u, "res\\test\\a\\");
                            strcpy_s(args[OUTPUT_DIRECTORY_PATH_INDEX], 3u, "a\\");
                            strcpy_s(args[ATLAS_WIDTH_INDEX], 2u, "1");
                            strcpy_s(args[ATLAS_HEIGHT_INDEX], 2u, "0");
                            strcpy_s(args[FONT_SIZES_START_INDEX], 2u, "0");
                            CommandLine{ sizeof args / sizeof(char*), args }.validate();
                          } catch (const invalid_argument&) {
                            try {
                              char* args[]{ new char[12u], new char[12u], new char[3u], new char[2u], new char[2u], new char[2u] };
                              strcpy_s(args[PROGRAM_NAME_INDEX], 12u, "font-packer");
                              strcpy_s(args[INPUT_DIRECTORY_PATH_INDEX], 12u, "res\\test\\a\\");
                              strcpy_s(args[OUTPUT_DIRECTORY_PATH_INDEX], 3u, "a\\");
                              strcpy_s(args[ATLAS_WIDTH_INDEX], 2u, "1");
                              strcpy_s(args[ATLAS_HEIGHT_INDEX], 2u, "1");
                              strcpy_s(args[FONT_SIZES_START_INDEX], 2u, "0");
                              CommandLine{ sizeof args / sizeof(char*), args }.validate();
                            } catch (const invalid_argument&) {
                              try {
                                char* args[]{ new char[12u], new char[12u], new char[3u], new char[2u], new char[2u], new char[2u], new char[2u], new char[2u] };
                                strcpy_s(args[PROGRAM_NAME_INDEX], 12u, "font-packer");
                                strcpy_s(args[INPUT_DIRECTORY_PATH_INDEX], 12u, "res\\test\\a\\");
                                strcpy_s(args[OUTPUT_DIRECTORY_PATH_INDEX], 3u, "a\\");
                                strcpy_s(args[ATLAS_WIDTH_INDEX], 2u, "1");
                                strcpy_s(args[ATLAS_HEIGHT_INDEX], 2u, "1");
                                strcpy_s(args[FONT_SIZES_START_INDEX], 2u, "0");
                                strcpy_s(args[FONT_SIZES_START_INDEX + 1u], 2u, "0");
                                strcpy_s(args[FONT_SIZES_START_INDEX + 1u], 2u, "0");
                                CommandLine{ sizeof args / sizeof(char*), args }.validate();
                              } catch (const invalid_argument&) {
                                try {
                                  char* args[]{ new char[12u], new char[12u], new char[3u], new char[2u], new char[2u], new char[2u], new char[2u], new char[2u] };
                                  strcpy_s(args[PROGRAM_NAME_INDEX], 12u, "font-packer");
                                  strcpy_s(args[INPUT_DIRECTORY_PATH_INDEX], 12u, "res\\test\\a\\");
                                  strcpy_s(args[OUTPUT_DIRECTORY_PATH_INDEX], 3u, "a\\");
                                  strcpy_s(args[ATLAS_WIDTH_INDEX], 2u, "1");
                                  strcpy_s(args[ATLAS_HEIGHT_INDEX], 2u, "1");
                                  strcpy_s(args[FONT_SIZES_START_INDEX], 2u, "1");
                                  strcpy_s(args[FONT_SIZES_START_INDEX + 1u], 2u, "1");
                                  strcpy_s(args[FONT_SIZES_START_INDEX + 1u], 2u, "1");
                                  CommandLine{ sizeof args / sizeof(char*), args }.validate();
                                } catch (const invalid_argument&) {
                                  return;
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  assert(false);
}

void testCommandLine() {
  testValidate();
}

}  // namespace ii887522::fontPacker

#endif
