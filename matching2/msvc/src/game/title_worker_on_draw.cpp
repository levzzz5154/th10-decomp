// 0x0041FEF0: scheduler context in ECX, worker argument on the stack.
#include "th10/render/animation_public_callers.hpp"
#pragma code_seg(".text$05zcallback")
void __fastcall TitleWorker_OnDraw(void* self) {
    TitleEffectsAdvance_0041fdd0((TitleEffectState_0041fdd0*)self);
}
#pragma code_seg()
