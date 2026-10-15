// 0x004148E0: delete the HUD (destructor, then free). Retail keeps the pointer in ESI.

struct Front;
extern "C" void asm_FUN_004145f0_004145f0(void* object);
extern "C" void __cdecl crt_free_startup(void* memory);
__declspec(noinline) void Front_Delete(Front* object);
#pragma code_seg(".text$01destroy004148e0")
void Front_Delete(Front* object) {
    if (object) {
        asm_FUN_004145f0_004145f0(object);
        crt_free_startup(object);
    }
}
#pragma code_seg()
