// Compiler context and ABI anchors only; none of these bytes enter the image.
#include "../../../src/game/mother/config_load_00420870.cpp"
#include <stdarg.h>

extern "C" int __cdecl ConfigLoadEscape(void* pointer, int value);

// A caller that keeps the path live beside the application object.
#pragma inline_depth(0)
#pragma code_seg(".text$0040a000_context")
extern "C" int __stdcall ConfigLoadContext(GameApp_00420870** apps, const char** paths, int count) {
    int total = 0;
    for (int index = 0; index < count; ++index) {
        const char* path = paths[index];
        total += ConfigLoadEscape(apps[index], index);
        total += apps[index]->LoadConfig(path);
        total += ConfigLoadEscape((void*)path, total);
    }
    return total;
}
#pragma code_seg()
#pragma inline_depth()

// The real defaults routine (0x00418C40).
#include "config_load_dependencies/config_defaults.cpp"

// The real archive read closure, supplying its register contracts.
#define ARCHIVE_READ_SECTION ".text$00d_read"
#define ARCHIVE_FIND_SECTION ".text$00e_find"
#define ARCHIVE_DECRYPT_SECTION ".text$00f_decrypt"
#define ARCHIVE_LOAD_SECTION ".text$00g_load"
#include "native_archive_read/read.cpp"
#include "../../../src/pack/arcmngr/archive_find.cpp"
#include "native_archive_read/decrypt.cpp"
#include "../../../src/core/zunlib/archive_load_file.cpp"

// The body of 0x0044B540 (src/core/zunlib/file_write_whole_file_0044b540.cpp),
// which takes its size in EDI.
extern "C" void* (__stdcall *imp_CreateFileA)(const char*, unsigned int, unsigned int, void*, unsigned int,
                                            unsigned int, void*);
extern "C" int (__stdcall *imp_WriteFile)(void*, const void*, unsigned long, unsigned long*, void*);
extern "C" unsigned long (__stdcall *imp_GetLastError)(void);
extern "C" unsigned long (__stdcall *imp_FormatMessageA)(unsigned long, void*, unsigned long, unsigned long, char**,
                                                    unsigned long, void*);
extern "C" void* (__stdcall *imp_LocalFree)(void*);
#pragma code_seg(".text$00h_write")
__declspec(noinline) int __stdcall File_WriteWholeFile(const char* path, const void* buffer, unsigned long size) {
    imp_EnterCriticalSection(g_file_lock);
    ++g_file_lock_depth;
    void* handle = imp_CreateFileA(path, 0x40000000, 1, 0, 2, 0x80, 0);
    if (handle == (void*)-1) {
        char* message;
        imp_FormatMessageA(0x1300, 0, imp_GetLastError(), 0x400, &message, 0, 0);
        imp_LocalFree(message);
        imp_LeaveCriticalSection(g_file_lock);
        --g_file_lock_depth;
        return -1;
    }
    unsigned long written;
    imp_WriteFile(handle, buffer, size, &written, 0);
    if (size != written) {
        imp_CloseHandle(handle);
        imp_LeaveCriticalSection(g_file_lock);
        --g_file_lock_depth;
        return -2;
    }
    imp_CloseHandle(handle);
    imp_LeaveCriticalSection(g_file_lock);
    --g_file_lock_depth;
    return 0;
}

// The bodies of the two log appenders (src/core/zunlib/text_log.cpp and
// text_log_append_line_0044b8e0.cpp).
extern "C" int __cdecl asm_vsprintf_004524a6(char* buffer, const char* format, char* arguments);
struct ConfigLoadCriticalSection { unsigned char storage[24]; };
extern "C" {
__declspec(dllimport) void __stdcall EnterCriticalSection(ConfigLoadCriticalSection* section);
__declspec(dllimport) void __stdcall LeaveCriticalSection(ConfigLoadCriticalSection* section);
extern ConfigLoadCriticalSection g_text_log_lock;
extern unsigned char g_text_log_lock_depth;
}
#pragma code_seg(".text$00i_append")
__declspec(noinline) char* TextLog_00420870::Append(char* format, ...) {
    char staging[0x2000];
    va_list arguments;
    va_start(arguments, format);
    EnterCriticalSection(&g_text_log_lock);
    ++g_text_log_lock_depth;
    asm_vsprintf_004524a6(staging, format, arguments);
    unsigned int length = strlen(staging);
    char* destination = cursor;
    if ((unsigned int)(destination + length) < (unsigned int)((char*)this + 0x1FFF)) {
        strcpy(cursor, staging);
        cursor = (char*)((unsigned int)cursor + length);
        *cursor = 0;
    }
    LeaveCriticalSection(&g_text_log_lock);
    --g_text_log_lock_depth;
    return format;
}
#pragma code_seg(".text$00j_line")
__declspec(noinline) char* TextLog_00420870::AppendLine(char* format, ...) {
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
