// 0x0041c310: release an owned object and free it. Retail keeps the object in ESI.

struct OwnedObject7;
extern "C" void __stdcall asm_LaserManager_Destroy_0041c1c0(
    void* object);
extern "C" void __cdecl crt_free_startup(void* memory);
__declspec(noinline) void ReleaseOwned3(OwnedObject7* object);
#pragma code_seg(".text$01release0041c310")
void ReleaseOwned3(OwnedObject7* object) {
    if (object) {
        asm_LaserManager_Destroy_0041c1c0(object);
        crt_free_startup(object);
    }
}
#pragma code_seg()
