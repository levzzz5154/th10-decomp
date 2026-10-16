#include "../build_support/include/asm_encoding.hpp"

typedef long (__stdcall *D3DXLoadSurfaceFromFileInMemoryImport_004521d0)(
    void* destination_surface, const void* destination_palette,
    const void* destination_rect, const void* source_file,
    unsigned long source_file_size, const void* source_rect,
    void* source_info, unsigned long filter, unsigned long color_key);

extern "C" D3DXLoadSurfaceFromFileInMemoryImport_004521d0 imp_D3DXLoadSurfaceFromFileInMemory;

// 0x004521D0..0x004521D5: imported D3DXLoadSurfaceFromFileInMemory tail thunk.
extern "C" long __stdcall asm_D3DXLoadSurfaceFromFileInMemory_004521d0(
    void* destination_surface, const void* destination_palette,
    const void* destination_rect, const void* source_file,
    unsigned long source_file_size, const void* source_rect,
    void* source_info, unsigned long filter, unsigned long color_key) {
    return imp_D3DXLoadSurfaceFromFileInMemory(destination_surface, destination_palette,
                          destination_rect, source_file, source_file_size,
                          source_rect, source_info, filter, color_key);
}
