extern "C" void __cdecl crt_free(void* block);

__declspec(noinline) void FreeBlock(void* block);

#pragma code_seg(".text$01free")
__declspec(noinline) void FreeBlock(void* block) {
    crt_free(block);
}
#pragma code_seg()
