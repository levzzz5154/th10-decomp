typedef void* (__stdcall* D3DXMatrixTranslationFn_00452182)(
    void* out, float x, float y, float z);
extern "C" D3DXMatrixTranslationFn_00452182 imp_D3DXMatrixTranslation;

// 0x00452182..0x00452187: imported D3DXMatrixTranslation tail thunk.
// The stdcall import slot preserves the native D3DX ABI while the cdecl
// view keeps this fixed-address legacy symbol undecorated.
typedef void* (__cdecl* D3DXMatrixTranslationTailFn_00452182)(
    void* out, float x, float y, float z);
extern "C" void* __cdecl asm_D3DXMatrixTranslation_00452182(
    void* out, float x, float y, float z) {
    return ((D3DXMatrixTranslationTailFn_00452182)imp_D3DXMatrixTranslation)(out, x, y, z);
}
