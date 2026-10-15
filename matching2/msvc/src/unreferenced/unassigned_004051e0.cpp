
extern "C" void* __cdecl entry_malloc(unsigned int size);

__declspec(noinline) void* AllocateBlock(unsigned int size);

#pragma code_seg(".text$01alloc")
__declspec(noinline) void* AllocateBlock(unsigned int size) {
    return entry_malloc(size);
}
#pragma code_seg()
