// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/FUN.cpp_405360.cpp"

#pragma code_seg(".text$03context")
int __stdcall ObjectInterfaceGetterCompilerContext(ManagedObject** objects, int count, void** out) {
    for (int index = 0; index < count; ++index) {
        out[index] = ManagedObject_GetInterface(objects[index]);
    }
    return 0;
}
#pragma code_seg()
