// Compiler context only; never selected as recovered game code.
#include "../../src/unreferenced/FUN_0042a9d0_0042a9d0.cpp"

#pragma code_seg(".text$03context")
int __stdcall H3801CompilerContext_0042a9d0(WordLoad_0042a9d0** items, int count) {
    int result = 0;
    while (count--) {
        WordLoad_0042a9d0* object = *items++;
        result += object->Load();
        result += object->Load();
    }
    return result;
}
#pragma code_seg()
