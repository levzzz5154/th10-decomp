#ifndef TH10_RECOVERY_SCRIPT_EXECUTOR_CALLER_00433EF0_HPP
#define TH10_RECOVERY_SCRIPT_EXECUTOR_CALLER_00433EF0_HPP

#include <stddef.h>
#include "th10/game/menu_cursor.hpp"
#include "th10/game/recovery_script_executor_0040bd80.hpp"

struct RecoveryMusicVector_00433ef0 { float x, y, z; };
struct RecoveryMusicVm_00433ef0;
struct RecoveryMusicChild_00433ef0 {
    RecoveryMusicVm_00433ef0* object;
    RecoveryMusicChild_00433ef0* next;
};
struct RecoveryMusicVm_00433ef0 {
    unsigned int id;
    unsigned char reserved_004[0x10];
    RecoveryMusicChild_00433ef0* children;
    int children_flagged;
    unsigned int reserved_01c;
    int render_bucket;
    unsigned char reserved_024[0x70 - 0x24];
    RecoveryMusicVector_00433ef0 base_transition;
    RecoveryMusicVector_00433ef0 target_transition;
    RecoveryMusicVector_00433ef0 defaults_088;
    RecoveryMusicVector_00433ef0 defaults_094;
    RecoveryTimer_0040bd80 transition_timer;
    int transition_mode;
    unsigned int transition_flag;
    unsigned char reserved_0bc[0x304 - 0xBC];
    unsigned short stop_frame;
    unsigned char reserved_306[0x334 - 0x306];
    RecoveryMusicVector_00433ef0 position;
    unsigned char reserved_340[0x35C - 0x340];
    unsigned int flags;

    __declspec(noinline) void InitializeTransition(
        const RecoveryMusicVector_00433ef0* base,
        const RecoveryMusicVector_00433ef0* target, int mode, unsigned char flag);
};

extern "C" float g_game_speed;

#pragma code_seg(push, ".text$0042c620_fn")
// This view ends at the last word used by the complete music-room handler.
// The 20 row-handle slots and 32 text records follow the retail offsets; the
// handler's parser and loops deliberately have no additional bounds guards.
struct Title {
    unsigned char reserved_000[0x14];
    void* animation_resource;
    unsigned int reserved_018;
    int timer_owner;
    int phase;
    MenuCursor cursor;
    unsigned char reserved_0fc[0x2B0 - 0xFC];
    RecoveryTimer_0040bd80 timer;
    unsigned int animation_slots[195]; // +2C4 through +5CC
    RecoveryHandle_0040bd80 fallback_handle;
    unsigned char reserved_5d4[0x614 - 0x5D4];
    RecoveryHandle_0040bd80 row_handles[20];
    RecoveryHandle_0040bd80 preview_handles[8];
    unsigned int reserved_684;
    int parsed_track_count;
    int preview_cursor;
    int displayed_track;
    int preview_armed;
    char titles[32][64];
    char comments[32][66];
    char preview_lines[32][8][66];
    int scroll_origin;
    unsigned char reserved_58dc[0x5AAC - 0x58DC];
    char* file_buffer;

    // 0x0042C620.  Defined in the class, as in the image: the compiler keeps
    // no register summary for the out-of-line copy of an in-class member, so
    // callers reload the room after it (0x0042D6DF).
    __declspec(noinline) void SetTimerTarget(int target) {
        phase = target;
        if (!(timer.flags & 1u)) {
            timer.current = 0;
            timer.previous = -999999;
            timer.elapsed = 0;
            timer.speed = &g_game_speed;
            timer.flags |= 1u;
        }
        timer.current = 0;
        timer.elapsed = 0;
        timer.previous = -1;
    }
    __declspec(noinline) int OnUpdate();
    __declspec(noinline) void DisableTimerWithOwner(int owner);
    __declspec(noinline) void ClearAnimationSlot(int index);
    __declspec(noinline) void SetSlotFrame(int index, short frame);
};

#pragma code_seg(pop)

struct RecoveryMusicResourceQueue_0043e460 {
    __declspec(noinline) char* RegisterResource(const char* name, int kind, int parameter);
};

typedef char RecoveryMusicRoomSizeCheck[sizeof(Title)==0x5AB0?1:-1];
typedef char RecoveryMusicRoomCursorCheck[offsetof(Title,cursor)==0x24?1:-1];
typedef char RecoveryMusicRoomTimerCheck[offsetof(Title,timer)==0x2B0?1:-1];
typedef char RecoveryMusicRoomSlotsCheck[offsetof(Title,animation_slots)==0x2C4?1:-1];
typedef char RecoveryMusicRoomFallbackCheck[offsetof(Title,fallback_handle)==0x5D0?1:-1];
typedef char RecoveryMusicRoomRowsCheck[offsetof(Title,row_handles)==0x614?1:-1];
typedef char RecoveryMusicRoomPreviewCheck[offsetof(Title,preview_handles)==0x664?1:-1];
typedef char RecoveryMusicRoomTitlesCheck[offsetof(Title,titles)==0x698?1:-1];
typedef char RecoveryMusicRoomCommentsCheck[offsetof(Title,comments)==0xE98?1:-1];
typedef char RecoveryMusicRoomLinesCheck[offsetof(Title,preview_lines)==0x16D8?1:-1];
typedef char RecoveryMusicRoomScrollCheck[offsetof(Title,scroll_origin)==0x58D8?1:-1];
typedef char RecoveryMusicRoomBufferCheck[offsetof(Title,file_buffer)==0x5AAC?1:-1];
typedef char RecoveryMusicVmDepthCheck[offsetof(RecoveryMusicVm_00433ef0,stop_frame)==0x304?1:-1];
typedef char RecoveryMusicVmPositionCheck[offsetof(RecoveryMusicVm_00433ef0,position)==0x334?1:-1];
typedef char RecoveryMusicVmFlagsCheck[offsetof(RecoveryMusicVm_00433ef0,flags)==0x35C?1:-1];

extern "C" __declspec(noinline) int __stdcall Title_UpdateMusicRoom(
    Title* room);

#endif
