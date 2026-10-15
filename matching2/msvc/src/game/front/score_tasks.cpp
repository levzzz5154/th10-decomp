// 0x00413A20..0x00413B40: initialize the task's cached and archive resources.
#include <stddef.h>
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

#include <string.h>

#include "th10/platform/archive_file.hpp"

extern "C" void* __fastcall LoadCachedResource(
    int index, void* owner, const char* name);

struct TextLog_0044b810 {
    char text[0x2000];
    char* cursor;
    unsigned char dirty;
    char* Append(char* format, ...);
};

struct ScoreTaskResourceNames {
    unsigned char reserved_0000[0x18];
    const char* archive_paths[2];      // +0x18, +0x1C, selected by g_globals_character
    const char* cached_resource_name;  // +0x20
};

typedef char ScoreTaskResourceNames_00413a20_offsets_check[
    offsetof(ScoreTaskResourceNames, archive_paths) == 0x18 &&
    offsetof(ScoreTaskResourceNames, cached_resource_name) == 0x20
        ? 1 : -1];

extern "C" float g_game_speed;
extern "C" TextLog_0044b810 g_log;
extern "C" char str_data_corrupted[];

// The addressed bytes are linker-owned game globals. Their uses here match
// the pointer/dword operations at 0x00413A20, without naming their owners.
extern "C" {
extern ScoreTaskResourceNames* g_stage_route_current;
extern unsigned int g_globals_score;
extern int g_globals_character;
extern void* g_next_stage_buffer;
extern void* g_sprt_ctrl;
extern char g_recovery_script_path[];
}

struct ScoreTaskClock {
    int previous_frame;
    int current_frame;
    float elapsed;
    const float* speed;
    unsigned int flags;
    __forceinline void Reset() {
        if ((flags & 1u) == 0) {
            current_frame = 0;
            previous_frame = -999999;
            elapsed = 0.0f;
            speed = &g_game_speed;
            flags |= 1u;
        }
        current_frame = 0;
        elapsed = 0.0f;
        // Pin the two zero stores before the previous-frame sentinel.
        _ReadWriteBarrier();
        previous_frame = -1;
    }
};

typedef char ScoreTaskClock_00413a20_size_check[
    sizeof(ScoreTaskClock) == 0x14 ? 1 : -1];

struct FrontResourcesView {
    unsigned char reserved_0000[0x9e60];
    ScoreTaskClock clock;
    unsigned char reserved_9e74[4];
    unsigned int field_9e78;
    unsigned char reserved_9e7c[4];
    void* cached_resource_9e80;
    unsigned char reserved_9e84[0x38];
    void* archive_buffer_9ebc;
    unsigned int field_9ec0;
    unsigned int field_9ec4;
};

typedef char FrontResourcesView_field_offsets_are_correct[
    (offsetof(FrontResourcesView, clock) == 0x9e60 &&
     offsetof(FrontResourcesView, cached_resource_9e80) == 0x9e80 &&
     offsetof(FrontResourcesView, archive_buffer_9ebc) == 0x9ebc &&
     offsetof(FrontResourcesView, field_9ec4) == 0x9ec4)
        ? 1
        : -1];

static void LogResourceLoadFailure() {
    g_log.Append(str_data_corrupted);
}

// Public stdcall task callback: state pointer on the stack and result in EAX.
// Legacy callers retain their fixed-address assembly symbol alias.
#pragma code_seg(".text$02xscore")
extern "C" __declspec(noinline) int __stdcall ScoreTask_Setup(
    FrontResourcesView* state) {

    void*& cached_resource = state->cached_resource_9e80;
    cached_resource =
        LoadCachedResource(0x1c, g_sprt_ctrl,
                                   g_stage_route_current->cached_resource_name);
    if (!cached_resource) {
        LogResourceLoadFailure();
        return -1;
    }

    void* preloaded_buffer = g_next_stage_buffer;
    if (preloaded_buffer) {
        state->archive_buffer_9ebc = preloaded_buffer;
        g_next_stage_buffer = 0;
    } else {
        const int path_index = g_globals_character;
        ScoreTaskResourceNames* resource_names = g_stage_route_current;
        const char* path_suffix = resource_names->archive_paths[path_index];
        char* path = g_recovery_script_path;
        path[0] = '\0';
        strcat(path, path_suffix);
        state->archive_buffer_9ebc = Archive_LoadFile(path, 0, 0);
        if (!state->archive_buffer_9ebc) {
            LogResourceLoadFailure();
            return -1;
        }
    }

    state->clock.Reset();
    // Keep the source counter load after the clock reset.
    // Compiler barriers preserve scheduling and emit no instructions.
    _ReadWriteBarrier();
    state->field_9ec0 = 0xffffffff;
    state->field_9ec4 = 0xffffffff;
    state->field_9e78 = g_globals_score;
    return 0;
}

#pragma code_seg()
