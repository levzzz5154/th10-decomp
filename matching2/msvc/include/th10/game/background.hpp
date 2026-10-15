#pragma once
// BackGround (background.cpp), the per-stage background (0x2B64 bytes): the stage script loader at its
// head, the stage timers, two arrays of animated entities, the three scheduler
// tasks that drive it and a snapshot of the camera it renders with.
#include <stddef.h>
#include <string.h>
#include "th10/game/entity.hpp"
#include "th10/core/func_ctrl.hpp"
#include "th10/math/timer.hpp"
#include "th10/render/camera_batch.hpp"

// A compiler context that only needs the state's layout defines
// TH10_BACKGROUND_LAYOUT_ONLY and sees plain members, so its stand-in
// constructor and destructor carry no member construction or unwind tables.
#ifdef TH10_BACKGROUND_LAYOUT_ONLY
typedef FrameTimer BackGroundTimer;
typedef Entity BackGroundEntity;
#else
// A frame timer that starts out uninitialised (first Set() fills it in).
struct BackGroundTimer : FrameTimer {
    BackGroundTimer() { flags &= ~1u; }
};

// 0x00402050 / 0x00401FF0
struct BackGroundEntity : Entity {
    BackGroundEntity();
    ~BackGroundEntity();
};
#endif

struct BackGroundCameraSnapshot { RenderCamera camera; char extra[0x118-sizeof(RenderCamera)]; };

struct BackGroundFile {
    short sub_count, instance_count;
    unsigned int timeline_offset, auxiliary_offset;
    char reserved_0c[4];
    char animation_name[0x80];
    unsigned int sub_offsets[1];
};

struct BackGround {
    unsigned int flags;
    unsigned int reserved_0004;
    SchedulerTask* primary;
    SchedulerTask* secondary;
    BackGroundFile* file;
    unsigned int* subroutines;
    char* timeline;
    char* auxiliary;
    unsigned char reserved_0020[4];
    BackGroundTimer timer_0024;
    BackGroundTimer timer_0038;
    unsigned char reserved_004c[0x80 - 0x4c];
    BackGroundTimer timer_0080;
    int value_094;
    unsigned char reserved_0098[0xcc - 0x98];
    BackGroundTimer timer_00cc;
    int value_0e0;
    unsigned char reserved_00e4[0x158 - 0xe4];
    BackGroundTimer timer_0158;
    unsigned char reserved_016c[0x178 - 0x16c];
    void* animation;
    void* instances;
    BackGroundEntity entities_0180[8];
    float frame_limit;
    unsigned char reserved_1ee4[0x1f08 - 0x1ee4];
    BackGroundEntity entities_1f08[3];
    unsigned char reserved_2a0c[0x2a18 - 0x2a0c];
    unsigned int state_flags;
    BackGroundTimer timer_2a1c;
    unsigned int stage_flags;
    int initialization_frame;
    unsigned char reserved_2a38[8];
    SchedulerTask* after_draw;
    char* original;
    int file_size;
    BackGroundCameraSnapshot camera;

    __declspec(noinline) BackGround();
    __declspec(noinline) ~BackGround();
    __declspec(noinline) int Load(const char* name);
    __declspec(noinline) int LoadNormalized(const char* name);
};

typedef char BackGroundFileOffsetCheck[offsetof(BackGround,file)==0x10?1:-1];
typedef char BackGroundAnimationOffsetCheck[offsetof(BackGround,animation)==0x178?1:-1];
typedef char BackGroundOriginalOffsetCheck[offsetof(BackGround,original)==0x2a44?1:-1];
typedef char BackGroundFileSizeOffsetCheck[offsetof(BackGround,file_size)==0x2a48?1:-1];
typedef char BackGroundEntitySizeCheck[sizeof(BackGroundEntity)==0x3ac?1:-1];
typedef char BackGroundTimerOffsetCheck[offsetof(BackGround,timer_0038)==0x38?1:-1];
typedef char BackGroundEntitiesOffsetCheck[offsetof(BackGround,entities_0180)==0x180?1:-1];
typedef char BackGroundFrameLimitOffsetCheck[offsetof(BackGround,frame_limit)==0x1ee0?1:-1];
typedef char BackGroundEntities2OffsetCheck[offsetof(BackGround,entities_1f08)==0x1f08?1:-1];
typedef char BackGroundFlagsOffsetCheck[offsetof(BackGround,state_flags)==0x2a18?1:-1];
typedef char BackGroundStageFlagsOffsetCheck[offsetof(BackGround,stage_flags)==0x2a30?1:-1];
typedef char BackGroundAfterDrawOffsetCheck[offsetof(BackGround,after_draw)==0x2a40?1:-1];
typedef char BackGroundCameraSnapshotSizeCheck[sizeof(BackGroundCameraSnapshot)==0x118?1:-1];
typedef char BackGroundCameraOffsetCheck[offsetof(BackGround,camera)==0x2a4c?1:-1];
typedef char BackGroundSizeCheck[sizeof(BackGround)==0x2b64?1:-1];

extern "C" {
extern BackGround* g_background_prev;
extern BackGround* g_background;
int __stdcall BackGround_Initialize(BackGround* state, const char* name, int state_id);
}
