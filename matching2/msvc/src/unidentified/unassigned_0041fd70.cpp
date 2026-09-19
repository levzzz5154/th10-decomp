// 0x0041fd70: release an owned object and free it. Retail keeps the object in ESI.

struct OwnedObject_0041fd70;
extern "C" void asm_FUN_0041fb50_0041fb50(void* object);
extern "C" void __cdecl entry_free_004524a1(void* memory);
__declspec(noinline) void ReleaseOwned_0041fd70(OwnedObject_0041fd70* object);
#pragma code_seg(".text$01release0041fd70")
void ReleaseOwned_0041fd70(OwnedObject_0041fd70* object) {
    if (object) {
        asm_FUN_0041fb50_0041fb50(object);
        entry_free_004524a1(object);
    }
}
#pragma code_seg()
