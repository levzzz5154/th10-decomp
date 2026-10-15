extern "C" void __cdecl entry_free_00452422(void* block);

struct ResourceOwner_0040c860 {
    void* vtable;
    unsigned char pad_004[0x8C - 0x04];
    void* block_8C;
    __declspec(noinline) void ReleaseBlock();
};

#pragma code_seg(".text$01release")
void ResourceOwner_0040c860::ReleaseBlock() {
    vtable = (void*)0x46D0F0;
    if (block_8C != 0) {
        entry_free_00452422(block_8C);
        block_8C = 0;
    }
}
#pragma code_seg()
