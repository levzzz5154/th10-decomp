#pragma once
#include <stddef.h>
#include "th10/render/animation_handle.hpp"
#include "th10/platform/sound_queue.hpp"

// The stage interface at 0x004776E8, as far as the spell card touches it.
struct CardInterface {
    unsigned char reserved_0000[0x2A18];
    unsigned int flags;            // +0x2A18, bit 0: the spell card banner is leaving
};

struct AnimationLookupContext;
// An animation's id. The user-declared constructors make functions return it
// through a caller-provided slot.
struct AnimationScriptId {
    int value;

    AnimationScriptId() {}
    AnimationScriptId(int id) : value(id) {}
};
// 0x004492A0: let the animation with this id, and its children, be removed.
void* __fastcall AnimationManager_SetFlag2(AnimationLookupContext* context, AnimationScriptId id);
extern "C" AnimationLookupContext* g_sprt_ctrl;

// An animation a game object owns, named by its id.
struct CardAnimation2 {
    AnimationScriptId id;

    // Let the manager dispose of the animation and forget it.
    void Release() {
        AnimationManager_SetFlag2(g_sprt_ctrl, id);
        id.value = 0;
    }
};

// The front-layer manager at 0x0047770C, which owns the bonus caption.
struct CardFront {
    unsigned char reserved_0000[0x9E14];
    CardAnimation2 caption;   // +0x9E14
    unsigned char reserved_9e18[0x9EC8 - 0x9E18];
    void* captions;                // +0x9EC8, animation file
};
// 0x004172E0: show a caption of the given kind with a number; 0 is the spell
// card bonus.
__declspec(noinline) void __stdcall Card_ShowCaption(int kind, CardFront* front, int number);
// 0x00448D00: create a front animation from a file's script.
__declspec(noinline) AnimationScriptId __stdcall Card_CreateAnimation(void* file, int script, int layer);

// The running game's counters at 0x00474C44.
struct CardGame {
    int score;                     // +0x00
    unsigned char reserved_04[0x20];
    int character;                 // +0x24
    int shot_type;                 // +0x28
};

// The play mode record at 0x00477838; mode 1 keeps the score file untouched.
struct CardMode {
    unsigned char reserved_00[0x10];
    int mode;
};

// The score file at 0x0047783C: per shot type, and once more for all of them,
// a history of every spell card.
struct CardHistory {
    unsigned char reserved_00[0x80];
    int captures;                  // +0x80
    unsigned char reserved_84[0x90 - 0x84];
};
struct CardShotScores {
    CardHistory spells[119];
    unsigned char reserved_42f0[0x437C - 0x42F0];
};
struct CardScoreFile {
    unsigned char reserved_000[0x5A4];
    CardShotScores shots[7];   // six shot types, then the total
};
typedef char CardShotScoresSize[sizeof(CardShotScores) == 0x437C ? 1 : -1];

// The spell card state at 0x004776F4.
struct Card5 {
    unsigned char reserved_0000[0x768];
    AnimationHandle effects[3];    // +0x768
    CardAnimation2 name;      // +0x774, the name banner
    unsigned char reserved_0778[0x3788 - 0x778];
    int spell_id;                  // +0x3788
    unsigned int flags;            // +0x378C, bit 0 active, bit 1 still capturable
    int bonus;                     // +0x3790

    __declspec(noinline) void End();
};
typedef char CardFlagsOffset[offsetof(Card5, flags) == 0x378C ? 1 : -1];

extern "C" {
extern CardInterface* g_background;
extern CardFront* g_front;
extern CardMode* g_replay;
extern CardScoreFile* g_score;
extern CardGame g_globals_score;
}
