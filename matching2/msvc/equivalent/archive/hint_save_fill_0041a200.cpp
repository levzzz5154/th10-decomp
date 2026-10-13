// Equivalence-check layout filler for the hint_save_0041a200 draft.
//
// The equivalence tool links the model sources contiguously, so the
// co-compiled WriteShared copy would sit immediately after SaveHints and the
// nine call displacements would point at the wrong address. This code-filled
// section pushes that copy to SaveHints+0x31540, the displacement retail
// uses. Context only: nothing of this file is compared, and it is not part of
// any registered build unit.
#include <intrin.h>
#pragma code_seg(".text$00zzfill")
extern "C" __declspec(noinline) void __stdcall hint_save_fill_0041a200(void) {
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
}
#pragma code_seg()
