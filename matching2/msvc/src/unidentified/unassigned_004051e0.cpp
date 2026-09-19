
extern "C" void* __cdecl entry_malloc_00452706(unsigned int size);

__declspec(noinline) void* AllocateBlock_004051e0(unsigned int size);

#pragma code_seg(".text$01alloc")
__declspec(noinline) void* AllocateBlock_004051e0(unsigned int size) {
    return entry_malloc_00452706(size);
}
#pragma code_seg()
