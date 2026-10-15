#include "../../../build_support/include/asm_encoding.hpp"
#include "../../../build_support/include/asm_symbols.hpp"

// 0x0042C5B0: the only slot of the title's info vtable (0x0046ECF0):
// the manager's allocation size, 0x5ACC bytes (allocated by 0x0042CD50).
// Constant leaf: the size of one fixed pool, handed back in EAX.
int Title_GetSize() {
    return 23244;
}
