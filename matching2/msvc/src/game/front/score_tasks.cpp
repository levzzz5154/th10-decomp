// 0x00413A20..0x00413B40: initialize the task's cached and archive resources.
#include <stddef.h>
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

#include <string.h>

#include "th10/platform/archive_file.hpp"

extern "C" void* __fastcall LoadCachedResource_00447280(
    int index, void* owner, const char* name);

struct TextLog_0044b810 {
    char text[0x2000];
    char* cursor;
    unsigned char dirty;
    char* Append(char* format, ...);
};

struct ScoreTaskResourceNames_00413a20 {
    unsigned char reserved_0000[0x18];
    const char* archive_paths[2];      // +0x18, +0x1C, selected by data_00474c68
    const char* cached_resource_name;  // +0x20
};

typedef char ScoreTaskResourceNames_00413a20_offsets_check[
    offsetof(ScoreTaskResourceNames_00413a20, archive_paths) == 0x18 &&
    offsetof(ScoreTaskResourceNames_00413a20, cached_resource_name) == 0x20
        ? 1 : -1];

extern "C" float g_game_speed;
extern "C" TextLog_0044b810 g_log;
extern "C" char data_0046cb68[];

// The addressed bytes are linker-owned game globals. Their uses here match
// the pointer/dword operations at 0x00413A20, without naming their owners.
extern "C" {
extern ScoreTaskResourceNames_00413a20* data_00477848;
extern unsigned int data_00474c44;
extern int data_00474c68;
extern void* data_00491be8;
extern void* g_sprt_ctrl;
extern char data_00497c38[];
}

struct ScoreTaskClock_00413a20 {
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
    sizeof(ScoreTaskClock_00413a20) == 0x14 ? 1 : -1];

struct FrontResourcesView {
    unsigned char reserved_0000[0x9e60];
    ScoreTaskClock_00413a20 clock;
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

static void LogResourceLoadFailure_00413a20() {
    g_log.Append(data_0046cb68);
}

// Public stdcall task callback: state pointer on the stack and result in EAX.
// Legacy callers retain their fixed-address assembly symbol alias.
#pragma code_seg(".text$02xscore")
extern "C" __declspec(noinline) int __stdcall ScoreTask_Setup_00413a20(
    FrontResourcesView* state) {

    void*& cached_resource = state->cached_resource_9e80;
    cached_resource =
        LoadCachedResource_00447280(0x1c, g_sprt_ctrl,
                                   data_00477848->cached_resource_name);
    if (!cached_resource) {
        LogResourceLoadFailure_00413a20();
        return -1;
    }

    void* preloaded_buffer = data_00491be8;
    if (preloaded_buffer) {
        state->archive_buffer_9ebc = preloaded_buffer;
        data_00491be8 = 0;
    } else {
        const int path_index = data_00474c68;
        ScoreTaskResourceNames_00413a20* resource_names = data_00477848;
        const char* path_suffix = resource_names->archive_paths[path_index];
        char* path = data_00497c38;
        path[0] = '\0';
        strcat(path, path_suffix);
        state->archive_buffer_9ebc = Archive_LoadFile(path, 0, 0);
        if (!state->archive_buffer_9ebc) {
            LogResourceLoadFailure_00413a20();
            return -1;
        }
    }

    state->clock.Reset();
    // Keep the source counter load after the clock reset.
    // Compiler barriers preserve scheduling and emit no instructions.
    _ReadWriteBarrier();
    state->field_9ec0 = 0xffffffff;
    state->field_9ec4 = 0xffffffff;
    state->field_9e78 = data_00474c44;
    return 0;
}

#pragma code_seg()
