// 0x0044B8E0..0x0044B9A8: TextLog::AppendLine
//
// The log object arrives in EDI, the format string and the varargs on the
// stack, and the format string is returned in EAX. That internal convention is
// established by the cluster's compiler-context caller, not by a prototype.

#include <stdarg.h>
#include <string.h>

// 0x004524A6 is the image's own printf engine; it is called as cdecl with the
// va_list address and cleans nothing.
extern "C" int __cdecl asm_vsprintf_004524a6(char* buffer, const char* format, char* args);

// 0x004922BC is the log's Win32 critical section; 0x0049231F counts the
// threads currently inside it.
struct CriticalSection_0044b8e0 { unsigned char storage[24]; };

extern "C" {
__declspec(dllimport) void __stdcall EnterCriticalSection(CriticalSection_0044b8e0* section);
__declspec(dllimport) void __stdcall LeaveCriticalSection(CriticalSection_0044b8e0* section);
extern CriticalSection_0044b8e0 g_text_log_lock;
extern unsigned char g_text_log_lock_depth;
}

// The 8 KiB text ring: the append cursor at +0x2000 and the dirty flag at
// +0x2004. Every append takes the lock, formats into a scratch buffer, and
// copies the text into the ring while it still fits below +0x1FFF.
struct TextLog_0044b8e0 {
    char text[0x2000];
    char* cursor;
    unsigned char dirty;
    char* AppendLine(char* format, ...);
};

#pragma code_seg(".text$01textlogline")
__declspec(noinline) char* TextLog_0044b8e0::AppendLine(char* format, ...) {
    char buffer[512];
    va_list va;
    va_start(va, format);
    EnterCriticalSection(&g_text_log_lock);
    ++g_text_log_lock_depth;
    asm_vsprintf_004524a6(buffer, format, va);
    unsigned int length = strlen(buffer);
    char* dest = cursor;
    if ((unsigned int)(dest + length) < (unsigned int)((char*)this + 0x1FFF)) {
        strcpy(cursor, buffer);
        cursor = (char*)((unsigned int)cursor + length);
        *cursor = 0;
    }
    dirty = 1;
    LeaveCriticalSection(&g_text_log_lock);
    --g_text_log_lock_depth;
    return format;
}
#pragma code_seg()
