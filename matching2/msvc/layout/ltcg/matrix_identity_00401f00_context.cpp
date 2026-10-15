// Compiler context only; never selected as recovered game code.
#include "../../src/unreferenced/unassigned_00401f00.cpp"

#pragma code_seg(".text$03context")
int __stdcall MatrixIdentityCompilerContext(Matrix4x4** matrices, int count) {
    Matrix4x4** cursor = matrices;
    while (count--) {
        Matrix4x4* matrix = *cursor++;
        matrix->SetIdentity();
        matrix->SetIdentity();
    }
    return 0;
}
#pragma code_seg()
