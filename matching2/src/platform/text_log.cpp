#include "th10/platform/text_log.hpp"

#ifndef _MSC_VER
#include <cstdarg>
#include <cstring>
extern "C" int __cdecl _vsprintf(char* destination, const char* format,
                                 va_list arguments);
#else
extern "C" int __cdecl _vsprintf(char* destination, const char* format,
                                 const char* arguments);
#endif
#ifdef _MSC_VER
extern "C" unsigned long ___security_cookie;
extern "C" void __stdcall security_check_cookie(unsigned long);
extern "C" void __alloca_probe();
extern "C" void* __imp_EnterCriticalSection;
extern "C" void* __imp_LeaveCriticalSection;
#endif
extern "C" void __stdcall EnterCriticalSection(void* critical_section);
extern "C" void __stdcall LeaveCriticalSection(void* critical_section);
extern unsigned int DAT_004922bc;
extern unsigned char DAT_0049231f;

namespace {

// Bounded append shared by both leaves: the staged line is copied only
// while it fits ahead of the cursor, keeping the trailing NUL inside the
// 0x2000-byte buffer. Oversized or out-of-room appends are dropped.
void TextLog_AppendStaged(TextLog* log, const char* staged) {
    unsigned int length = 0;
    while (staged[length] != 0)
        ++length;
    if (log->cursor + length < log->text + 0x1FFF) {
        for (unsigned int index = 0; index < length; ++index)
            log->cursor[index] = staged[index];
        log->cursor += length;
        *log->cursor = 0;
    }
}

} // namespace

// 0x0044B810 - Format into a 0x2000-byte staging buffer and append the
// result, all inside the text-log critical section; the depth byte is
// raised after entering and lowered after leaving.
#ifdef _MSC_VER
__declspec(naked) void TextLog_Append(TextLog* log, const char* format, ...) {
    __asm {
        mov eax, 2004h
        call __alloca_probe
        mov eax, ___security_cookie
        xor eax, esp
        push esi
        push edi
        push 4922BCh
        mov [esp+200Ch], eax
        mov edi, ecx
        call dword ptr [__imp_EnterCriticalSection]
        mov al, byte ptr [DAT_0049231f]
        mov ecx, [esp+2010h]
        inc al
        mov byte ptr [DAT_0049231f], al
        lea eax, [esp+2014h]
        push eax
        push ecx
        lea edx, [esp+10h]
        push edx
        call _vsprintf
        lea eax, [esp+14h]
        add esp, 0Ch
        lea edx, [eax+1]
loc_44B867:
        mov cl, [eax]
        inc eax
        test cl, cl
        jnz loc_44B867
        mov esi, [edi+2000h]
        sub eax, edx
        lea ecx, [esi+eax]
        lea edx, [edi+1FFFh]
        cmp ecx, edx
        jnb loc_44B8A4
        lea edx, [esp+8]
loc_44B887:
        mov cl, [edx]
        inc edx
        mov [esi], cl
        inc esi
        test cl, cl
        jnz loc_44B887
        mov ecx, [edi+2000h]
        add ecx, eax
        mov [edi+2000h], ecx
        mov edi, ecx
        mov byte ptr [edi], 0
loc_44B8A4:
        push 4922BCh
        call dword ptr [__imp_LeaveCriticalSection]
        mov al, byte ptr [DAT_0049231f]
        mov ecx, [esp+2008h]
        dec al
        pop edi
        pop esi
        mov byte ptr [DAT_0049231f], al
        mov eax, [esp+2008h]
        xor ecx, esp
        call security_check_cookie
        add esp, 2004h
        ret
    }
}
#else
void TextLog_Append(TextLog* log, const char* format, ...) {
    char staging[0x2000];
#ifndef _MSC_VER
    va_list arguments;
    va_start(arguments, format);
#endif

    EnterCriticalSection(&DAT_004922bc);
    ++DAT_0049231f;
#ifndef _MSC_VER
    _vsprintf(staging, format, arguments);
#else
    _vsprintf(staging, format, (const char*)&format + sizeof(format));
#endif
    TextLog_AppendStaged(log, staging);
    LeaveCriticalSection(&DAT_004922bc);
    --DAT_0049231f;

#ifndef _MSC_VER
    va_end(arguments);
#endif
}
#endif

// 0x0044B8E0 - Format into a 0x200-byte staging buffer and append inside
// the text-log critical section, then raise the log's dirty byte after
// leaving.
#ifdef _MSC_VER
__declspec(naked) void TextLog_AppendLine(TextLog* log, const char* format, ...) {
    __asm {
        sub esp, 204h
        mov eax, ___security_cookie
        xor eax, esp
        push 4922BCh
        mov [esp+204h], eax
        call dword ptr [__imp_EnterCriticalSection]
        mov al, byte ptr [DAT_0049231f]
        mov ecx, [esp+208h]
        inc al
        mov byte ptr [DAT_0049231f], al
        lea eax, [esp+20Ch]
        push eax
        push ecx
        lea edx, [esp+8]
        push edx
        call _vsprintf
        lea eax, [esp+0Ch]
        add esp, 0Ch
        lea edx, [eax+1]
        nop
loc_44B930:
        mov cl, [eax]
        inc eax
        test cl, cl
        jnz loc_44B930
        sub eax, edx
        push esi
        mov esi, [edi+2000h]
        lea ecx, [esi+eax]
        lea edx, [edi+1FFFh]
        cmp ecx, edx
        jnb loc_44B96E
        lea edx, [esp+4]
loc_44B951:
        mov cl, [edx]
        inc edx
        mov [esi], cl
        inc esi
        test cl, cl
        jnz loc_44B951
        mov ecx, [edi+2000h]
        add ecx, eax
        mov eax, ecx
        mov [edi+2000h], ecx
        mov byte ptr [eax], 0
loc_44B96E:
        push 4922BCh
        mov byte ptr [edi+2004h], 1
        call dword ptr [__imp_LeaveCriticalSection]
        mov al, byte ptr [DAT_0049231f]
        mov ecx, [esp+204h]
        dec al
        pop esi
        mov byte ptr [DAT_0049231f], al
        mov eax, [esp+208h]
        xor ecx, esp
        call security_check_cookie
        add esp, 204h
        ret
    }
}
#else
void TextLog_AppendLine(TextLog* log, const char* format, ...) {
    char staging[0x200];
#ifndef _MSC_VER
    va_list arguments;
    va_start(arguments, format);
#endif

    EnterCriticalSection(&DAT_004922bc);
    ++DAT_0049231f;
#ifndef _MSC_VER
    _vsprintf(staging, format, arguments);
#else
    _vsprintf(staging, format, (const char*)&format + sizeof(format));
#endif
    TextLog_AppendStaged(log, staging);
    log->dirty = 1;
    LeaveCriticalSection(&DAT_004922bc);
    --DAT_0049231f;

#ifndef _MSC_VER
    va_end(arguments);
#endif
}
#endif
