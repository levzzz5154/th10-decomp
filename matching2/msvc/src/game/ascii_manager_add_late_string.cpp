// 0x004015C0: append a named record to the game thread late queue.
#include <string.h>
struct Vec3_004015c0 {
    float x, y, z;
};
struct QueueRecord_004015c0 {
    char name[0x40];
    Vec3_004015c0 position;
    int value_4c;
    int value_50;
    int value_54;
    int unknown_58;
    int value_5c;
    int value_60;
    int value_64;
};
struct GameThread_004015c0 {
    unsigned char reserved_0000[0x76C];
    QueueRecord_004015c0 records[0x100];
    QueueRecord_004015c0 late_records[0x40];
    int record_count;
    int late_record_count;
    int current_4c;
    int current_50;
    int current_54;
    int current_5c;
    int unknown_8984;
    int current_64;
};

#pragma code_seg(".text$01accessor")
__declspec(noinline) void __stdcall AsciiManager_AddLateString(GameThread_004015c0* thread, const char* name, const Vec3_004015c0* position) {
    if (thread->late_record_count < 0x40) {
        QueueRecord_004015c0* record = &thread->late_records[thread->late_record_count++];
        strcpy(record->name, name);
        record->position = *position;
        record->value_4c = thread->current_4c;
        record->value_50 = thread->current_50;
        record->value_54 = thread->current_54;
        record->value_5c = thread->current_5c;
        record->value_60 = 0;
    }
}
#pragma code_seg()
