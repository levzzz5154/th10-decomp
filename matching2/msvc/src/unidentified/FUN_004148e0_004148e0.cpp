// 0x004148E0: destroy and free an owned object. Retail keeps the pointer in ESI.

struct OwnedObject_004148e0;
extern "C" void asm_FUN_004145f0_004145f0(void* object);
extern "C" void __cdecl entry_free_004524a1(void* memory);
__declspec(noinline) void DestroyOwned_004148e0(OwnedObject_004148e0* object);
#pragma code_seg(".text$01destroy004148e0")
void DestroyOwned_004148e0(OwnedObject_004148e0* object) {
    if (object) {
        asm_FUN_004145f0_004145f0(object);
        entry_free_004524a1(object);
    }
}
#pragma code_seg()
