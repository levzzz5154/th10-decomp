// Release one indexed animation resource set at 0x00447F70.
// Native LTCG supplies the retail EDI manager and ESI index convention.
extern "C" void __cdecl ReleaseHeapMemory_00452422(void* memory);
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
struct Resource_00447f70 {
    virtual long __stdcall QueryInterface(const void*, void**) = 0;
    virtual unsigned long __stdcall AddRef() = 0;
    virtual unsigned long __stdcall Release() = 0;
};
struct AnimationManagerIndexed_00447f70 {
    unsigned char pad[0x3ad4e0];
    Resource_00447f70* primary[32];   // +0x3AD4E0
    Resource_00447f70* secondary[32]; // +0x3AD560
    void* memory[32];               // +0x3AD5E0
    __declspec(noinline) void Clear(int index);
};
#pragma code_seg(".text$01clear")
void AnimationManagerIndexed_00447f70::Clear(int index) {
    if (primary[index]) { primary[index]->Release(); primary[index] = 0; }
    if (secondary[index]) { secondary[index]->Release(); secondary[index] = 0; }
    if (memory[index]) {
        ReleaseHeapMemory_00452422(memory[index]);
        memory[index] = 0;
        // Preserve the retail conditional clear followed by the final clear.
        _ReadWriteBarrier();
    }
    memory[index] = 0;
}
#pragma code_seg()
