#pragma once
#include <stddef.h>
#include "th10/game/score_file.hpp"
#include "th10/platform/thread_sync.hpp"

// The actual score owner passed by Title and the manager teardown.
struct ScoreArchive_0042B1E0 {
    ScoreFileHeader* file;
    unsigned char* sections;
    ScoreRecordSection records[SCORE_RECORD_COUNT];
    ScoreSettingsSection settings;

    __declspec(noinline) int Save();
};

typedef char ScoreArchive_0042B1E0_records_offset[offsetof(ScoreArchive_0042B1E0, records) == 8 ? 1 : -1];
typedef char ScoreArchive_0042B1E0_settings_offset[offsetof(ScoreArchive_0042B1E0, settings) == 0x1D86C ? 1 : -1];
typedef char ScoreArchive_0042B1E0_size[sizeof(ScoreArchive_0042B1E0) == 0x1DCB4 ? 1 : -1];

extern "C" {
void* __cdecl asm_malloc_00452706(unsigned int size);
void __cdecl asm_free_00452422(void* memory);
unsigned char* __stdcall CompressScore(unsigned char* data, int size, int* packed_size);
int __stdcall OpenSharedFileWrite(const char* name);

// Six genuine logical arguments. Co-compile encrypt.cpp to derive its actual
// AL seed plus five stack arguments; an opaque stdcall declaration cannot
// describe that private native ABI.
__declspec(noinline) unsigned char* __stdcall EncryptDatBuffer(
    unsigned char* data, int size, unsigned char key, unsigned char step,
    int block_size, int limit);

extern int (__stdcall* imp_CloseHandle)(void* handle);
extern int (__stdcall* imp_WriteFile)(void* handle, const void* data,
    unsigned int size, unsigned int* written, void* overlapped);
extern void (__stdcall* imp_LeaveCriticalSection)(CriticalSection* section);
extern void* g_file_write_handle;
extern unsigned char g_file_lock_depth;
extern CriticalSection g_file_lock;
extern char str_score_file[];
}
