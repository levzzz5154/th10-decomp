// Unselected native ABI anchor: verbatim copy of src/game/ascii/add_string.cpp.
// Complete queue writer0x00401530, with the real FPS caller in the native closure.
#include <string.h>
#include "th10/game/game_thread_queue_native.hpp"

#pragma code_seg(".text$01append")
__declspec(noinline) void __stdcall AsciiManager_AddString(GameThread2* thread, const char* name, const Vec32* position) {
    if (thread->record_count < 0x100) {
        QueueRecord* record = &thread->records[thread->record_count++];
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
