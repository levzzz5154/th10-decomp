// 0x004464D0: remap a texture format index while the device flag bit 0 is set.
extern "C" unsigned char data_00491d78;
extern "C" int data_0046f288[];

#pragma code_seg(".text$01accessor")
__declspec(noinline) int __stdcall RemapFormat_004464d0(int index) {
    if (data_00491d78 & 1) {
        int format = data_0046f288[index];
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
