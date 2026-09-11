// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/FUN_004053d0_004053d0.cpp"

#pragma code_seg(".text$03context")
int __stdcall ObjectField3CGetterCompilerContext(ManagedObject** objects, int count) {
    int total = 0;
    for (int index = 0; index < count; ++index) {
        total += ManagedObject_GetField3C(objects[index]);
    }
    return total;
}
#pragma code_seg()
