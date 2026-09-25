#include <stddef.h>
#include <string.h>

// Retail 0x00435280..0x004352B2 receives the cursor address in EDX.
extern "C" char* __cdecl AdvancePastAlignedString_00435280(char** cursor) {
    const size_t bytes_with_terminator = strlen(*cursor) + 1;
    const size_t padded_bytes = (bytes_with_terminator + 3) & ~size_t(3);
    *cursor += padded_bytes;
    return *cursor;
}
