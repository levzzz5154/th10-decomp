#pragma once

#ifdef _MSC_VER
#include "th10/msvc_stdint.hpp"
#else
#include <cstdint>
#endif

// Loaded version-list text (retail fields at +0x764 / +0x760 of the
// owning object).
struct VersionList {
    const char* text;  // +0x764, newline-separated "tagNN d d" lines
    int32_t length;    // +0x760, bytes remaining in the buffer
};

// 0x00420DD0 - Match a five-character tag with two integers against the
// version list. Returns 0 when the list is missing, when the tag starts
// with "debug", or when a line starting with the tag parses (via
// sscanf "%d %d" after the 6-byte prefix) to the exact integer pair;
// returns -1 when the list is exhausted without a match. Lines are
// separated by '\n'.
int32_t VersionList_Match(const VersionList* list, const char* tag,
                          int32_t first, int32_t second);
