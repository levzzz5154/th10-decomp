// 0x00438A10..0x00438A24: run the owned object's second virtual slot and drop
// the pointer held at +0x08.
struct Object19 {
    unsigned char pad_000[8];
    void* owner;                     // +0x08
    __declspec(noinline) void Release();
};

#pragma code_seg(".text$01accessor")
void Object19::Release() {
    if (owner) {
        void** table = (void**)*(void**)owner;
        ((void (__stdcall*)(void*))table[2])(owner);
        owner = 0;
    }
}
#pragma code_seg()
