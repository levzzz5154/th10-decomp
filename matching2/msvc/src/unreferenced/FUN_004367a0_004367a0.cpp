#include "../../build_support/include/asm_encoding.hpp"
#include "../../build_support/include/asm_symbols.hpp"
#include <string.h>

// 0x004367A0..0x004367C2: FUN_004367a0
// Bulk copy of a run-time sized block that hands back the destination. The
// compiler expands the intrinsic memcpy to the retail doubleword/byte rep movs
// pair and forwards the intrinsic's own result.
void* __cdecl FUN_004367a0_004367a0(void* destination, const void* source, unsigned int size) {
    return memcpy(destination, source, size);
}
