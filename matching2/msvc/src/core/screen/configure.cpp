// The screen effect (Screen, 0x44 bytes): a full-screen or
// playfield colour overlay, or a camera shake, run by one update task and an
// optional draw task. Configure (0x0043C970) picks the tasks by mode:
//
//   mode 0, 3  fade in  (overlay alpha 255 -> 0)  update 0x0043BD40
//   mode 2, 5  fade out (overlay alpha 0 -> 255)  update 0x0043C230
//              draw 0x0043C1A0 full screen (modes 0, 5) or 0x0043C2C0 playfield (2, 3)
//   mode 4     flash                             update 0x0043C460, draw 0x0043C500
//   mode 6, 7  dim to half opacity               update 0x0043C310,
//              draw 0x0043C3C0 full screen (6) or 0x0043C410 playfield (7)
//   mode 1     linear camera shake               update 0x0043C550
//   mode 8     envelope camera shake             update 0x0043C710
//
// Files in this folder follow the compile units: updates.cpp and draws.cpp
// (two native-LTCG clusters), dim_update.cpp, shake_update.cpp, flash_draw.cpp.
#include "th10/core/screen.hpp"

// 0x0043C970..0x0043CAFB: screen fade/pulse/shake selector and its nine-way
// compiler-generated switch table. Native LTCG agrees on this in ESI,
// priority in EBX, and selected mode plus four parameters on the stack.
// Genuine scheduler creation bodies establish callback EAX and priority EDI.
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
#pragma code_seg(".text$03selector")
void Screen::Configure(int priority, int selected_mode,
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

#pragma code_seg(".text$01factory")

// The native closure supplies the draw priority in EBX and the five effect
// parameters on the stack. The inline constructor retains the original
// timer flag access before the complete state wipe.
Screen* __stdcall Screen_Create(
        int priority, int mode, int first, int second, int third, int fourth) {
    Screen* owner = new Screen;
    if (owner) {
        owner->Configure(priority, mode, first, second, third, fourth);
    }
    return owner;
}

#pragma code_seg()
