// 0x0044DBD0..0x0044DBED: reset an archive cursor's active handle.
// Native LTCG preserves the retail ESI receiver convention for this member.

extern "C" void (__stdcall* data_004660cc)(int handle);

struct ArchiveCursor_0044dbd0 {
    unsigned char reserved_000[0x78];
    int active_078;
    unsigned char reserved_07c[0x10];
    int handle_08c;

    __declspec(noinline) void Reset();
};

#pragma code_seg(".text$01reset")
void ArchiveCursor_0044dbd0::Reset() {
    if (active_078 == 1) {
        data_004660cc(handle_08c);
        handle_08c = -1;
    }
}
#pragma code_seg()
