// 0x0041AFB0: delete the native effect manager (destructor, then free). Retail keeps the pointer in ESI.

struct NativeEffectManager;
extern "C" void __stdcall BulletManager_Destroy_0041adf0(void* object);
extern "C" void __cdecl entry_free_004524a1(void* memory);
__declspec(noinline) void NativeEffectManager_Delete(NativeEffectManager* object);
#pragma code_seg(".text$01destroy0041afb0")
void NativeEffectManager_Delete(NativeEffectManager* object) {
    if (object) {
        BulletManager_Destroy_0041adf0(object);
        entry_free_004524a1(object);
    }
}
#pragma code_seg()
