// 0x00446B70 (245 bytes): create an ANM texture from an image file in the
// archive. The file stays loaded and is recorded on the texture together with
// its size and the pixel size of the format actually used; when the renderer
// is restricted to 16-bit textures the format is narrowed first.
//
// The first stack argument is a pointer the body never dereferences: its slot
// is reused to receive the file size. Retail makes the /GS shadow copy of it
// (parameter copied below the path buffer right after the cookie is stored),
// which the compiler only does for pointer-typed parameters.
//
// Native LTCG passes the texture in ESI and the format index in ECX; the
// reused pointer, file name and colour key stay on the stack. Nothing in the
// retail image calls it.
#include "th10/render/anm_texture.hpp"
#include "th10/platform/archive_file.hpp"

#pragma code_seg(".text$01loadfile")
int AnmTexture::LoadFile(int format, void* size_slot, const char* name, unsigned int color_key) {
    char path[260];
    int stored_format = format;
    if (g_sound_flags & 1) {
        int d3d_format = g_texture_formats_a[format];
        if (d3d_format == 21 || d3d_format == 0)
            stored_format = 5;
        else if (d3d_format == 20)
            stored_format = 3;
    }
    sprintf(path, str_string_format, name);
    char* file = Archive_LoadFile(path, reinterpret_cast<int*>(&size_slot), 1);
    if (!file)
        return -1;
    data_size = reinterpret_cast<int>(size_slot);
    if (asm_D3DXCreateTextureFromFileInMemoryEx_004521ca(
            g_d3d_device, file, reinterpret_cast<unsigned int>(size_slot), 0, 0, 0, 0,
            g_texture_formats_a[stored_format], 1, 3,
            0xFFFFFFFF, color_key, 0, 0, &texture) != 0) {
        crt_free(file);
        return -1;
    }
    FillTransparentPixels();
    bytes_per_pixel = g_texture_formats_b[stored_format];
    file_data = file;
    return 0;
}
#pragma code_seg()
