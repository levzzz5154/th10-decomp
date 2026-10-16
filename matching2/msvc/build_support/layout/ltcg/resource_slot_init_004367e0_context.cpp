// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/FUN.cpp_4367e0.cpp"

#pragma code_seg(".text$03context")
int __stdcall InitCompilerContext(ResourceSlotInit** items, int count, int value) {
    while (count--) {
        (*items++)->Init(value);
    }
    return 0;
}
#pragma code_seg()
