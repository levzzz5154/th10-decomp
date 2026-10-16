// 0x00446EB0 (132 bytes): create an ANM texture of an explicit size from the
// image file the texture already holds in memory, then patch transparent
// pixels and record the pixel size. When the renderer is restricted to 16-bit
// textures the format is narrowed first.
//
// Native LTCG passes the texture in ESI, the format index in EAX and the
// height in EDX; the unread tag, colour key and width stay on the stack.
#include "th10/render/anm_texture.hpp"

#pragma code_seg(".text$04create")
int __stdcall AnmTexture_CreateFromMemory(AnmUploadTag tag,
                                                   AnmTexture* texture, int format,
                                                   unsigned int color_key, int width, int height) {
    int stored_format = format;
    if (g_sound_flags & 1) {
        int d3d_format = g_texture_formats_a[format];
        if (d3d_format == 21 || d3d_format == 0)
            stored_format = 5;
        else if (d3d_format == 20)
            stored_format = 3;
    }
    if (asm_D3DXCreateTextureFromFileInMemoryEx_004521ca(
            g_d3d_device, texture->file_data, texture->data_size, width, height, 0, 0,
            g_texture_formats_a[stored_format], 1, 1, 0xFFFFFFFF, color_key, 0, 0, &texture->texture) != 0)
        return -1;
    texture->FillTransparentPixels();
    texture->bytes_per_pixel = g_texture_formats_b[stored_format];
    return 0;
}
#pragma code_seg()
