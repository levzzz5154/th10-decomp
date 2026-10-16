// 0x00438A30: release the 32 interfaces an object holds and clear their slots.
struct Releasable3 {
    virtual long __stdcall QueryInterface(const void* iid, void** object) = 0;
    virtual unsigned long __stdcall AddRef() = 0;
    virtual unsigned long __stdcall Release() = 0;
};
struct Holder2 {
    unsigned char unknown_000000[0x3AD4E0];
    Releasable3* interfaces[32];
};

#pragma code_seg(".text$01accessor")
__declspec(noinline) void __stdcall ReleaseAll(Holder2* holder) {
    for (int i = 0; i < 32; ++i) {
        if (holder->interfaces[i]) {
            holder->interfaces[i]->Release();
            holder->interfaces[i] = 0;
        }
    }
}
#pragma code_seg()
