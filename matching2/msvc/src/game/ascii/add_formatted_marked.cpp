#include <stdio.h>
#include <stdarg.h>
#include "th10/game/game_thread_queue_native.hpp"

// Complete marked-text writer100: thread ESI, position EBX, format/varargs stack.
#pragma code_seg(".text$03marked")
__declspec(noinline) void __cdecl AsciiManager_AddFormattedMarked(GameThread_00401530 *thread,
                const Vec3_00401530 *position, const char *format, ...) {
    char text[0x200];
    va_list args;
    va_start(args,format);
    vsprintf(text,format,args);
    va_end(args);
    AsciiManager_AddString(thread,text,position);
    thread->records[thread->record_count-1].value_60=1;
}
#pragma code_seg()
