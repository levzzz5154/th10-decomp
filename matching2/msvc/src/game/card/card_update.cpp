// 0x00408D60: per-frame update of the in-game side panel, and the scheduler
// callback at 0x00409220 that runs it.
#include "th10/game/card_update.hpp"
#include "th10/game/player.hpp"

struct StageState_00408d60 {
    unsigned char reserved[0x2A18];
    unsigned int flags;                            // +0x2A18
};
struct FrontResources_00408d60 {
    unsigned char reserved[0x9EC8];
    Resource_0043e5a0* digits;                     // +0x9EC8
};
struct SpellRecord_00408d60 {
    int attempts;
    int captures;
    unsigned char reserved[0x88];
};
struct ShotRecord_00408d60 {
    unsigned char reserved[0x624];
    SpellRecord_00408d60 spells[1];
    unsigned char reserved_6b4[0x437C - 0x6B4];
};
struct ScoreFile_00408d60 {
    ShotRecord_00408d60 shots[6];
};
struct MarkerTarget_00408d60 {
    unsigned char reserved[0x1068];
    Vec3 position;                                 // +0x1068
};
struct MarkerOwner_00408d60 {
    unsigned char reserved[0x10];
    MarkerTarget_00408d60* target;                 // +0x10
};

// Part of the global game state.
struct GameSelection_00408d60 {
    int character;                                 // 0x00474C68
    int shot_type;                                 // 0x00474C6C
};

extern "C" {
extern StageState_00408d60* data_004776e8;
extern FrontResources_00408d60* data_0047770c;
extern ScoreFile_00408d60* data_0047783c;
extern MarkerOwner_00408d60* data_00477704;
extern GameSelection_00408d60 g_selection;         // 0x00474C68
// The animation VM takes one stack object pointer and returns with RET 4.
int __stdcall RunAnimationVm(HudSprite_00408d60* sprite);
}

static inline void Configure(HudSprite_00408d60* sprite, int script) {
    data_0047770c->digits->ConfigureObject(
        reinterpret_cast<AnimationObject_0043e5a0*>(sprite), script);
}

#pragma code_seg(".text$a00update")
int Card_00408d60::Update() {
    if (!(flags & 1))
        return 1;
    if (timer.current >= 60)
        data_004776e8->flags &= ~1u;
    if (timer.current >= 300 && !(flags & 8)) {
        bonus -= (bonus_start - bonus_start / 10) / (bonus_duration - 300);
        bonus -= bonus % 10;
    }
    RunAnimationVm(&frame_sprite);
    RunAnimationVm(&label_sprite);
    timer.previous = timer.current;
    if (*timer.speed > g_frame_timer_normal_lower && *timer.speed < g_frame_timer_normal_upper) {
        ++timer.current;
        timer.elapsed += 1.0f;
    } else {
        timer.current = int(timer.elapsed = *timer.speed + timer.elapsed);
    }

    if (timer.current >= 120) {
        int i;
        if (!(flags & 4)) {
            if (g_player->position.y < 96.0f) {
                for (i = 0; i < 3; ++i)
                    panel_handles[i].SetStopFrame(3);
                for (i = 0; i < 8; ++i)
                    bonus_digits[i].stop_frame = 3;
                for (i = 0; i < 5; ++i)
                    counter_digits[i].stop_frame = 3;
                flags |= 4;
            }
        } else if (g_player->position.y > 128.0f) {
            for (i = 0; i < 3; ++i)
                panel_handles[i].SetStopFrame(2);
            for (i = 0; i < 8; ++i)
                bonus_digits[i].stop_frame = 2;
            for (i = 0; i < 5; ++i)
                counter_digits[i].stop_frame = 2;
            flags &= ~4u;
        }
    }

    if (flags & 2) {
        int value = bonus;
        int divisor = 10000000;
        for (int i = 0; i < 8; ++i) {
            Configure(&bonus_digits[i], value / divisor + 30);
            RunAnimationVm(&bonus_digits[i]);
            value %= divisor;
            divisor /= 10;
        }
    } else {
        Configure(&bonus_digits[2], 41);
        RunAnimationVm(&bonus_digits[2]);
    }

    int count = data_0047783c->shots[g_selection.shot_type + g_selection.character * 3]
        .spells[record_index].attempts;
    if (count >= 100)
        count = 99;
    Configure(&counter_digits[0], count / 10 + 30);
    Configure(&counter_digits[1], count % 10 + 30);
    count = data_0047783c->shots[g_selection.shot_type + g_selection.character * 3]
        .spells[record_index].captures;
    if (count >= 100)
        count = 99;
    Configure(&counter_digits[3], count / 10 + 30);
    Configure(&counter_digits[4], count % 10 + 30);
    for (int j = 0; j < 5; ++j)
        RunAnimationVm(&counter_digits[j]);

    marker_position += (data_00477704->target->position - marker_position) * 0.05f;
    SetAnimationTranslatedPosition_00449350(
        reinterpret_cast<const PositionVector_004492f0*>(&marker_position), data_00491c10, marker_handle);
    return 1;
}
#pragma code_seg()

#pragma code_seg(".text$a01callback")
extern "C" int __fastcall CardPrimary_00409220(Card_00408d60* hud) {
    return hud->Update();
}
#pragma code_seg()
