#include "../../../build_support/include/asm_symbols.hpp"

// 0x0042A430: the replay manager's draw task (registered by 0x00428F60).
// The scene arrives in ECX. The routine reports whether the active global scene
// owns a live object with bit 2 of its flag byte set; otherwise it hands the
// scene straight to the frame-tick routine at 0x00429A70, whose receiver reads
// it from EDX next to its unused first argument.
extern "C" unsigned char g_game;                       // 0x00477810  active scene

typedef int (__fastcall* SceneTick)(int self, void* scene);

int __fastcall ReplayManager_OnDraw(void* self) {
    void* scene = *(void**)&g_game;
    if (scene != 0 && (*(unsigned char*)((char*)scene + 0x58) & 4) != 0)
        return 1;
    return ((SceneTick)asm_FUN_00429a70_00429a70)((int)self, self);
}
