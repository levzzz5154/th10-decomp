#include "asm_symbols.hpp"

// 0x004525A1..0x004525CF: __ArrayUnwind
// The runtime passes the current element cursor, the element stride, the
// number of already-constructed elements, and the element destructor.
extern "C" void __stdcall ArrayUnwind_004525A1(
    void* current_element,
    unsigned int element_stride,
    int constructed_count,
    ArrayElementDestructor_004525A1 destroy_element) {
    unsigned char* cursor = static_cast<unsigned char*>(current_element);
    unsigned int remaining = static_cast<unsigned int>(constructed_count);

    // The retail loop decrements the signed count before testing its sign.
    // Express the x86 sign test with the high bit so decrement wraps exactly
    // as a 32-bit integer operation, including for unusual negative inputs.
    for (;;) {
        --remaining;
        if ((remaining & 0x80000000u) != 0) {
            break;
        }

        cursor -= element_stride;
        destroy_element(cursor);
    }
}
