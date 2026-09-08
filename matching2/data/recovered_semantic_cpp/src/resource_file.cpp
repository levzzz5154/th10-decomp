#include "th10/platform/memory_file.hpp"

__declspec(noinline) ResourceFile::~ResourceFile() {
    Close();
}

