#pragma once
// The per-stage game state (0x2B64 bytes): the stage script loader at its
// head, the stage timers, two arrays of animated entities, the three scheduler
// tasks that drive it and a snapshot of the camera it renders with.
#include <stddef.h>
#include <string.h>
#include "th10/game/entity.hpp"
#include "th10/game/scheduler.hpp"
#include "th10/math/timer.hpp"
#include "th10/render/camera_batch.hpp"

// A compiler context that only needs the state's layout defines
// TH10_GAME_STATE_LAYOUT_ONLY and sees plain members, so its stand-in
// constructor and destructor carry no member construction or unwind tables.
#ifdef TH10_GAME_STATE_LAYOUT_ONLY
typedef FrameTimer GameStateTimer;
typedef Entity GameStateEntity;
#else
// A frame timer that starts out uninitialised (first Set() fills it in).
struct GameStateTimer : FrameTimer {
    GameStateTimer() { flags &= ~1u; }
};

// 0x00402050 / 0x00401FF0
struct GameStateEntity : Entity {
    GameStateEntity();
    ~GameStateEntity();
};
#endif

struct GameCameraSnapshot_00402230 { RenderCamera camera; char extra[0x118-sizeof(RenderCamera)]; };

struct GameState_00402230 {
    unsigned int flags;
    unsigned int reserved_0004;
    SchedulerTask* primary;
    SchedulerTask* secondary;
    void* block_0010;
    unsigned char reserved_0014[0x24 - 0x14];
    GameStateTimer timer_0024;
    GameStateTimer timer_0038;
    unsigned char reserved_004c[0x80 - 0x4c];
    GameStateTimer timer_0080;
    int value_094;
    unsigned char reserved_0098[0xcc - 0x98];
    GameStateTimer timer_00cc;
    int value_0e0;
    unsigned char reserved_00e4[0x158 - 0xe4];
    GameStateTimer timer_0158;
    unsigned char reserved_016c[0x17c - 0x16c];
    void* block_017c;
    GameStateEntity entities_0180[8];
    float frame_limit;
    unsigned char reserved_1ee4[0x1f08 - 0x1ee4];
    GameStateEntity entities_1f08[3];
    unsigned char reserved_2a0c[0x2a18 - 0x2a0c];
    unsigned int state_flags;
    GameStateTimer timer_2a1c;
    unsigned int stage_flags;
    int initialization_frame;
    unsigned char reserved_2a38[8];
    SchedulerTask* after_draw;
    void* block_2a44;
    unsigned char reserved_2a48[4];
    GameCameraSnapshot_00402230 camera;

    __declspec(noinline) GameState_00402230();
    __declspec(noinline) ~GameState_00402230();
};

typedef char GameStateEntitySizeCheck[sizeof(GameStateEntity)==0x3ac?1:-1];
typedef char GameStateTimerOffsetCheck[offsetof(GameState_00402230,timer_0038)==0x38?1:-1];
typedef char GameStateEntitiesOffsetCheck[offsetof(GameState_00402230,entities_0180)==0x180?1:-1];
typedef char GameStateFrameLimitOffsetCheck[offsetof(GameState_00402230,frame_limit)==0x1ee0?1:-1];
typedef char GameStateEntities2OffsetCheck[offsetof(GameState_00402230,entities_1f08)==0x1f08?1:-1];
typedef char GameStateFlagsOffsetCheck[offsetof(GameState_00402230,state_flags)==0x2a18?1:-1];
typedef char GameStateStageFlagsOffsetCheck[offsetof(GameState_00402230,stage_flags)==0x2a30?1:-1];
typedef char GameStateAfterDrawOffsetCheck[offsetof(GameState_00402230,after_draw)==0x2a40?1:-1];
typedef char GameCameraSnapshotSizeCheck[sizeof(GameCameraSnapshot_00402230)==0x118?1:-1];
typedef char GameStateCameraOffsetCheck[offsetof(GameState_00402230,camera)==0x2a4c?1:-1];
typedef char GameStateSizeCheck[sizeof(GameState_00402230)==0x2b64?1:-1];

extern "C" {
extern GameState_00402230* data_004776e4;
extern GameState_00402230* data_004776e8;
int __stdcall InitializeGameState_00402230(GameState_00402230* state, const char* name, int state_id);
}
