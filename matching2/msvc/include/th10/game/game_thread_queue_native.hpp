#pragma once
#include <stddef.h>

struct Vec3_00401530 {
    float x, y, z;
};
struct QueueRecord_00401530 {
    char name[0x40];
    Vec3_00401530 position;
    int value_4c;
    int value_50;
    int value_54;
    int unknown_58;
    int value_5c;
    int value_60;
    int value_64;
};
struct GameThread_00401530 {
    unsigned char reserved_0000[0x76C];
    QueueRecord_00401530 records[0x100];
    QueueRecord_00401530 late_records[0x40];
    int record_count;
    int late_record_count;
    int current_4c;
    int current_50;
    int current_54;
    int current_5c;
    int unknown_8984;
    int current_64;
};

__declspec(noinline) void __stdcall AsciiManager_AddString(GameThread_00401530* thread, const char* name, const Vec3_00401530* position);
__declspec(noinline) void __cdecl AsciiManager_AddFormattedMarked(GameThread_00401530* thread, const Vec3_00401530* position, const char* format, ...);
typedef char GameQueue_count_is_896c[offsetof(GameThread_00401530, record_count) == 0x896C ? 1 : -1];
typedef char GameQueue_color_is_8974[offsetof(GameThread_00401530, current_4c) == 0x8974 ? 1 : -1];

__declspec(noinline) void __cdecl AsciiManager_AddFormatted(GameThread_00401530* thread, const Vec3_00401530* position, const char* format, ...);
