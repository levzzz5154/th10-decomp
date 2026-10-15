extern "C" void __cdecl entry_free_00452422(void* block);

__declspec(noinline) void FreeBlock_00402040(void* block);

#pragma code_seg(".text$01free")
__declspec(noinline) void FreeBlock_00402040(void* block) {
    entry_free_00452422(block);
}
#pragma code_seg()
