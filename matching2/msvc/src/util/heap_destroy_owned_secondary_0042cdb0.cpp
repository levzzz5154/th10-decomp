// 0x0042CDB0: destroy and free an owned object. Retail keeps the pointer in ESI.

struct OwnedObject_0042cdb0;
extern "C" void asm_FUN_0042cb60_0042cb60(void* object);
extern "C" void __cdecl entry_free_004524a1(void* memory);
__declspec(noinline) void DestroyOwned_0042cdb0(OwnedObject_0042cdb0* object);
#pragma code_seg(".text$01destroy0042cdb0")
void DestroyOwned_0042cdb0(OwnedObject_0042cdb0* object) {
    if (object) {
        asm_FUN_0042cb60_0042cb60(object);
        entry_free_004524a1(object);
    }
}
#pragma code_seg()
