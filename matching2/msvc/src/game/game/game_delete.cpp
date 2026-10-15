// 0x00418150: destroy and free an owned object. Retail keeps the pointer in ESI.

struct Game;
extern "C" void asm_FUN_00417c80_00417c80(void* object);
extern "C" void __cdecl entry_free_004524a1(void* memory);
__declspec(noinline) void Game_Delete(Game* object);
#pragma code_seg(".text$01destroy00418150")
void Game_Delete(Game* object) {
    if (object) {
        asm_FUN_00417c80_00417c80(object);
        entry_free_004524a1(object);
    }
}
#pragma code_seg()
