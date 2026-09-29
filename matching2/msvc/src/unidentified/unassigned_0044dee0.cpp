// 0x0044DEE0: close an archive cursor's open handle.
extern "C" void (__stdcall* data_004660cc)(int handle);

struct ArchiveCursor_0044dee0 {
    unsigned char reserved_000[0x78];
    int active_078;
    unsigned char reserved_07c[0x10];
    int handle_08c;

    __declspec(noinline) int Close();
};

#pragma code_seg(".text$01accessor")
int ArchiveCursor_0044dee0::Close() {
    if (active_078 == 1) {
        data_004660cc(handle_08c);
        handle_08c = -1;
    }
    return 0;
}
#pragma code_seg()
