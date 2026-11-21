// 0x00418150: destroy and free an owned object. Retail keeps the pointer in ESI.

struct Game;
extern "C" void Game_DestroyState(void* object);
extern "C" void __cdecl crt_free_startup(void* memory);
__declspec(noinline) void Game_Delete(Game* object);
#pragma code_seg(".text$01destroy00418150")
void Game_Delete(Game* object) {
    if (object) {
        Game_DestroyState(object);
        crt_free_startup(object);
    }
}
#pragma code_seg()
