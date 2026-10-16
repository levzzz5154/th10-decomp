// 0x00446F40 (264 bytes): create an ANM texture of an explicit size and fill
// its top surface from the raw pixels of a THTX block, then record the pixel
// size. When the renderer is restricted to 16-bit textures the texture format
// is narrowed first; the THTX block keeps its own format.
//
// Native LTCG passes the texture in EBX, the format index in EAX and the THTX
// block in ECX; width and height stay on the stack.
#include "th10/render/anm_texture.hpp"

#pragma code_seg(".text$04upload")
int __stdcall AnmTexture_CreateAndUpload(AnmTexture* texture, const AnmThtxHeader* thtx, int format, int width, int height) {
    int stored_format = format;
    AnmSurface* surface = 0;
    if (g_sound_flags & 1) {
        int d3d_format = g_texture_formats_a[format];
        if (d3d_format == 21 || d3d_format == 0)
            stored_format = 5;
        else if (d3d_format == 20)
            stored_format = 3;
    }
    AnmRect rect;
    rect.left = 0;
    rect.top = 0;
    rect.right = thtx->width;
    rect.bottom = thtx->height;
    if (asm_D3DXCreateTexture_004521a0(g_d3d_device, width, height, 1, 0,
                                       g_texture_formats_a[stored_format], 1,
                                       reinterpret_cast<void**>(&texture->texture)) != 0) {
        if (surface)
            surface->Release();
        return -1;
    }
    texture->texture->GetSurfaceLevel(0, &surface);
    asm_D3DXLoadSurfaceFromMemory_004521a6(
        surface, 0, &rect, thtx->pixels, g_texture_formats_a[thtx->format],
        thtx->width * g_texture_formats_b[thtx->format], 0, &rect, 1, 0);
    texture->bytes_per_pixel = g_texture_formats_b[stored_format];
    if (surface)
        surface->Release();
    return 0;
}
#pragma code_seg()
