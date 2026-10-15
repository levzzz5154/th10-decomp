// 0x004148E0: delete the HUD (destructor, then free). Retail keeps the pointer in ESI.

struct Hud;
extern "C" void asm_FUN_004145f0_004145f0(void* object);
extern "C" void __cdecl entry_free_004524a1(void* memory);
__declspec(noinline) void Hud_Delete(Hud* object);
#pragma code_seg(".text$01destroy004148e0")
void Hud_Delete(Hud* object) {
    if (object) {
        asm_FUN_004145f0_004145f0(object);
        entry_free_004524a1(object);
    }
}
#pragma code_seg()
