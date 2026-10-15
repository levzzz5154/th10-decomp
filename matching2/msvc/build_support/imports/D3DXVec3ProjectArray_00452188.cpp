
// D3DXVec3ProjectArray is the stdcall nine-argument import entry used by the
// renderer.  Keeping the slot typed lets MSVC emit the retail indirect tail
// jump while exposing the real API signature to readable callers.
typedef void* (__stdcall *D3DXVec3ProjectArrayImport_00452188)(
    void* out, unsigned int out_stride, const void* vectors,
    unsigned int vector_stride, unsigned int count, const void* viewport,
    const void* projection, const void* view, const void* world);

extern "C" D3DXVec3ProjectArrayImport_00452188 imp_D3DXVec3ProjectArray;

// 0x00452188..0x0045218D: D3DXVec3ProjectArray import thunk.
extern "C" void* __stdcall asm_D3DXVec3ProjectArray_00452188(
    void* out, unsigned int out_stride, const void* vectors,
    unsigned int vector_stride, unsigned int count, const void* viewport,
    const void* projection, const void* view, const void* world) {
    return imp_D3DXVec3ProjectArray(out, out_stride, vectors, vector_stride, count,
                         viewport, projection, view, world);
}
