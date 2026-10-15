// Complete queue writer at 0x00401530, used by the name-entry formatter.
#include <string.h>
#include "th10/game/name_entry_queue_00401530.hpp"

#pragma code_seg(".text$01append")
__declspec(noinline) void __stdcall AsciiManager_AddString(GameThread_00401530* thread, const char* name, const Vec3_00401530* position) {
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
