// 0x004389F0..0x00438A04: run the owned object's second virtual slot and drop
// the pointer.
struct Object18 {
    unsigned char pad_000[4];
    void* owner;                     // +0x04
    __declspec(noinline) void Release();
};

#pragma code_seg(".text$01accessor")
void Object18::Release() {
    if (owner) {
        void** table = (void**)*(void**)owner;
        ((void (__stdcall*)(void*))table[2])(owner);
        owner = 0;
    }
}
#pragma code_seg()
