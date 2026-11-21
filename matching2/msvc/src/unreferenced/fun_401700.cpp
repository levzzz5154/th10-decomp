// 0x00401700: format a message into a 512-byte stack buffer, hand it to the
// game-thread record queue, and return the formatted length.
//
// The queue pointer arrives in ESI and the record's position vector in EBX; both
// are callee-saved registers the body only passes through to the append helper,
// so they stay undeclared here and survive untouched.

extern "C" int __cdecl asm_vsprintf_004524a6(char* buffer, const char* format, char* args);

// 0x004015C0 reads the text from ECX and the record context from EBX/ESI; it
// never reads EAX, so a __fastcall prototype reproduces the retail call site
// (the formatted text moves straight into ECX).
extern "C" void __fastcall asm_FUN_004015c0_004015c0(char* text);

#include <string.h>

#pragma code_seg(".text$01format_text")
unsigned int GameThread_FormatRecordText(char* format, ...) {
    char buffer[512];
    asm_vsprintf_004524a6(buffer, format, (char*)&format + sizeof(format));
    asm_FUN_004015c0_004015c0(buffer);
    return (unsigned int)strlen(buffer);
}
#pragma code_seg()
