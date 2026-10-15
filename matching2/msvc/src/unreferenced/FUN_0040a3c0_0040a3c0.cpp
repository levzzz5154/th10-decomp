// Complete state factory at 0x0040A3C0; no arguments, pointer result.
#include "th10/game/sprite_viewer_state.hpp"
void *__cdecl operator new(unsigned int);
struct RawState_0040a130;
extern "C" int __stdcall SpriteViewer_RegisterTasks(RawState_0040a130 *);
extern "C" void __stdcall asm_FUN_0040a1a0_0040a1a0(SpriteViewerState *);
extern "C" void __cdecl entry_free_004524a1(void *);

#pragma code_seg(".text$00_zfactory")
extern "C" __declspec(noinline) SpriteViewerState *__cdecl
asm_FUN_0040a3c0_0040a3c0() {
    SpriteViewerState *state = new SpriteViewerState;
    if (SpriteViewer_RegisterTasks(reinterpret_cast<RawState_0040a130 *>(state))) {
        if (state) {
            asm_FUN_0040a1a0_0040a1a0(state);
            entry_free_004524a1(state);
        }
        return 0;
    }
    return state;
}
#pragma code_seg()
