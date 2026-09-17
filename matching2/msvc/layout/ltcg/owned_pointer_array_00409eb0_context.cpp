#include "../../src/unidentified/FUN_00409eb0_00409eb0.cpp"
#pragma code_seg(".text$03context")
int __stdcall OwnedPointerArray00409eb0CompilerContext(OwnedPointerArray_00409eb0** arrays, int count) {
    while (count--) { OwnedPointerArray_00409eb0* array = *arrays++; array->Clear(); array->Clear(); }
    return 0;
}
#pragma code_seg()
