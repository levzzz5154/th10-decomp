// 0x0041c310: release an owned object and free it. Retail keeps the object in ESI.

struct OwnedObject_0041c310;
extern "C" void __stdcall asm_LaserManager_Destroy_0041c1c0(
    void* object);
extern "C" void __cdecl entry_free_004524a1(void* memory);
__declspec(noinline) void ReleaseOwned_0041c310(OwnedObject_0041c310* object);
#pragma code_seg(".text$01release0041c310")
void ReleaseOwned_0041c310(OwnedObject_0041c310* object) {
    if (object) {
        asm_LaserManager_Destroy_0041c1c0(object);
        entry_free_004524a1(object);
    }
}
#pragma code_seg()
