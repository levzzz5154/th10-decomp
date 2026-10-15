// Checked score HUD and animation views for the complete native call graph.
#pragma once
#include <stddef.h>
#include "th10/math/timer.hpp"
#include "th10/game/entity.hpp"
#include "th10/render/animation_object_0043e5a0.hpp"
#include "th10/render/animation_handle.hpp"
#include "th10/platform/sound_queue.hpp"

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
extern "C" ResultAnimationLookup* g_sprt_ctrl;

// An animation a game object owns, named by its id.
struct ResultAnimationHandle {
    ResultAnimationId id;

    // Let the manager dispose of the animation and forget it.
    void Release() {
        ResultAnimation_Retire(g_sprt_ctrl, id);
        id.value = 0;
    }
};


struct HudFlagWord {
    union { unsigned int value; unsigned char bytes[4]; };
    HudFlagWord& operator|=(unsigned int bits) { value |= bits; return *this; }
};
struct HudLifeIcon { unsigned int flags; unsigned char reserved_04[0x3AC-4]; };
struct FrontScoreView {
    unsigned char reserved_00[0x10];
    Entity animations[20];
    unsigned char reserved_4980[0x4CDC-0x4980];
    HudLifeIcon life_icons[9];
    unsigned char reserved_6de8[0x9DF4-0x6DE8];
    ResultAnimationId digits[8];
    ResultAnimationHandle caption;
    ResultAnimationHandle secondary;
    unsigned char reserved_9e1c[0x9E64-0x9E1C];
    int stage_frame;
    unsigned char reserved_9e68[0x9E74-0x9E68];
    int previous_high_score;
    int displayed_score;
    int score_velocity;
    unsigned char reserved_9e80[0x9EB4-0x9E80];
    HudFlagWord flags;
    unsigned char reserved_9eb8[0x9EC8-0x9EB8];
    void* captions;
    __declspec(noinline) void Update();
    __declspec(noinline) void SetActiveCount(int count);
};
typedef char HudHigh[offsetof(FrontScoreView,animations)==0x10?1:-1];
typedef char HudScore[offsetof(FrontScoreView,animations)+10*sizeof(Entity)==0x24C8?1:-1];
typedef char HudFrame[offsetof(FrontScoreView,stage_frame)==0x9E64?1:-1];
typedef char HudDisplayed[offsetof(FrontScoreView,displayed_score)==0x9E78?1:-1];
typedef char HudFlags[offsetof(FrontScoreView,flags)==0x9EB4?1:-1];
typedef char HudResource[offsetof(FrontScoreView,captions)==0x9EC8?1:-1];
// 0x00448D00: create a front animation from a file's script.
__declspec(noinline) ResultAnimationId __stdcall ResultAnimation_CreatePrimary(void* file, int script, int layer);

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

struct HudGameState {
    int high_score;               // 0x00474C40
    int score;                    // 0x00474C44
    short word_08;                // 0x00474C48
    int gauge;                    // 0x00474C4C
    int gauge_decay;
    FrameTimer gauge_timer;       // 0x00474C54
    int character;                // 0x00474C68
    int shot_type;                // 0x00474C6C
    int lives;                    // 0x00474C70
    int difficulty;               // 0x00474C74
    int field_38;
    int stage;                    // 0x00474C7C
    int stage_shown;              // 0x00474C80
    int reserved_44[3];
    int continues;                // 0x00474C90
    int high_score_continues;     // 0x00474C94
    int field_58;                 // 0x00474C98
    int next_extend;                 // 0x00474C9C
    HudFlagWord flags;           // 0x00474CA0
    int reserved_64[2];
    int initial_lives;            // 0x00474CAC

    // 0x004188A0: award lives and refresh the HUD.
    __declspec(noinline) void AddLives(int amount);
};
typedef char GameStateField5c[offsetof(HudGameState, next_extend) == 0x5C ? 1 : -1];


extern "C" HudGameState g_globals;
extern "C" FrontScoreView* g_front;
extern "C" const int g_next_extend_score[5];
extern "C" const int g_next_extend_score_2[5];
extern "C" int __stdcall HudTickAnimation(Entity* object);
