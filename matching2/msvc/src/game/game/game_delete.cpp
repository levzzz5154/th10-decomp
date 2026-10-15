// 0x00418150: destroy and free an owned object. Retail keeps the pointer in ESI.

struct Game;
extern "C" void asm_FUN_00417c80_00417c80(void* object);
extern "C" void __cdecl crt_free_startup(void* memory);
__declspec(noinline) void Game_Delete(Game* object);
#pragma code_seg(".text$01destroy00418150")
void Game_Delete(Game* object) {
    if (object) {
        asm_FUN_00417c80_00417c80(object);
        crt_free_startup(object);
    }
}
#pragma code_seg()
