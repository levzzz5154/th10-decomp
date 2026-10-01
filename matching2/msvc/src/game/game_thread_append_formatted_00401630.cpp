#include <stdio.h>
#include <stdarg.h>
#include "th10/game/game_thread_queue_native.hpp"
// Ordinary formatter: real panel caller retains position in EBX while thread,
// format and varargs use the stack. The full queue writer receives the buffer.
#pragma code_seg(".text$02bformatted")
__declspec(noinline) void __cdecl AppendFormatted_00401630(GameThread_00401530* thread, const Vec3_00401530* position, const char* format, ...) {
    char text[0x200];
    va_list args;
    va_start(args,format);
    vsprintf(text,format,args);
    va_end(args);
    AppendRecord_00401530(thread,text,position);
}
#pragma code_seg()
