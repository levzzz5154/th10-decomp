typedef unsigned int (__stdcall *D3DXLoadSurfaceFromMemoryFn)(
    void*, const void*, const void*, const void*, unsigned int,
    unsigned int, const void*, const void*, unsigned int, unsigned int);
extern "C" D3DXLoadSurfaceFromMemoryFn data_004662e0;
extern "C" unsigned int __stdcall asm_D3DXLoadSurfaceFromMemory_004521a6(
    void* destination, const void* destination_palette, const void* destination_rect,
    const void* source, unsigned int format, unsigned int pitch,
    const void* source_palette, const void* source_rect, unsigned int filter,
    unsigned int color_key) {
    return data_004662e0(destination, destination_palette, destination_rect,
                         source, format, pitch, source_palette, source_rect,
                         filter, color_key);
}
