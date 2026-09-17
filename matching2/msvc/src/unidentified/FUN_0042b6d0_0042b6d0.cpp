// 0x0042B6D0: destroy and free an owned object. Retail keeps the pointer in ESI.

struct OwnedObject_0042b6d0;
extern "C" void asm_FUN_0042b570_0042b570(void* object);
extern "C" void __cdecl entry_free_004524a1(void* memory);
__declspec(noinline) void DestroyOwned_0042b6d0(OwnedObject_0042b6d0* object);
#pragma code_seg(".text$01destroy0042b6d0")
void DestroyOwned_0042b6d0(OwnedObject_0042b6d0* object) {
    if (object) {
        asm_FUN_0042b570_0042b570(object);
        entry_free_004524a1(object);
    }
}
#pragma code_seg()
