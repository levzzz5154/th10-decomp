typedef void* (__stdcall* D3DXMatrixRotationXFn_004521ac)(
    void* out, float angle);
extern "C" D3DXMatrixRotationXFn_004521ac imp_D3DXMatrixRotationX;

// 0x004521AC..0x004521B1: imported D3DXMatrixRotationX tail thunk.
// The typed stdcall import slot produces the retail six-byte indirect jump.
extern "C" void* __stdcall asm_D3DXMatrixRotationX_004521ac(
    void* out, float angle) {
    return imp_D3DXMatrixRotationX(out, angle);
}
