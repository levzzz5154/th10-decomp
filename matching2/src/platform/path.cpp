#include "th10/platform/file.hpp"

// Clean conventional-ABI form of 0x004356D0.
const char* File_AfterFirstSlash(const char* path) {
    const char* cursor = path;
    while (*cursor != 0) {
        if (*cursor == '/') {
            return cursor + 1;
        }
        ++cursor;
    }
    return path;
}
