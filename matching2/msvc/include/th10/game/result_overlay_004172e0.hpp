// Checked animation and overlay views for the complete native call graph.
#pragma once
#include <stddef.h>
#include "th10/game/entity.hpp"
#include "th10/render/animation_object_0043e5a0.hpp"
#include "th10/render/animation_handle.hpp"
#include "th10/platform/sound_queue.hpp"

// The stage interface at 0x004776E8, as far as the spell card touches it.
struct CardInterface_00409c00 {
    unsigned char reserved_0000[0x2A18];
    unsigned int flags;            // +0x2A18, bit 0: the spell card banner is leaving
};

struct ResultAnimationLookup;
// An animation's id. The user-declared constructors make functions return it
// through a caller-provided slot.
struct ResultAnimationId {
    unsigned int value;

    ResultAnimationId() {}
    ResultAnimationId(unsigned int id) : value(id) {}
    ResultAnimationId& operator++() { ++value; return *this; }
    bool operator==(ResultAnimationId other) const { return value == other.value; }
    __declspec(noinline) void Show();
    __declspec(noinline) void Hide();
};
// 0x004492A0: let the animation with this id, and its children, be removed.
void* __fastcall ResultAnimation_Retire(ResultAnimationLookup* context, ResultAnimationId id);
extern "C" ResultAnimationLookup* data_00491c10;

// An animation a game object owns, named by its id.
struct ResultAnimationHandle {
    ResultAnimationId id;

    // Let the manager dispose of the animation and forget it.
    void Release() {
        ResultAnimation_Retire(data_00491c10, id);
        id.value = 0;
    }
};

// The front-layer manager at 0x0047770C, which owns the bonus caption.
struct ResultOverlayState_004172e0 {
    unsigned char reserved_0000[0x9DF4];
    ResultAnimationId digits[8];
    ResultAnimationHandle caption;   // +0x9E14
    ResultAnimationHandle secondary;
    unsigned char reserved_9e1c[0x9EC8 - 0x9E1C];
    void* captions;                // +0x9EC8, animation file
};
// 0x004172E0: show a caption of the given kind with a number; 0 is the spell
// card bonus.
__declspec(noinline) void __stdcall ResultOverlay_SetMode(int kind, ResultOverlayState_004172e0* front, int number);
// 0x00448D00: create a front animation from a file's script.
__declspec(noinline) ResultAnimationId __stdcall ResultAnimation_CreatePrimary(void* file, int script, int layer);

// The following partial views support the complete real spell-end compiler
// context. Its existing separately recovered production owner is unchanged.

// The running game's counters at 0x00474C44.
struct CardGame_00409c00 {
    int score;                     // +0x00
    unsigned char reserved_04[0x20];
    int character;                 // +0x24
    int shot_type;                 // +0x28
};

// The play mode record at 0x00477838; mode 1 keeps the score file untouched.
struct CardMode_00409c00 {
    unsigned char reserved_00[0x10];
    int mode;
};

// The score file at 0x0047783C: per shot type, and once more for all of them,
// a history of every spell card.
struct CardHistory_00409c00 {
    unsigned char reserved_00[0x80];
    int captures;                  // +0x80
    unsigned char reserved_84[0x90 - 0x84];
};
struct CardShotScores_00409c00 {
    CardHistory_00409c00 spells[119];
    unsigned char reserved_42f0[0x437C - 0x42F0];
};
struct CardScoreFile_00409c00 {
    unsigned char reserved_000[0x5A4];
    CardShotScores_00409c00 shots[7];   // six shot types, then the total
};
typedef char CardShotScoresSize_00409c00[sizeof(CardShotScores_00409c00) == 0x437C ? 1 : -1];

// The spell card state at 0x004776F4.
struct ResultCard_00409c00 {
    unsigned char reserved_0000[0x768];
    AnimationHandle effects[3];    // +0x768
    ResultAnimationHandle name;      // +0x774, the name banner
    unsigned char reserved_0778[0x3788 - 0x778];
    int spell_id;                  // +0x3788
    unsigned int flags;            // +0x378C, bit 0 active, bit 1 still capturable
    int bonus;                     // +0x3790

    __declspec(noinline) void End();
};
typedef char CardFlagsOffset_00409c00[offsetof(ResultCard_00409c00, flags) == 0x378C ? 1 : -1];

extern "C" {
extern CardInterface_00409c00* data_004776e8;
extern ResultOverlayState_004172e0* data_0047770c;
extern CardMode_00409c00* data_00477838;
extern CardScoreFile_00409c00* data_0047783c;
extern CardGame_00409c00 data_00474c44;
}

struct ResultAnimationPool {
    unsigned char header[0x68];
    Entity objects[4096];
    unsigned char occupied[4096];
    int next_slot;
    __declspec(noinline) Entity* Allocate();
};
struct ResultAnimationResource {
    __declspec(noinline) void InitializeObject(Entity* object, int index);
};
struct CaptionNode { Entity* object; CaptionNode* next; CaptionNode* previous; };
struct ResultAnimationLists {
    unsigned char reserved[0x72DAD4];
    CaptionNode* primary_head;
    CaptionNode* primary_tail;
    unsigned char reserved_72dadc[0x732454-0x72DADC];
    ResultAnimationId next_id;
    __declspec(noinline) ResultAnimationId RegisterPrimaryBack(Entity* object);
};
__declspec(noinline) void __stdcall Entity_Init(Entity* entity);
Entity* __fastcall Entity_Constructor(Entity* entity);
void* __cdecl operator new(unsigned int size);

typedef char ResultDigitOffset[offsetof(ResultOverlayState_004172e0,digits)==0x9DF4?1:-1];
typedef char ResultMainCaptionOffset[offsetof(ResultOverlayState_004172e0,caption)==0x9E14?1:-1];
typedef char ResultSecondaryCaptionOffset[offsetof(ResultOverlayState_004172e0,secondary)==0x9E18?1:-1];
typedef char ResultCaptionResourceOffset[offsetof(ResultOverlayState_004172e0,captions)==0x9EC8?1:-1];
typedef char ResultPoolObjectOffset[offsetof(ResultAnimationPool,objects)==0x68?1:-1];
typedef char ResultPoolBusyOffset[offsetof(ResultAnimationPool,occupied)==0x3AC068?1:-1];
typedef char ResultPoolCursorOffset[offsetof(ResultAnimationPool,next_slot)==0x3AD068?1:-1];
typedef char ResultListIdOffset[offsetof(ResultAnimationLists,next_id)==0x732454?1:-1];
