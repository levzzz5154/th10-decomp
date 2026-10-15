// D3DXLoadSurfaceFromSurface is an eight-argument stdcall import.  Keeping
// the fixed import slot as a typed pointer lets MSVC emit the readable tail
// jump while retaining the retail ABI.
typedef long (__stdcall *D3DXLoadSurfaceFromSurfaceImport_004521d6)(
    void* destination_surface, const void* destination_palette,
    const void* destination_rect, void* source_surface,
    const void* source_palette, const void* source_rect,
    unsigned long filter, unsigned long color_key);

extern "C" D3DXLoadSurfaceFromSurfaceImport_004521d6 data_004662c0;

extern "C" long __stdcall D3DXLoadSurfaceFromSurface_004521d6(
    void* destination_surface, const void* destination_palette,
    const void* destination_rect, void* source_surface,
    const void* source_palette, const void* source_rect,
    unsigned long filter, unsigned long color_key) {
    return data_004662c0(destination_surface, destination_palette,
                         destination_rect, source_surface, source_palette,
                         source_rect, filter, color_key);
}
