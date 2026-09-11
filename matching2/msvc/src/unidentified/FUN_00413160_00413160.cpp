#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00413160..0x00413169: FUN_00413160
// The value arrives on the stack and the object in ECX, so this is a
// __thiscall setter; retail stores it at +0x18 and returns the same value.
struct Object00413160 {
    int pad_000[6];
    int value;   // +0x18

    int SetValue(int new_value);
};

int Object00413160::SetValue(int new_value) {
    value = new_value;
    return new_value;
}
