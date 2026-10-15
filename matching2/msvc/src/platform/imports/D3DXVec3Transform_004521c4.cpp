// D3DXVec3Transform is the three-pointer stdcall import thunk.  Calling the
// typed import slot directly gives MSVC 13.10 the original six-byte indirect
// jump while preserving the D3DX ABI and its decorated public symbol.
typedef void* (__stdcall *D3DXVec3TransformImport_004521c4)(
    void* out, const void* vector, const void* matrix);
extern "C" D3DXVec3TransformImport_004521c4 data_004662cc;

// 0x004521C4..0x004521C9: imported D3DXVec3Transform tail thunk.
extern "C" void* __stdcall D3DXVec3Transform(
    void* out, const void* vector, const void* matrix) {
    return data_004662cc(out, vector, matrix);
}
