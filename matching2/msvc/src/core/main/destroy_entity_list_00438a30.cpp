// 0x00438A30: release the 32 interfaces an object holds and clear their slots.
struct Releasable_00438a30 {
    virtual long __stdcall QueryInterface(const void* iid, void** object) = 0;
    virtual unsigned long __stdcall AddRef() = 0;
    virtual unsigned long __stdcall Release() = 0;
};
struct Holder_00438a30 {
    unsigned char unknown_000000[0x3AD4E0];
    Releasable_00438a30* interfaces[32];
};

#pragma code_seg(".text$01accessor")
__declspec(noinline) void __stdcall ReleaseAll_00438a30(Holder_00438a30* holder) {
    for (int i = 0; i < 32; ++i) {
        if (holder->interfaces[i]) {
            holder->interfaces[i]->Release();
            holder->interfaces[i] = 0;
        }
    }
}
#pragma code_seg()
