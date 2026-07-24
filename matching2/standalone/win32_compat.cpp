#include <cstdlib>

// The recovered MSVC sources name the CRT entry points as `_malloc`/`_free`.
// MinGW exposes the standard spellings, so keep the source ABI stable through
// this narrow PE32 bridge.
extern "C" void* _malloc(unsigned int size) {
    return std::malloc(size);
}

extern "C" void _free(void* memory) {
    std::free(memory);
}
