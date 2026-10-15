// 0x0042B6D0: delete the effect manager (destructor, then free). Retail keeps the pointer in ESI.

struct EffectManager;
extern "C" void asm_FUN_0042b570_0042b570(void* object);
extern "C" void __cdecl entry_free_004524a1(void* memory);
__declspec(noinline) void EffectManager_Delete(EffectManager* object);
#pragma code_seg(".text$01destroy0042b6d0")
void EffectManager_Delete(EffectManager* object) {
    if (object) {
        asm_FUN_0042b570_0042b570(object);
        entry_free_004524a1(object);
    }
}
#pragma code_seg()
