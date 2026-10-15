// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/FUN_00405390_00405390.cpp"

#pragma code_seg(".text$03context")
int __stdcall ObjectField04GetterCompilerContext(ManagedObject** objects, int count) {
    int total = 0;
    for (int index = 0; index < count; ++index) {
        total += ManagedObject_GetField04(objects[index]);
    }
    return total;
}
#pragma code_seg()
