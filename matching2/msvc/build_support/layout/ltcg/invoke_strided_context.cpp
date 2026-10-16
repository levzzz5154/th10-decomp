// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/FUN.cpp_401fd0.cpp"

#pragma code_seg(".text$03context")
int __stdcall InvokeStridedCompilerContext(int count, int cursor, int stride,
                                           int (__fastcall *callback)(int)) {
    return InvokeStridedCallback(count, cursor, stride, callback);
}
#pragma code_seg()
