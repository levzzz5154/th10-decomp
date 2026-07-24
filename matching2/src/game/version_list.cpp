#include "th10/game/version_list.hpp"

#include <cstdio>
#include <cstring>

// 0x00420DD0 - Match a tag and integer pair against the version list.
// Retail also inlines a constant comparison of the strings "0100a" and
// "debug" (never equal, so the branch is dead) before scanning; only
// the strncmp(tag, "debug", 5) early-out is observable. The cursor
// walks line by line with the CRT strchr (retail 0x00452730),
// recomputing the remaining byte count exactly like the retail
// pointer arithmetic.
int32_t VersionList_Match(const VersionList* list, const char* tag,
                          int32_t first, int32_t second) {
    const char* cursor = list->text;
    if (cursor == 0) {
        return 0;
    }
    int32_t remaining = list->length;
    if (strncmp(tag, "debug", 5) == 0) {
        return 0;
    }
    for (;;) {
        if (remaining == 0) {
            return -1;
        }
        if (strncmp(tag, cursor, 5) == 0) {
            int parsed_first = 0;
            int parsed_second = 0;
            sscanf(cursor + 6, "%d %d", &parsed_first, &parsed_second);
            if (parsed_first == first && parsed_second == second) {
                return 0;
            }
        }
        const char* newline = strchr(cursor, '\n');
        remaining = (int32_t)((cursor + remaining) - (newline + 1));
        cursor = newline + 1;
    }
}
