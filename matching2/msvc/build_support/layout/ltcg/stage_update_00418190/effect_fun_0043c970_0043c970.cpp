#define g_sprt_ctrl stage_effect_g_sprt_ctrl
#define g_front stage_effect_g_front
#define g_globals stage_effect_data_00474c40
#define g_ascii_manager stage_effect_data_004776e0
#define g_enemy_ctrl stage_effect_g_enemy_ctrl
#define g_player stage_effect_data_00477834
#define g_replay stage_effect_data_00477838
#define g_score stage_effect_data_0047783c
#define g_game_speed stage_effect_data_00476f78
#define g_stage_flags stage_effect_data_00491fc4
#define g_main_state stage_effect_data_00491fb8
#define g_sound_manager stage_effect_data_00492590
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
#pragma code_seg(".text$0043c970_fn")
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
#undef g_sprt_ctrl
#undef g_front
#undef g_globals
#undef g_ascii_manager
#undef g_enemy_ctrl
#undef g_player
#undef g_replay
#undef g_score
#undef g_game_speed
#undef g_stage_flags
#undef g_main_state
#undef g_sound_manager
