// 0x0040D680..0x0040D6A3: restore a bullet entity's vtable and release its
// owned resource.  The native-LTCG cluster preserves the retail this pointer
// in ESI, so this remains an ordinary named member implementation.

extern "C" void __cdecl entry_free_00452422(void* memory);

struct BulletEntity_0040d680 {
    unsigned int vtable;
    unsigned char reserved_004[0x88];
    void* owned_resource;

    __declspec(noinline) void ReleaseResource();
};

#pragma code_seg(".text$01release")
void BulletEntity_0040d680::ReleaseResource() {
    void* const resource = owned_resource;
    vtable = 0x0046D0F0;
    if (resource != 0) {
        entry_free_00452422(resource);
        owned_resource = 0;
    }
}
#pragma code_seg()
