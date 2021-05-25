// Copyright ii887522

#ifdef TEST

#define ALLOCATOR_IMPLEMENTATIONS
#include <nitro/Any/allocator.h>

#include "cli_ext.test.h"
#include "../Any/CommandLine.test.h"
#include "util.test.h"  // NOLINT(build/include_subdir)

namespace ii887522::fontPacker {

static int main() {
  testCliExt();
  testCommandLine();
  testUtil();
  return EXIT_SUCCESS;
}

}  // namespace ii887522::fontPacker

int main() {
  return ii887522::fontPacker::main();
}

#endif
