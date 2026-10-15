#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include <stddef.h>

// 0x004367D0..0x004367D4: memmove forwarding thunk.
extern "C" void* __cdecl asm_unassigned_004367d0(
        void* destination, const void* source, unsigned int size) {
    typedef void* (__cdecl *MemmoveFn)(void*, const void*, size_t);
    return ((MemmoveFn)asm_memmove_00453280)(destination, source, size);
}
