typedef void* (__stdcall* D3DXMatrixRotationYFn_004521b8)(
    void* out, float angle);
extern "C" D3DXMatrixRotationYFn_004521b8 imp_D3DXMatrixRotationY;

// 0x004521B8..0x004521BD: imported D3DXMatrixRotationY tail thunk.
// The typed stdcall import slot produces the retail six-byte indirect jump.
extern "C" void* __stdcall asm_D3DXMatrixRotationY_004521b8(
    void* out, float angle) {
    return imp_D3DXMatrixRotationY(out, angle);
}
