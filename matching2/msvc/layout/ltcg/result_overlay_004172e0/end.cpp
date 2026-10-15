// 0x00409C00: end the active spell card. Stops its three effects and lets its
// name banner go; a captured card adds a tenth of its bonus to the score,
// shows the bonus caption and counts the capture in the score file, a failed
// one replaces the caption with the "failed" one. The card arrives in EAX.
#include "th10/game/result_overlay_004172e0.hpp"

#pragma code_seg(".text$00409c00_fn")
void ResultCard_00409c00::End() {
    if (flags & 1) {
        data_004776e8->flags |= 1;
        effects[0].StopAtFrame1();
        effects[1].StopAtFrame1();
        effects[2].StopAtFrame1();
        flags &= ~1u;
        name.Release();
        if (flags & 2) {
            data_00474c44.score += bonus / 10;
            if (data_00474c44.score >= 1000000000) data_00474c44.score = 999999999;
            ResultOverlay_SetMode(0, data_0047770c, bonus);
            if (data_00477838->mode != 1) {
                CardHistory_00409c00* history =
                    &data_0047783c->shots[data_00474c44.shot_type + data_00474c44.character * 3].spells[spell_id];
                if (history->captures < 99999) history->captures++;
                history = &data_0047783c->shots[6].spells[spell_id];
                if (history->captures < 99999) history->captures++;
            }
            data_00492590.Queue(0x2D, 0);
        } else {
            // The slot is located before the create call, which may replace
            // the front manager.
            ResultAnimationHandle& caption = data_0047770c->caption;
            caption.Release();
            caption.id = ResultAnimation_CreatePrimary(data_0047770c->captions, 0x48, 0xF);
        }
    }
}
#pragma code_seg()
