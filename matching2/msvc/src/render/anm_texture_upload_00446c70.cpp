// 0x00446C70 (243 bytes): fill an ANM texture's top surface, either from an
// image file held in memory or from the raw pixels of the entry's THTX block,
// then patch transparent pixels and record the pixel size. When the renderer
// is restricted to 16-bit textures the recorded format is narrowed first.
//
// Native LTCG passes the texture in EDI, the format index in EAX, the data in
// ESI and its size in EBX; the tag and `has_thtx` stay on the stack. Nothing
// in the retail image calls it.
#include "th10/render/anm_texture_00446c70.hpp"

#pragma code_seg(".text$01upload")
int AnmTexture_00446c70::Upload(AnmUploadTag_00446c70 tag, int format, const void* data, int size,
                                int has_thtx) {
    int stored_format = format;
    if (data_00491d78 & 1) {
        int d3d_format = data_0046f288[format];
        if (d3d_format == 21 || d3d_format == 0)
            stored_format = 5;
        else if (d3d_format == 20)
            stored_format = 3;
    }
    data_size = size;
    AnmSurface_00446c70* surface = 0;
    texture->GetSurfaceLevel(0, &surface);
    if (!has_thtx) {
        asm_D3DXLoadSurfaceFromFileInMemory_004521d0(surface, 0, 0, data, size, 0, 1, 0, 0);
    } else {
        const AnmEntryHeader_00446c70* entry = static_cast<const AnmEntryHeader_00446c70*>(data);
        AnmRect_00446c70 rect;
        rect.left = 0;
        rect.top = 0;
        rect.right = entry->Thtx()->width;
        rect.bottom = entry->Thtx()->height;
        asm_D3DXLoadSurfaceFromMemory_004521a6(
            surface, 0, 0, entry->Thtx()->pixels, data_0046f288[entry->Thtx()->format],
            entry->Thtx()->width * data_0046f2a0[entry->Thtx()->format], 0, &rect, 1, 0);
    }
    surface->Release();
    FillTransparentPixels();
    bytes_per_pixel = data_0046f2a0[stored_format];
    return 0;
}
#pragma code_seg()
