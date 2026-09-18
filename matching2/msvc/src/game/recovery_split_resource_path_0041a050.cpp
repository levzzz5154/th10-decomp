// 0x0041A050..0x0041A09A: Recovery_SplitResourcePath
//
// Copy the line into the key buffer, split it at the first colon, move the
// value into the value buffer and trim both halves.  Retail passes the line in
// EAX, the value destination in EBX and the key destination in EDI, and every
// exit is a tail jump into the trim helper at 0x0041A0A0, so the model is
// compiled as a native-LTCG cluster together with that helper.
#include <string.h>

// 0x00452730: the CRT first-occurrence byte search (strchr shape), bound to the
// retail address by the layout.  The custom name keeps /Oi from inlining it.
extern "C" char* __cdecl asm_FUN_00452730_00452730(const char* text, int ch);

// 0x0041A0A0: co-compiled whitespace trim (argument and result in EAX).
char* TrimWhitespace_0041a0a0(char* text);

#pragma code_seg(".text$01split")
extern "C" __declspec(noinline) char* __stdcall SplitResourcePath_0041a050(char* line, char* value, char* key) {
    strcpy(key, line);
    char* colon = asm_FUN_00452730_00452730(key, ':');
    if (colon == 0) {
        return TrimWhitespace_0041a0a0(key);
    }
    strcpy(value, colon + 1);
    *colon = 0;
    TrimWhitespace_0041a0a0(key);
    return TrimWhitespace_0041a0a0(value);
}
#pragma code_seg()
