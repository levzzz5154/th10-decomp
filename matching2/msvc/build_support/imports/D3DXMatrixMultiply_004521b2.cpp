typedef void (__stdcall* D3DXMatrixMultiplyFn_004521b2)(
    void* out, const void* left, const void* right);
extern "C" D3DXMatrixMultiplyFn_004521b2 data_004662d8;

// 0x004521B2..0x004521B7: imported D3DXMatrixMultiply tail thunk.
// Ghidra identifies this as a six-byte JMP through the D3DX import slot at
// 0x004662D8.  The stdcall prototype preserves the three matrix pointers and
// lets MSVC emit the same indirect tail call without inline assembly.
extern "C" void __stdcall asm_D3DXMatrixMultiply_004521b2(
    void* out, const void* left, const void* right) {
    data_004662d8(out, left, right);
}
