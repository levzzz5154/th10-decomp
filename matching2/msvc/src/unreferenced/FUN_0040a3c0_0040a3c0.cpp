// Complete state factory at 0x0040A3C0; no arguments, pointer result.
#include "th10/game/ecl_view.hpp"
void *__cdecl operator new(unsigned int);
struct RawState_0040a130;
extern "C" int __stdcall EclView_RegisterTasks(RawState_0040a130 *);
extern "C" void __stdcall asm_FUN_0040a1a0_0040a1a0(EclViewState *);
extern "C" void __cdecl crt_free_startup(void *);

#pragma code_seg(".text$00_zfactory")
extern "C" __declspec(noinline) EclViewState *__cdecl
asm_FUN_0040a3c0_0040a3c0() {
    EclViewState *state = new EclViewState;
    if (EclView_RegisterTasks(reinterpret_cast<RawState_0040a130 *>(state))) {
        if (state) {
            asm_FUN_0040a1a0_0040a1a0(state);
            crt_free_startup(state);
        }
        return 0;
    }
    return state;
}
#pragma code_seg()
