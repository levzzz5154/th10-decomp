// 0x00401530: append a named record to the game thread queue.
#include <string.h>
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

#pragma code_seg(".text$01accessor")
__declspec(noinline) void __stdcall AppendRecord_00401530(GameThread_00401530* thread, const char* name, const Vec3_00401530* position) {
    if (thread->record_count < 0x100) {
        QueueRecord_00401530* record = &thread->records[thread->record_count++];
        strcpy(record->name, name);
        record->position = *position;
        record->value_4c = thread->current_4c;
        record->value_50 = thread->current_50;
        record->value_54 = thread->current_54;
        record->value_5c = thread->current_5c;
        record->value_60 = 0;
        record->value_64 = thread->current_64;
    }
}
#pragma code_seg()
