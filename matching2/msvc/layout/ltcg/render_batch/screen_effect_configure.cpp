// Copy compiled into the render batch link so the stage background task sees
// the screen effect factory's private entry convention.
// 0x0043C970..0x0043CAFB: screen fade/pulse/shake selector and its nine-way
// compiler-generated switch table. Native LTCG agrees on this in ESI,
// priority in EBX, and selected mode plus four parameters on the stack.
// Genuine scheduler creation bodies establish callback EAX and priority EDI.
#include "th10/game/runtime_selector_0043c970.hpp"
__declspec(noinline) SchedulerTask* __stdcall CreateEffectPrimary(void* context, int priority, void* routine);
__declspec(noinline) SchedulerTask* __stdcall CreateEffectSecondary(void* context, int priority, void* routine);
extern "C" int __fastcall FadeOutUpdate_0043bd40(void*);
extern "C" int __fastcall ViewportOverlayDraw_0043c1a0(void*);
extern "C" int __fastcall FadeInUpdate_0043c230(void*);
extern "C" int __fastcall PlayfieldOverlayDraw_0043c2c0(void*);
extern "C" int __fastcall HalfOpacityFadeUpdate_0043c310(void*);
extern "C" int __fastcall ScreenOverlayDraw_0043c3c0(void*);
extern "C" int __fastcall PlayfieldHalfOpacityDraw_0043c410(void*);
extern "C" int __fastcall ColorPulseUpdate_0043c460(void*);
extern "C" int __fastcall ColorPulseDraw_0043c500(void*);
extern "C" int __fastcall LinearShakeUpdate_0043c550(void*);
extern "C" int __fastcall EnvelopeShakeUpdate_0043c710(void*);
extern "C" int __fastcall ScreenEffectRemove_0043c870(void*);
extern "C" float data_00476f78;
#pragma code_seg(".text$03w8configure")
void ScreenEffectController_0043c970::Configure(int priority, int selected_mode,
        int first, int second, int third, int fourth) {
    // Parameters retain their shared representation; each update routine
    // interprets them as colors, durations, repetition counts, or shake limits.
    switch (selected_mode) {
    case 0:
        primary = CreateEffectPrimary(this,14,reinterpret_cast<void*>(FadeOutUpdate_0043bd40));
        secondary = CreateEffectSecondary(this,priority,reinterpret_cast<void*>(ViewportOverlayDraw_0043c1a0));
        break;
    case 1:
        primary = CreateEffectPrimary(this,14,reinterpret_cast<void*>(LinearShakeUpdate_0043c550));
        break;
    case 2:
        primary = CreateEffectPrimary(this,14,reinterpret_cast<void*>(FadeInUpdate_0043c230));
        secondary = CreateEffectSecondary(this,priority,reinterpret_cast<void*>(PlayfieldOverlayDraw_0043c2c0));
        break;
    case 3:
        opacity = 255;
        primary = CreateEffectPrimary(this,14,reinterpret_cast<void*>(FadeOutUpdate_0043bd40));
        secondary = CreateEffectSecondary(this,priority,reinterpret_cast<void*>(PlayfieldOverlayDraw_0043c2c0));
        break;
    // Keep the two viewport fades adjacent for the shared registration tail.
    case 5:
        primary = CreateEffectPrimary(this,14,reinterpret_cast<void*>(FadeInUpdate_0043c230));
        secondary = CreateEffectSecondary(this,priority,reinterpret_cast<void*>(ViewportOverlayDraw_0043c1a0));
        break;
    case 4:
        primary = CreateEffectPrimary(this,14,reinterpret_cast<void*>(ColorPulseUpdate_0043c460));
        secondary = CreateEffectSecondary(this,priority,reinterpret_cast<void*>(ColorPulseDraw_0043c500));
        break;
    case 6:
        primary = CreateEffectPrimary(this,14,reinterpret_cast<void*>(HalfOpacityFadeUpdate_0043c310));
        secondary = CreateEffectSecondary(this,priority,reinterpret_cast<void*>(ScreenOverlayDraw_0043c3c0));
        break;
    case 7:
        primary = CreateEffectPrimary(this,14,reinterpret_cast<void*>(HalfOpacityFadeUpdate_0043c310));
        secondary = CreateEffectSecondary(this,priority,reinterpret_cast<void*>(PlayfieldHalfOpacityDraw_0043c410));
        break;
    case 8:
        primary = CreateEffectPrimary(this,14,reinterpret_cast<void*>(EnvelopeShakeUpdate_0043c710));
        break;
    }
    primary->on_remove = ScreenEffectRemove_0043c870;
    if (!(timer.flags & 1u)) {
        timer.current = 0;
        timer.previous = -999999;
        timer.elapsed = 0;
        timer.speed = &data_00476f78;
        timer.flags |= 1u;
    }
    // Reset the first three timer words together. The zero bits stored in
    // elapsed are IEEE-754 +0.0f; this shared view preserves their retail order.
    int* timer_words = reinterpret_cast<int*>(&timer);
    timer_words[1] = 0;
    timer_words[2] = 0;
    timer_words[0] = -1;
    duration_or_strength = first;
    mode = selected_mode;
    parameter20 = second;
    parameter24 = third;
    parameter28 = fourth;
}
#pragma code_seg()
