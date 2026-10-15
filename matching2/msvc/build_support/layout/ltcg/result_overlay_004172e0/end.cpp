// 0x00409C00: end the active spell card. Stops its three effects and lets its
// name banner go; a captured card adds a tenth of its bonus to the score,
// shows the bonus caption and counts the capture in the score file, a failed
// one replaces the caption with the "failed" one. The card arrives in EAX.
#include "th10/game/result_overlay_004172e0.hpp"

#pragma code_seg(".text$00409c00_fn")
void ResultCard_00409c00::End() {
    if (flags & 1) {
        g_background->flags |= 1;
        effects[0].StopAtFrame1();
        effects[1].StopAtFrame1();
        effects[2].StopAtFrame1();
        flags &= ~1u;
        name.Release();
        if (flags & 2) {
            g_globals_score.score += bonus / 10;
            if (g_globals_score.score >= 1000000000) g_globals_score.score = 999999999;
            ResultOverlay_SetMode(0, g_front, bonus);
            if (g_replay->mode != 1) {
                CardHistory_00409c00* history =
                    &g_score->shots[g_globals_score.shot_type + g_globals_score.character * 3].spells[spell_id];
                if (history->captures < 99999) history->captures++;
                history = &g_score->shots[6].spells[spell_id];
                if (history->captures < 99999) history->captures++;
            }
            g_sound_manager.Queue(0x2D, 0);
        } else {
            // The slot is located before the create call, which may replace
            // the front manager.
            ResultAnimationHandle& caption = g_front->caption;
            caption.Release();
            caption.id = ResultAnimation_CreatePrimary(g_front->captions, 0x48, 0xF);
        }
    }
}
#pragma code_seg()
