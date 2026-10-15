// 0x0043D050..0x0043D074: run the record's second virtual slot, clear the
// owner pointer, then free the record when the low bit of the flags is set.
extern "C" void __cdecl entry_free_004524a1(void* memory);

struct Object_0043d050 {
    void** owner;                    // +0x00
    __declspec(noinline) void* Destroy(unsigned int flags);
};

#pragma code_seg(".text$01accessor")
void* Object_0043d050::Destroy(unsigned int flags) {
    if (owner) {
        void** table = (void**)*owner;
        ((void (__stdcall*)(void*))table[2])(owner);
        owner = 0;
    }
    if (flags & 1) {
        entry_free_004524a1(this);
    }
    return this;
}
#pragma code_seg()
