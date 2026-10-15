
// 0x004521CA..0x004521CF: D3DXCreateTextureFromFileInMemoryEx
// D3DX9 exposes this fifteen-argument stdcall import through the fixed slot.
typedef long (__stdcall *D3DXCreateTextureFromFileInMemoryExImport_004521ca)(
    void* device, const void* source_data, unsigned long source_data_size,
    unsigned long width, unsigned long height, unsigned long mip_levels,
    unsigned long usage, unsigned long format, unsigned long pool,
    unsigned long filter, unsigned long mip_filter, unsigned long color_key,
    void* source_info, void* palette, void* texture);

extern "C" D3DXCreateTextureFromFileInMemoryExImport_004521ca imp_D3DXCreateTextureFromFileInMemoryEx;

extern "C" long __stdcall D3DXCreateTextureFromFileInMemoryEx_004521ca(
    void* device, const void* source_data, unsigned long source_data_size,
    unsigned long width, unsigned long height, unsigned long mip_levels,
    unsigned long usage, unsigned long format, unsigned long pool,
    unsigned long filter, unsigned long mip_filter, unsigned long color_key,
    void* source_info, void* palette, void* texture) {
    return imp_D3DXCreateTextureFromFileInMemoryEx(device, source_data, source_data_size, width, height,
                          mip_levels, usage, format, pool, filter, mip_filter,
                          color_key, source_info, palette, texture);
}
