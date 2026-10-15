// 0x00417C70..0x00417C7B: the stage loading thread (started by 0x004180E0).
// Hand the object held by the global at 0x00477810 to
// the routine at 0x00417870 (argument taken on the stack, cleaned by the
// callee).
extern "C" unsigned char g_game;                 // 0x00477810
extern "C" void __stdcall asm_FUN_00417870_00417870(void* object);

extern "C" void __cdecl Game_LoadThread(void) {
    asm_FUN_00417870_00417870(*(void**)&g_game);
}
