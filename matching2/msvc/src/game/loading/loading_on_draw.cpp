// 0x0041FEF0: the loading screen's draw task (registered by 0x0041FAC0);
// scheduler context in ECX, worker argument on the stack.
#include "th10/render/animation_public_callers.hpp"
#pragma code_seg(".text$05zcallback")
void __fastcall Loading_OnDraw(void* self) {
    TitleEffectsAdvance((TitleEffectState*)self);
}
#pragma code_seg()
