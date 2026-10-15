// 0x00446F40 (264 bytes): create an ANM texture of an explicit size and fill
// its top surface from the raw pixels of a THTX block, then record the pixel
// size. When the renderer is restricted to 16-bit textures the texture format
// is narrowed first; the THTX block keeps its own format.
//
// Native LTCG passes the texture in EBX, the format index in EAX and the THTX
// block in ECX; width and height stay on the stack.
#include "th10/render/anm_texture_00446c70.hpp"

#pragma code_seg(".text$04upload")
int __stdcall AnmTexture_CreateAndUpload_00446f40(AnmTexture_00446c70* texture, const AnmThtxHeader_00446c70* thtx, int format, int width, int height) {
    int stored_format = format;
    AnmSurface_00446c70* surface = 0;
    if (data_00491d78 & 1) {
        int d3d_format = data_0046f288[format];
        if (d3d_format == 21 || d3d_format == 0)
            stored_format = 5;
        else if (d3d_format == 20)
            stored_format = 3;
    }
    AnmRect_00446c70 rect;
    rect.left = 0;
    rect.top = 0;
    rect.right = thtx->width;
    rect.bottom = thtx->height;
    if (asm_D3DXCreateTexture_004521a0(g_d3d_device, width, height, 1, 0,
                                       data_0046f288[stored_format], 1,
                                       reinterpret_cast<void**>(&texture->texture)) != 0) {
        if (surface)
            surface->Release();
        return -1;
    }
    texture->texture->GetSurfaceLevel(0, &surface);
    asm_D3DXLoadSurfaceFromMemory_004521a6(
        surface, 0, &rect, thtx->pixels, data_0046f288[thtx->format],
        thtx->width * data_0046f2a0[thtx->format], 0, &rect, 1, 0);
    texture->bytes_per_pixel = data_0046f2a0[stored_format];
    if (surface)
        surface->Release();
    return 0;
}
#pragma code_seg()
