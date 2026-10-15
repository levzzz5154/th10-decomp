// 0x0045218E..0x00452193: the D3DXVec3Project import thunk.
//
// The retail entry is the stdcall six-argument import tail jump.  The
// executable's fixed import slot is declared as a typed function pointer so
// MSVC can emit a readable tail call through that slot.
typedef void* (__stdcall *D3DXVec3ProjectImport_0045218e)(
    void* out, const void* vector, const void* viewport,
    const void* projection, const void* view, const void* world);

extern "C" D3DXVec3ProjectImport_0045218e imp_D3DXVec3Project;

extern "C" void* __stdcall D3DXVec3Project_0045218e(
    void* out, const void* vector, const void* viewport,
    const void* projection, const void* view, const void* world) {
    return imp_D3DXVec3Project(out, vector, viewport, projection, view, world);
}
