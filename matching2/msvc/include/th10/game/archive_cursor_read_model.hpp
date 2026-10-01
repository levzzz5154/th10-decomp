#pragma once
#include <stddef.h>
struct ArchiveReadCursor {
    unsigned char reserved_000[8];
    unsigned int file_remaining;
    unsigned char reserved_00c[0x7C-0x0C];
    unsigned int buffered;
    unsigned char* buffer_begin;
    unsigned char* position;
    unsigned int memory_end;
    void* file;
};
typedef char ArchiveModeOffset[offsetof(ArchiveReadCursor,buffered)==0x7C?1:-1];
typedef char ArchivePositionOffset[offsetof(ArchiveReadCursor,position)==0x84?1:-1];
typedef char ArchiveFileOffset[offsetof(ArchiveReadCursor,file)==0x8C?1:-1];
extern "C" __declspec(dllimport) int __stdcall ReadFile(
    void* file,void* output,unsigned int requested,unsigned int* received,void* overlapped);
extern "C" __declspec(noinline) int __stdcall ArchiveCursorRead(
    ArchiveReadCursor* cursor,unsigned int requested,unsigned int destination,unsigned int* received);
