// 0x00413A20..0x00413B40: initialize the task's cached and archive resources.
#include <stddef.h>
#include <string.h>

#include "th10/platform/archive_file.hpp"

struct CachedResource;
extern CachedResource* __fastcall Recovery_LoadCachedResource(
    int index, void* owner, const char* name);

struct TextLog_0044b810 {
    char text[0x2000];
    char* cursor;
    unsigned char dirty;
    char* Append(char* format, ...);
};

// The addressed bytes are linker-owned game globals. Their uses here match
// the pointer/dword operations at 0x00413A20, without naming their owners.
extern "C" {
extern unsigned char data_00477848;
extern unsigned char data_00474c44;
extern unsigned char data_00474c68;
extern unsigned char data_00491be8;
extern unsigned char data_00491c10;
extern unsigned char data_00497c38;
}

struct TaskResourceState_00413a20 {
    unsigned char unknown_0000_9e60[0x9e60];
    unsigned int field_9e60;
    unsigned int field_9e64;
    unsigned int field_9e68;
    void* field_9e6c;
    unsigned int flags_9e70;
    unsigned char unknown_9e74_9e78[4];
    unsigned int field_9e78;
    unsigned char unknown_9e7c_9e80[4];
    void* cached_resource_9e80;
    unsigned char unknown_9e84_9ebc[0x38];
    void* archive_buffer_9ebc;
    unsigned int field_9ec0;
    unsigned int field_9ec4;
};

typedef char TaskResourceState_00413a20_field_offsets_are_correct[
    (offsetof(TaskResourceState_00413a20, field_9e60) == 0x9e60 &&
     offsetof(TaskResourceState_00413a20, cached_resource_9e80) == 0x9e80 &&
     offsetof(TaskResourceState_00413a20, archive_buffer_9ebc) == 0x9ebc &&
     offsetof(TaskResourceState_00413a20, field_9ec4) == 0x9ec4)
        ? 1
        : -1];

static void LogResourceLoadFailure_00413a20() {
    ((TextLog_0044b810*)0x00474f70)->Append((char*)0x0046cb68);
}

// Keep this C-linkage entry for the existing assembly callers. The entry's
// observed ABI is stdcall with one stack pointer and an int result.
extern "C" int __stdcall asm_FUN_00413a20_00413a20(
    TaskResourceState_00413a20* state) {
    void* resourceOwner = *(void**)&data_00491c10;
    void* stageAssetTable = *(void**)&data_00477848;
    const char* resourceName =
        *(const char**)((char*)stageAssetTable + 0x20);

    state->cached_resource_9e80 =
        Recovery_LoadCachedResource(0x1c, resourceOwner, resourceName);
    if (!state->cached_resource_9e80) {
        LogResourceLoadFailure_00413a20();
        return -1;
    }

    void* preloadedBuffer = *(void**)&data_00491be8;
    if (preloadedBuffer) {
        state->archive_buffer_9ebc = preloadedBuffer;
        *(void**)&data_00491be8 = 0;
    } else {
        const int pathIndex = *(int*)&data_00474c68;
        const char* pathSuffix =
            *(const char**)((char*)stageAssetTable + 0x18 + pathIndex * 4);
        char* path = (char*)&data_00497c38;
        path[0] = '\0';
        strcat(path, pathSuffix);
        state->archive_buffer_9ebc = Archive_LoadFile(path, 0, 0);
        if (!state->archive_buffer_9ebc) {
            LogResourceLoadFailure_00413a20();
            return -1;
        }
    }

    if ((state->flags_9e70 & 1) == 0) {
        state->field_9e64 = 0;
        state->field_9e60 = 0xfff0bdc1;
        state->field_9e68 = 0;
        state->field_9e6c = (void*)0x00476f78;
        state->flags_9e70 |= 1;
    }

    state->field_9e64 = 0;
    state->field_9e68 = 0;
    state->field_9e60 = 0xffffffff;
    state->field_9ec0 = 0xffffffff;
    state->field_9ec4 = 0xffffffff;
    state->field_9e78 = *(unsigned int*)&data_00474c44;
    return 0;
}
