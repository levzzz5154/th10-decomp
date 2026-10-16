#include <cstdint>

// Semantic model of the CRT __store_str helper at 0x0045A75E.
//
// The retail entry point is not callable through an ordinary C++ prototype:
// ECX is the address of the output cursor, EDX is the source string, and EAX
// is the address of the remaining-capacity counter.  Keep this typed model
// separate until its caller can use the same explicit interface.
extern "C" void semantic_store_str(
    char** output_cursor,
    std::uint32_t* remaining_capacity,
    const char* source) {
    while (*remaining_capacity != 0 && *source != '\0') {
        **output_cursor = *source;
        ++*output_cursor;
        ++source;
        --*remaining_capacity;
    }
}
