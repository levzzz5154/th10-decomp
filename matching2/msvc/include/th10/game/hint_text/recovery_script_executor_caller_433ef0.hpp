#ifndef TH10_RECOVERY_SCRIPT_EXECUTOR_CALLER_00433EF0_HPP
#define TH10_RECOVERY_SCRIPT_EXECUTOR_CALLER_00433EF0_HPP

#include <stddef.h>
#include "th10/game/title_input.hpp"
#include "th10/game/hint_text/recovery_script_executor.hpp"

struct TitleVec3 { float x, y, z; };
struct TitleAnmVm;
struct TitleAnmChild {
    TitleAnmVm* object;
    TitleAnmChild* next;
};
struct TitleAnmVm {
    unsigned int id;
    unsigned char reserved_004[0x10];
    TitleAnmChild* children;
    int children_flagged;
    unsigned int reserved_01c;
    int render_bucket;
    unsigned char reserved_024[0x70 - 0x24];
    TitleVec3 base_transition;
    TitleVec3 target_transition;
    TitleVec3 defaults_088;
    TitleVec3 defaults_094;
    GameFrameTimer transition_timer;
    int transition_mode;
    unsigned int transition_flag;
    unsigned char reserved_0bc[0x304 - 0xBC];
    unsigned short stop_frame;
    unsigned char reserved_306[0x334 - 0x306];
    TitleVec3 position;
    unsigned char reserved_340[0x35C - 0x340];
    unsigned int flags;

    __declspec(noinline) void InitializeTransition(
        const TitleVec3* base,
        const TitleVec3* target, int mode, unsigned char flag);
};

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
    GameFrameTimer timer;
    AnimationScriptId animation_slots[195]; // +2C4 through +5CC
    AnmScriptHandle fallback_handle;
    unsigned char reserved_5d4[0x614 - 0x5D4];
    AnmScriptHandle row_handles[20];
    AnmScriptHandle preview_handles[8];
    unsigned int reserved_684;
    int parsed_track_count;
    int preview_cursor;
    int displayed_track;
    int preview_armed;
    char titles[32][64];
    char comments[32][66];
    char preview_lines[32][8][66];
    int scroll_origin;
    TitleNameKeyboard keyboard;
    short edited_key_bindings[5];
    unsigned char reserved_59d6[2];
    TitleReplayList replay_list;
    char* file_buffer;

    __declspec(noinline) void SetTimerTarget(int target);
    __declspec(noinline) int OnUpdate();
    __declspec(noinline) void DisableTimerWithOwner(int owner);
    __declspec(noinline) void ClearAnimationSlot(int index);
    __declspec(noinline) void SetSlotFrame(int index, unsigned short frame);
};

struct MusicRequestQueue {
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
typedef char TitleKeyboardOffset[offsetof(Title, keyboard) == 0x58DC ? 1 : -1];
typedef char TitleBindingsOffset[offsetof(Title, edited_key_bindings) == 0x59CC ? 1 : -1];
typedef char TitleReplayListOffset[offsetof(Title, replay_list) == 0x59D8 ? 1 : -1];
typedef char RecoveryMusicRoomBufferCheck[offsetof(Title,file_buffer)==0x5AAC?1:-1];
typedef char RecoveryMusicVmDepthCheck[offsetof(TitleAnmVm,stop_frame)==0x304?1:-1];
typedef char RecoveryMusicVmPositionCheck[offsetof(TitleAnmVm,position)==0x334?1:-1];
typedef char RecoveryMusicVmFlagsCheck[offsetof(TitleAnmVm,flags)==0x35C?1:-1];

extern "C" __declspec(noinline) int __stdcall Title_UpdateMusicRoom(
    Title* room);

#endif
