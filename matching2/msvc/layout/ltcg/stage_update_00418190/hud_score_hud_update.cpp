#define data_00491c10 stage_hud_data_00491c10
#define data_0047770c stage_hud_data_0047770c
#define data_00474c40 stage_hud_data_00474c40
#define data_004776e0 stage_hud_data_004776e0
#define data_00477704 stage_hud_data_00477704
#define data_00477834 stage_hud_data_00477834
#define data_00477838 stage_hud_data_00477838
#define data_0047783c stage_hud_data_0047783c
#define data_00476f78 stage_hud_data_00476f78
#define data_00491fc4 stage_hud_data_00491fc4
#define data_00491fb8 stage_hud_data_00491fb8
#define data_00492590 stage_hud_data_00492590
#include "hud_view.hpp"
#pragma code_seg(".text$00417040_fn")
void ScoreHud_00417040::Update() {
    if (data_00474c40.score != displayed_score) {
        int old_displayed = displayed_score;
        int candidate = (data_00474c40.score - displayed_score) / 32;
        if (candidate>=0x8D55E) candidate=0x8D55E;
        else if (!candidate) candidate=1;
        if (score_velocity<candidate) score_velocity=candidate;
        if (score_velocity>data_00474c40.score-displayed_score)
            score_velocity=data_00474c40.score-displayed_score;
        displayed_score += score_velocity;
        if (displayed_score>=data_00474c40.score) score_velocity=0;
        if (displayed_score>=100000000 && old_displayed<100000000)
            animations[19].stop_frame = 4;
    }
    if (data_00474c40.high_score<displayed_score) {
        // Preserve the byte test after updating the complete flag word.
        HudFlagWord updated_flags = data_00474c40.flags;
        updated_flags |= 4;
        data_00474c40.high_score=displayed_score;
        data_00474c40.high_score_continues=data_00474c40.continues;
        data_00474c40.flags=updated_flags;
        if (!(updated_flags.bytes[0]&4)) {
            ResultAnimationHandle* banner = &data_0047770c->secondary;
            banner->Release();
            banner->id = ResultAnimation_CreatePrimary(data_0047770c->captions,74,15);
        }
    }
    if (stage_frame>=20) {
        if (data_00474c40.high_score>=100000000 && previous_high_score<100000000)
            animations[9].stop_frame = 4;
        previous_high_score=data_00474c40.high_score;
    }
    int high = data_00474c40.high_score;
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
        data_00474c40.high_score_continues + 8);
    reinterpret_cast<Resource_0043e5a0*>(captions)->ConfigureObject(
        reinterpret_cast<AnimationObject_0043e5a0*>(&animations[10]),
        data_00474c40.continues + 8);
    HudTickAnimation(&animations[0]);
    HudTickAnimation(&animations[10]);
    if (!(flags.bytes[0]&0x20)) {
        if (data_00474c40.difficulty!=4) {
            if (displayed_score>=data_00474474[data_00474c40.next_extend]) {
                data_00474c40.AddLives(1);
                ++data_00474c40.next_extend;
            }
        } else {
            if (displayed_score>=data_00474488[data_00474c40.next_extend]) {
                data_00474c40.AddLives(1);
                ++data_00474c40.next_extend;
            }
        }
    }
}
#pragma code_seg()
#undef data_00491c10
#undef data_0047770c
#undef data_00474c40
#undef data_004776e0
#undef data_00477704
#undef data_00477834
#undef data_00477838
#undef data_0047783c
#undef data_00476f78
#undef data_00491fc4
#undef data_00491fb8
#undef data_00492590
