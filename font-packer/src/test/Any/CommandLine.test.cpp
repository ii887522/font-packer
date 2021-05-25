// Copyright ii887522

#ifdef TEST

#include "CommandLine.test.h"
#include <cassert>
#include <stdexcept>
#include <cstring>
#include <filesystem>
#include "../../main/Any/constants.h"
#include "../../main/Any/CommandLine.h"

using std::invalid_argument;
using std::filesystem::create_directory;
using std::filesystem::remove_all;

namespace ii887522::fontPacker {

static void init() {
  create_directory("res/test/j/");
}

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
                                strcpy_s(args[FONT_SIZES_START_INDEX + 2u], 2u, "0");
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
                                  strcpy_s(args[FONT_SIZES_START_INDEX + 2u], 2u, "1");
                                  CommandLine{ sizeof args / sizeof(char*), args }.validate();
                                } catch (const invalid_argument&) {
                                  assert(false);
                                }
                                try {
                                  char* args[]{ new char[12u], new char[12u], new char[3u], new char[2u], new char[2u], new char[2u], new char[2u], new char[2u] };
                                  strcpy_s(args[PROGRAM_NAME_INDEX], 12u, "font-packer");
                                  strcpy_s(args[INPUT_DIRECTORY_PATH_INDEX], 12u, "res\\test\\j\\");
                                  strcpy_s(args[OUTPUT_DIRECTORY_PATH_INDEX], 3u, "a\\");
                                  strcpy_s(args[ATLAS_WIDTH_INDEX], 2u, "1");
                                  strcpy_s(args[ATLAS_HEIGHT_INDEX], 2u, "1");
                                  CommandLine{ sizeof args / sizeof(char*), args }.validate();
                                } catch (const invalid_argument&) {
                                  try {
                                    char* args[]{ new char[12u], new char[12u], new char[3u], new char[2u], new char[2u], new char[2u], new char[2u], new char[2u] };
                                    strcpy_s(args[PROGRAM_NAME_INDEX], 12u, "font-packer");
                                    strcpy_s(args[INPUT_DIRECTORY_PATH_INDEX], 12u, "res\\test\\c\\");
                                    strcpy_s(args[OUTPUT_DIRECTORY_PATH_INDEX], 3u, "a\\");
                                    strcpy_s(args[ATLAS_WIDTH_INDEX], 2u, "1");
                                    strcpy_s(args[ATLAS_HEIGHT_INDEX], 2u, "1");
                                    CommandLine{ sizeof args / sizeof(char*), args }.validate();
                                  } catch (const invalid_argument&) {
                                    try {
                                      char* args[]{ new char[12u], new char[12u], new char[3u], new char[2u], new char[2u], new char[2u] };
                                      strcpy_s(args[PROGRAM_NAME_INDEX], 12u, "font-packer");
                                      strcpy_s(args[INPUT_DIRECTORY_PATH_INDEX], 12u, "res\\test\\d\\");
                                      strcpy_s(args[OUTPUT_DIRECTORY_PATH_INDEX], 3u, "a\\");
                                      strcpy_s(args[ATLAS_WIDTH_INDEX], 2u, "1");
                                      strcpy_s(args[ATLAS_HEIGHT_INDEX], 2u, "1");
                                      strcpy_s(args[FONT_SIZES_START_INDEX], 2u, "1");
                                      CommandLine{ sizeof args / sizeof(char*), args }.validate();
                                    } catch (const invalid_argument&) {
                                      assert(false);
                                    }
                                    try {
                                      char* args[]{ new char[12u], new char[12u], new char[3u], new char[2u], new char[2u], new char[2u] };
                                      strcpy_s(args[PROGRAM_NAME_INDEX], 12u, "font-packer");
                                      strcpy_s(args[INPUT_DIRECTORY_PATH_INDEX], 12u, "res\\test\\e\\");
                                      strcpy_s(args[OUTPUT_DIRECTORY_PATH_INDEX], 3u, "a\\");
                                      strcpy_s(args[ATLAS_WIDTH_INDEX], 2u, "1");
                                      strcpy_s(args[ATLAS_HEIGHT_INDEX], 2u, "1");
                                      strcpy_s(args[FONT_SIZES_START_INDEX], 2u, "1");
                                      CommandLine{ sizeof args / sizeof(char*), args }.validate();
                                    } catch (const invalid_argument&) {
                                      assert(false);
                                    }
                                    try {
                                      char* args[]{ new char[12u], new char[12u], new char[3u], new char[2u], new char[2u] };
                                      strcpy_s(args[PROGRAM_NAME_INDEX], 12u, "font-packer");
                                      strcpy_s(args[INPUT_DIRECTORY_PATH_INDEX], 12u, "res\\test\\f\\");
                                      strcpy_s(args[OUTPUT_DIRECTORY_PATH_INDEX], 3u, "a\\");
                                      strcpy_s(args[ATLAS_WIDTH_INDEX], 2u, "1");
                                      strcpy_s(args[ATLAS_HEIGHT_INDEX], 2u, "1");
                                      CommandLine{ sizeof args / sizeof(char*), args }.validate();
                                    } catch (const invalid_argument&) {
                                      try {
                                        char* args[]{ new char[12u], new char[12u], new char[3u], new char[2u], new char[2u], new char[2u], new char[2u] };
                                        strcpy_s(args[PROGRAM_NAME_INDEX], 12u, "font-packer");
                                        strcpy_s(args[INPUT_DIRECTORY_PATH_INDEX], 12u, "res\\test\\g\\");
                                        strcpy_s(args[OUTPUT_DIRECTORY_PATH_INDEX], 3u, "a\\");
                                        strcpy_s(args[ATLAS_WIDTH_INDEX], 2u, "1");
                                        strcpy_s(args[ATLAS_HEIGHT_INDEX], 2u, "1");
                                        strcpy_s(args[FONT_SIZES_START_INDEX], 2u, "1");
                                        strcpy_s(args[FONT_SIZES_START_INDEX + 1u], 2u, "1");
                                        CommandLine{ sizeof args / sizeof(char*), args }.validate();
                                      } catch (const invalid_argument&) {
                                        assert(false);
                                      }
                                      try {
                                        char* args[]{ new char[12u], new char[12u], new char[3u], new char[2u], new char[2u], new char[2u], new char[2u] };
                                        strcpy_s(args[PROGRAM_NAME_INDEX], 12u, "font-packer");
                                        strcpy_s(args[INPUT_DIRECTORY_PATH_INDEX], 12u, "res\\test\\h\\");
                                        strcpy_s(args[OUTPUT_DIRECTORY_PATH_INDEX], 3u, "a\\");
                                        strcpy_s(args[ATLAS_WIDTH_INDEX], 2u, "1");
                                        strcpy_s(args[ATLAS_HEIGHT_INDEX], 2u, "1");
                                        strcpy_s(args[FONT_SIZES_START_INDEX], 2u, "1");
                                        strcpy_s(args[FONT_SIZES_START_INDEX + 1u], 2u, "1");
                                        CommandLine{ sizeof args / sizeof(char*), args }.validate();
                                      } catch (const invalid_argument&) {
                                        assert(false);
                                      }
                                      try {
                                        char* args[]{ new char[12u], new char[12u], new char[3u], new char[2u], new char[2u], new char[2u] };
                                        strcpy_s(args[PROGRAM_NAME_INDEX], 12u, "font-packer");
                                        strcpy_s(args[INPUT_DIRECTORY_PATH_INDEX], 12u, "res\\test\\i\\");
                                        strcpy_s(args[OUTPUT_DIRECTORY_PATH_INDEX], 3u, "a\\");
                                        strcpy_s(args[ATLAS_WIDTH_INDEX], 2u, "1");
                                        strcpy_s(args[ATLAS_HEIGHT_INDEX], 2u, "1");
                                        strcpy_s(args[FONT_SIZES_START_INDEX], 2u, "1");
                                        CommandLine{ sizeof args / sizeof(char*), args }.validate();
                                      } catch (const invalid_argument&) {
                                        assert(false);
                                      }
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
    }
  }
  assert(false);
}

static void free() {
  remove_all("res/test/j/");
}

void testCommandLine() {
  init();
  testValidate();
  free();
}

}  // namespace ii887522::fontPacker

#endif
