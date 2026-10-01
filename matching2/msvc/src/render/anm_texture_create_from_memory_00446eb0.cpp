// 0x00446EB0 (132 bytes): create an ANM texture of an explicit size from the
// image file the texture already holds in memory, then patch transparent
// pixels and record the pixel size. When the renderer is restricted to 16-bit
// textures the format is narrowed first.
//
// Native LTCG passes the texture in ESI, the format index in EAX and the
// height in EDX; the unread tag, colour key and width stay on the stack.
#include "th10/render/anm_texture_00446c70.hpp"

#pragma code_seg(".text$04create")
int __stdcall AnmTexture_CreateFromMemory_00446eb0(AnmUploadTag_00446c70 tag,
                                                   AnmTexture_00446c70* texture, int format,
                                                   unsigned int color_key, int width, int height) {
    int stored_format = format;
    if (data_00491d78 & 1) {
        int d3d_format = data_0046f288[format];
        if (d3d_format == 21 || d3d_format == 0)
            stored_format = 5;
        else if (d3d_format == 20)
            stored_format = 3;
    }
    if (asm_D3DXCreateTextureFromFileInMemoryEx_004521ca(
            data_00491c30, texture->file_data, texture->data_size, width, height, 0, 0,
            data_0046f288[stored_format], 1, 1, 0xFFFFFFFF, color_key, 0, 0, &texture->texture) != 0)
        return -1;
    texture->FillTransparentPixels();
    texture->bytes_per_pixel = data_0046f2a0[stored_format];
    return 0;
}
#pragma code_seg()
