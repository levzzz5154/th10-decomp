// 0x004464D0: remap a texture format index while the device flag bit 0 is set.
extern "C" unsigned char g_sound_flags;
extern "C" int g_texture_formats_a[];

#pragma code_seg(".text$01accessor")
__declspec(noinline) int __stdcall RemapFormat_004464d0(int index) {
    if (g_sound_flags & 1) {
        int format = g_texture_formats_a[index];
        if (format == 0x15 || format == 0) {
            return 5;
        }
        if (format == 0x14) {
            return 3;
        }
    }
    return index;
}
#pragma code_seg()
