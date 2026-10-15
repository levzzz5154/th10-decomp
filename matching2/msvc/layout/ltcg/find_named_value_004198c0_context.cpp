// Compiler context only; never selected as recovered game code.
#include "../../src/game/hint/named_value_lookup_004198c0.cpp"
#pragma code_seg(".text$03context")
int __stdcall FindNamedValueContext_004198c0(
        const char** names, NamedValue_004198c0* table, int count) {
    int total = 0;
    for (int index = 0; index < count; ++index)
        total += FindNamedValue_004198c0(names[index], table, 0x3d) +
                 FindNamedValue_004198c0(names[index], table + 5, 3);
    return total;
}
#pragma code_seg()
