// Compiler context only; never selected as recovered game code.
#include "th10/platform/windows_types.hpp"
#include "../../../src/core/sound/sound_preload_worker_0043d080.cpp"
#define ARCHIVE_READ_SECTION ".text$01read"
#define ARCHIVE_FIND_SECTION ".text$02find"
#define ARCHIVE_DECRYPT_SECTION ".text$04decrypt"
#define ARCHIVE_LOAD_SECTION ".text$05load"
#include "native_archive_read/read.cpp"
#include "../../../src/pack/arcmngr/archive_find.cpp"
#include "native_archive_read/decrypt.cpp"
#include "../../../src/core/zunlib/archive_load_file.cpp"
#include "../../../src/core/zunlib/text_log.cpp"

typedef void (__cdecl* ThreadRoutine)();

#pragma code_seg(".text$90context")
int __stdcall SoundPreloadContext_0043d080(ThreadRoutine* routine) {
    // The worker is only started through its address.
    *routine = Sound_PreloadWorker;
    return 0;
}
#pragma code_seg()
