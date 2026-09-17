// 0x00425090: destroy and free an owned object. Retail keeps the pointer in ESI.

struct OwnedObject_00425090;
extern "C" void asm_FUN_00424ed0_00424ed0(void* object);
extern "C" void __cdecl entry_free_004524a1(void* memory);
__declspec(noinline) void DestroyOwned_00425090(OwnedObject_00425090* object);
#pragma code_seg(".text$01destroy00425090")
void DestroyOwned_00425090(OwnedObject_00425090* object) {
    if (object) {
        asm_FUN_00424ed0_00424ed0(object);
        entry_free_004524a1(object);
    }
}
#pragma code_seg()
