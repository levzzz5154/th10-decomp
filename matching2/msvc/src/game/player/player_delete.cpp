// 0x00425090: delete the player (destructor, then free). Retail keeps the pointer in ESI.

struct Player;
extern "C" void asm_FUN_00424ed0_00424ed0(void* object);
extern "C" void __cdecl crt_free_startup(void* memory);
__declspec(noinline) void Player_Delete(Player* object);
#pragma code_seg(".text$01destroy00425090")
void Player_Delete(Player* object) {
    if (object) {
        asm_FUN_00424ed0_00424ed0(object);
        crt_free_startup(object);
    }
}
#pragma code_seg()
