// 0x00419100: release an owned object and free it. Retail keeps the object in ESI.

struct OwnedObject4;
extern "C" void __stdcall ResourceManager_CleanupState(void* object);
extern "C" void __cdecl crt_free_startup(void* memory);
__declspec(noinline) void ReleaseOwned2(OwnedObject4* object);
#pragma code_seg(".text$01release00419100")
void ReleaseOwned2(OwnedObject4* object) {
    if (object) {
        ResourceManager_CleanupState(object);
        crt_free_startup(object);
    }
}
#pragma code_seg()
