#define g_sprt_ctrl stage_hud_g_sprt_ctrl
#define g_front stage_hud_g_front
#define g_globals stage_hud_data_00474c40
#define g_ascii_manager stage_hud_data_004776e0
#define g_enemy_ctrl stage_hud_g_enemy_ctrl
#define g_player stage_hud_data_00477834
#define data_00477838 stage_hud_data_00477838
#define data_0047783c stage_hud_data_0047783c
#define g_game_speed stage_hud_data_00476f78
#define data_00491fc4 stage_hud_data_00491fc4
#define data_00491fb8 stage_hud_data_00491fb8
#define g_sound_manager stage_hud_data_00492590
#include "hud_view.hpp"
#pragma code_seg(".text$00417040_fn")
void FrontScoreView::Update() {
    if (g_globals.score != displayed_score) {
        int old_displayed = displayed_score;
        int candidate = (g_globals.score - displayed_score) / 32;
        if (candidate>=0x8D55E) candidate=0x8D55E;
        else if (!candidate) candidate=1;
        if (score_velocity<candidate) score_velocity=candidate;
        if (score_velocity>g_globals.score-displayed_score)
            score_velocity=g_globals.score-displayed_score;
        displayed_score += score_velocity;
        if (displayed_score>=g_globals.score) score_velocity=0;
        if (displayed_score>=100000000 && old_displayed<100000000)
            animations[19].stop_frame = 4;
    }
    if (g_globals.high_score<displayed_score) {
        // Preserve the byte test after updating the complete flag word.
        HudFlagWord updated_flags = g_globals.flags;
        updated_flags |= 4;
        g_globals.high_score=displayed_score;
        g_globals.high_score_continues=g_globals.continues;
        g_globals.flags=updated_flags;
        if (!(updated_flags.bytes[0]&4)) {
            ResultAnimationHandle* banner = &g_front->secondary;
            banner->Release();
            banner->id = ResultAnimation_CreatePrimary(g_front->captions,74,15);
        }
    }
    if (stage_frame>=20) {
        if (g_globals.high_score>=100000000 && previous_high_score<100000000)
            animations[9].stop_frame = 4;
        previous_high_score=g_globals.high_score;
    }
    int high = g_globals.high_score;
    int score = displayed_score;
    // Each row has a continues marker followed by nine score digits.
    // Count down while visiting score digits 11..19 and high-score digits 1..9.
    for (int count = 9; count; --count) {
        Entity* current = &animations[20 - count];
        Entity* best = current - 10;
        if (high) {
            int digit = high % 10;
            int next = high / 10;
            reinterpret_cast<Resource_0043e5a0*>(captions)->ConfigureObject(
                reinterpret_cast<AnimationObject_0043e5a0*>(best), digit + 8);
            high = next;
        } else {
            reinterpret_cast<Resource_0043e5a0*>(captions)->ConfigureObject(
                reinterpret_cast<AnimationObject_0043e5a0*>(best), 8);
        }
        if (score) {
            int digit = score % 10;
            int next = score / 10;
            reinterpret_cast<Resource_0043e5a0*>(captions)->ConfigureObject(
                reinterpret_cast<AnimationObject_0043e5a0*>(current), digit + 8);
            score = next;
        } else {
            reinterpret_cast<Resource_0043e5a0*>(captions)->ConfigureObject(
                reinterpret_cast<AnimationObject_0043e5a0*>(current), 8);
        }
        HudTickAnimation(best);
        HudTickAnimation(current);
    }
    reinterpret_cast<Resource_0043e5a0*>(captions)->ConfigureObject(
        reinterpret_cast<AnimationObject_0043e5a0*>(&animations[0]),
        g_globals.high_score_continues + 8);
    reinterpret_cast<Resource_0043e5a0*>(captions)->ConfigureObject(
        reinterpret_cast<AnimationObject_0043e5a0*>(&animations[10]),
        g_globals.continues + 8);
    HudTickAnimation(&animations[0]);
    HudTickAnimation(&animations[10]);
    if (!(flags.bytes[0]&0x20)) {
        if (g_globals.difficulty!=4) {
            if (displayed_score>=data_00474474[g_globals.next_extend]) {
                g_globals.AddLives(1);
                ++g_globals.next_extend;
            }
        } else {
            if (displayed_score>=data_00474488[g_globals.next_extend]) {
                g_globals.AddLives(1);
                ++g_globals.next_extend;
            }
        }
    }
}
#pragma code_seg()
#undef g_sprt_ctrl
#undef g_front
#undef g_globals
#undef g_ascii_manager
#undef g_enemy_ctrl
#undef g_player
#undef data_00477838
#undef data_0047783c
#undef g_game_speed
#undef data_00491fc4
#undef data_00491fb8
#undef g_sound_manager
