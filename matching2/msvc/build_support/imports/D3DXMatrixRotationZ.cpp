typedef void* (__stdcall* D3DXMatrixRotationZFn_004521be)(
    void* out, float angle);
extern "C" D3DXMatrixRotationZFn_004521be imp_D3DXMatrixRotationZ;
// The fixed-address thunk is an undecorated cdecl symbol in the legacy
// manifest.  Calling through a cdecl view lets MSVC tail-call the typed slot;
// the slot itself remains the stdcall D3DX ABI and the emitted body is the
// direct six-byte import jump.
typedef void* (__cdecl* D3DXMatrixRotationZTailFn_004521be)(
    void* out, float angle);
// 0x004521BE..0x004521C3: imported D3DXMatrixRotationZ tail thunk.
// The typed stdcall import slot produces the retail six-byte indirect jump.
extern "C" void* __cdecl asm_D3DXMatrixRotationZ_004521be(
    void* out, float angle) {
    return ((D3DXMatrixRotationZTailFn_004521be)imp_D3DXMatrixRotationZ)(out, angle);
}
