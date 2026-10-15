// Compiler context and ABI anchors only; none of these bytes enter the image.
#include "../../src/game/replay/replay_file_load_0042a200.cpp"

extern "C" int __cdecl ReplayFileLoadEscape(void* pointer, int value);

// A caller that keeps the manager live across calls.
#pragma inline_depth(0)
#pragma code_seg(".text$00a1context")
extern "C" int __stdcall ReplayFileLoadContext(ReplayManager_0042a6a0** managers, const char** names,
                                               int count) {
    int total = 0;
    for (int index = 0; index < count; ++index) {
        ReplayManager_0042a6a0* manager = managers[index];
        total += ReplayFileLoadEscape(manager, index);
        total += manager->LoadFile(names[index]);
        total += ReplayFileLoadEscape(manager->summary, total);
    }
    return total;
}
#pragma code_seg()
#pragma inline_depth()

// The body of 0x0044B790 (src/platform/file_read_shared_0044b790.cpp), which
// takes its size in EDI.
extern "C" int (__stdcall* data_004660cc)(void* handle);
extern "C" int (__stdcall* data_004660d0)(void* handle, void* buffer, unsigned int size, unsigned int* read,
                                          void* overlapped);
extern "C" void* data_00474c38;
#pragma code_seg(".text$08eshared")
__declspec(noinline) void* __stdcall ReadShared_0044b790(unsigned int size) {
    unsigned int read;
    if (data_00474c38 == (void*)-1) return 0;
    void* buffer = malloc(size);
    if (!buffer) {
        data_004660cc(data_00474c38);
        return 0;
    }
    data_004660d0(data_00474c38, buffer, size, &read, 0);
    return buffer;
}
#pragma code_seg()

// The real archive read closure, supplying its register contracts.
#define ARCHIVE_READ_SECTION ".text$02e_read"
#define ARCHIVE_FIND_SECTION ".text$04find"
#define ARCHIVE_DECRYPT_SECTION ".text$08adecrypt"
#define ARCHIVE_LOAD_SECTION ".text$08cload"
#include "native_archive_read/read.cpp"
#include "native_archive_read/find.cpp"
#include "native_archive_read/decrypt.cpp"
#include "native_archive_read/load.cpp"
