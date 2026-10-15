// 0x00418150: destroy and free an owned object. Retail keeps the pointer in ESI.

struct OwnedObject_00418150;
extern "C" void asm_FUN_00417c80_00417c80(void* object);
extern "C" void __cdecl entry_free_004524a1(void* memory);
__declspec(noinline) void DestroyOwned_00418150(OwnedObject_00418150* object);
#pragma code_seg(".text$01destroy00418150")
void DestroyOwned_00418150(OwnedObject_00418150* object) {
    if (object) {
        asm_FUN_00417c80_00417c80(object);
        entry_free_004524a1(object);
    }
}
#pragma code_seg()
