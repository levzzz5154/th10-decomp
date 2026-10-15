// Copy compiled into the render batch link so the stage background task sees
// the screen effect factory's private entry convention.
// 0x0043C970..0x0043CAFB: screen fade/pulse/shake selector and its nine-way
// compiler-generated switch table. Native LTCG agrees on this in ESI,
// priority in EBX, and selected mode plus four parameters on the stack.
// Genuine scheduler creation bodies establish callback EAX and priority EDI.
#include "th10/core/screen.hpp"
__declspec(noinline) SchedulerTask* __stdcall CreateEffectPrimary(void* context, int priority, void* routine);
__declspec(noinline) SchedulerTask* __stdcall CreateEffectSecondary(void* context, int priority, void* routine);
extern "C" int __fastcall FadeOutUpdate(void*);
extern "C" int __fastcall ViewportOverlayDraw(void*);
extern "C" int __fastcall FadeInUpdate(void*);
extern "C" int __fastcall PlayfieldOverlayDraw(void*);
extern "C" int __fastcall HalfOpacityFadeUpdate(void*);
extern "C" int __fastcall ScreenOverlayDraw(void*);
extern "C" int __fastcall PlayfieldHalfOpacityDraw(void*);
extern "C" int __fastcall ColorPulseUpdate(void*);
extern "C" int __fastcall ColorPulseDraw(void*);
extern "C" int __fastcall LinearShakeUpdate(void*);
extern "C" int __fastcall EnvelopeShakeUpdate(void*);
extern "C" int __fastcall ScreenEffectRemove(void*);
extern "C" float g_game_speed;
#pragma code_seg(".text$03w8configure")
void Screen::Configure(int priority, int selected_mode,
        int first, int second, int third, int fourth) {
    // Parameters retain their shared representation; each update routine
    // interprets them as colors, durations, repetition counts, or shake limits.
    switch (selected_mode) {
    case 0:
        primary = CreateEffectPrimary(this,14,reinterpret_cast<void*>(FadeOutUpdate));
        secondary = CreateEffectSecondary(this,priority,reinterpret_cast<void*>(ViewportOverlayDraw));
        break;
    case 1:
        primary = CreateEffectPrimary(this,14,reinterpret_cast<void*>(LinearShakeUpdate));
        break;
    case 2:
        primary = CreateEffectPrimary(this,14,reinterpret_cast<void*>(FadeInUpdate));
        secondary = CreateEffectSecondary(this,priority,reinterpret_cast<void*>(PlayfieldOverlayDraw));
        break;
    case 3:
        opacity = 255;
        primary = CreateEffectPrimary(this,14,reinterpret_cast<void*>(FadeOutUpdate));
        secondary = CreateEffectSecondary(this,priority,reinterpret_cast<void*>(PlayfieldOverlayDraw));
        break;
    // Keep the two viewport fades adjacent for the shared registration tail.
    case 5:
        primary = CreateEffectPrimary(this,14,reinterpret_cast<void*>(FadeInUpdate));
        secondary = CreateEffectSecondary(this,priority,reinterpret_cast<void*>(ViewportOverlayDraw));
        break;
    case 4:
        primary = CreateEffectPrimary(this,14,reinterpret_cast<void*>(ColorPulseUpdate));
        secondary = CreateEffectSecondary(this,priority,reinterpret_cast<void*>(ColorPulseDraw));
        break;
    case 6:
        primary = CreateEffectPrimary(this,14,reinterpret_cast<void*>(HalfOpacityFadeUpdate));
        secondary = CreateEffectSecondary(this,priority,reinterpret_cast<void*>(ScreenOverlayDraw));
        break;
    case 7:
        primary = CreateEffectPrimary(this,14,reinterpret_cast<void*>(HalfOpacityFadeUpdate));
        secondary = CreateEffectSecondary(this,priority,reinterpret_cast<void*>(PlayfieldHalfOpacityDraw));
        break;
    case 8:
        primary = CreateEffectPrimary(this,14,reinterpret_cast<void*>(EnvelopeShakeUpdate));
        break;
    }
    primary->on_remove = ScreenEffectRemove;
    if (!(timer.flags & 1u)) {
        timer.current = 0;
        timer.previous = -999999;
        timer.elapsed = 0;
        timer.speed = &g_game_speed;
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
