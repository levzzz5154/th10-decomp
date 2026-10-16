// 0x00446D70 (319 bytes): fill an ANM texture's top surface starting `top`
// rows down, either from an image file held in memory or from the raw pixels
// of the entry's THTX block, then patch transparent pixels and record the
// pixel size. When the renderer is restricted to 16-bit textures the recorded
// format is narrowed first.
//
// Native LTCG passes the format index in EAX, the row offset in ECX and the
// data in EDI; the unread tag, the texture, the size and `has_thtx` stay on
// the stack, the texture after the tag, so this one is not a member call.
// Nothing in the retail image calls it.
#include "th10/render/anm_texture.hpp"

#pragma code_seg(".text$03uploadat")
int __stdcall AnmTexture_UploadAt(AnmUploadTag tag, AnmTexture* texture,
                                           int format, const void* data, int top, int size,
                                           int has_thtx) {
    int stored_format = format;
    if (g_sound_flags & 1) {
        int d3d_format = g_texture_formats_a[format];
        if (d3d_format == 21 || d3d_format == 0)
            stored_format = 5;
        else if (d3d_format == 20)
            stored_format = 3;
    }
    texture->data_size = size;
    AnmSurface* surface = 0;
    texture->texture->GetSurfaceLevel(0, &surface);
    if (!has_thtx) {
        AnmSurfaceDesc desc;
        surface->GetDesc(&desc);
        AnmRect destination;
        destination.left = 0;
        destination.top = top;
        destination.right = desc.width;
        destination.bottom = desc.height;
        asm_D3DXLoadSurfaceFromFileInMemory_004521d0(surface, 0, &destination, data, size, 0, 1, 0, 0);
    } else {
        const AnmEntryHeader2* entry = static_cast<const AnmEntryHeader2*>(data);
        AnmRect source;
        source.left = 0;
        source.top = 0;
        source.right = entry->Thtx()->width;
        source.bottom = entry->Thtx()->height;
        AnmRect destination;
        destination.left = 0;
        destination.top = top;
        destination.right = entry->Thtx()->width;
        destination.bottom = entry->Thtx()->height + top;
        asm_D3DXLoadSurfaceFromMemory_004521a6(
            surface, 0, &destination, entry->Thtx()->pixels, g_texture_formats_a[entry->Thtx()->format],
            entry->Thtx()->width * g_texture_formats_b[entry->Thtx()->format], 0, &source, 1, 0);
    }
    surface->Release();
    texture->FillTransparentPixels();
    texture->bytes_per_pixel = g_texture_formats_b[stored_format];
    return 0;
}
#pragma code_seg()
