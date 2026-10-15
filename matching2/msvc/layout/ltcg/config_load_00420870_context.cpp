// Compiler context and ABI anchors only; none of these bytes enter the image.
#include "../../src/game/mother/config_load_00420870.cpp"
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
#include "native_archive_read/find.cpp"
#include "native_archive_read/decrypt.cpp"
#include "native_archive_read/load.cpp"

// The body of 0x0044B540 (src/core/zunlib/file_write_whole_file_0044b540.cpp),
// which takes its size in EDI.
extern "C" void* (__stdcall *data_004660c4)(const char*, unsigned int, unsigned int, void*, unsigned int,
                                            unsigned int, void*);
extern "C" int (__stdcall *data_004660d4)(void*, const void*, unsigned long, unsigned long*, void*);
extern "C" unsigned long (__stdcall *data_0046610c)(void);
extern "C" unsigned long (__stdcall *data_00466124)(unsigned long, void*, unsigned long, unsigned long, char**,
                                                    unsigned long, void*);
extern "C" void* (__stdcall *data_00466128)(void*);
#pragma code_seg(".text$00h_write")
__declspec(noinline) int __stdcall File_WriteWholeFile(const char* path, const void* buffer, unsigned long size) {
    data_004660b0(data_004922a4);
    ++data_0049231e;
    void* handle = data_004660c4(path, 0x40000000, 1, 0, 2, 0x80, 0);
    if (handle == (void*)-1) {
        char* message;
        data_00466124(0x1300, 0, data_0046610c(), 0x400, &message, 0, 0);
        data_00466128(message);
        data_004660b4(data_004922a4);
        --data_0049231e;
        return -1;
    }
    unsigned long written;
    data_004660d4(handle, buffer, size, &written, 0);
    if (size != written) {
        data_004660cc(handle);
        data_004660b4(data_004922a4);
        --data_0049231e;
        return -2;
    }
    data_004660cc(handle);
    data_004660b4(data_004922a4);
    --data_0049231e;
    return 0;
}

// The bodies of the two log appenders (src/core/zunlib/text_log.cpp and
// text_log_append_line_0044b8e0.cpp).
extern "C" int __cdecl asm_vsprintf_004524a6(char* buffer, const char* format, char* arguments);
struct ConfigLoadCriticalSection { unsigned char storage[24]; };
extern "C" {
__declspec(dllimport) void __stdcall EnterCriticalSection(ConfigLoadCriticalSection* section);
__declspec(dllimport) void __stdcall LeaveCriticalSection(ConfigLoadCriticalSection* section);
extern ConfigLoadCriticalSection data_004922bc;
extern unsigned char data_0049231f;
}
#pragma code_seg(".text$00i_append")
__declspec(noinline) char* TextLog_00420870::Append(char* format, ...) {
    char staging[0x2000];
    va_list arguments;
    va_start(arguments, format);
    EnterCriticalSection(&data_004922bc);
    ++data_0049231f;
    asm_vsprintf_004524a6(staging, format, arguments);
    unsigned int length = strlen(staging);
    char* destination = cursor;
    if ((unsigned int)(destination + length) < (unsigned int)((char*)this + 0x1FFF)) {
        strcpy(cursor, staging);
        cursor = (char*)((unsigned int)cursor + length);
        *cursor = 0;
    }
    LeaveCriticalSection(&data_004922bc);
    --data_0049231f;
    return format;
}
#pragma code_seg(".text$00j_line")
__declspec(noinline) char* TextLog_00420870::AppendLine(char* format, ...) {
    char buffer[512];
    va_list va;
    va_start(va, format);
    EnterCriticalSection(&data_004922bc);
    ++data_0049231f;
    asm_vsprintf_004524a6(buffer, format, va);
    unsigned int length = strlen(buffer);
    char* dest = cursor;
    if ((unsigned int)(dest + length) < (unsigned int)((char*)this + 0x1FFF)) {
        strcpy(cursor, buffer);
        cursor = (char*)((unsigned int)cursor + length);
        *cursor = 0;
    }
    dirty = 1;
    LeaveCriticalSection(&data_004922bc);
    --data_0049231f;
    return format;
}
#pragma code_seg()
