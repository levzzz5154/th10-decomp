// Compiler-only copies of canonical dependency bodies; no production ownership or credit.
#include "th10/platform/temporary_track.hpp"
// 0x0043A9B0 — the MIDI sound manager's track-reload leaf.
//
// Retail reaches this member with the manager in EAX, the track index in ESI
// (an unsaved register argument) and the file name as the only stack argument,
// and returns with `ret 4` — a private convention no declaration names, so the
// body is modelled inside the registered `load_archive_file` native-LTCG
// cluster whose link already co-compiles 0x0044B360 with its own body, and the
// whole-program pass derives the entry agreement from the bodies.
//
// The receiver's callee-saved home is EDI in retail (with `name` in EBP and
// `index` in ESI, i.e. `push ebp; mov ebp,[esp+8]; push edi; mov edi,eax`).
// That home is not a free choice of this body: the caller follows whichever
// register the *callee* that it calls bare takes its receiver in, and the two
// callees here have no declaration that names a register, so their bodies are
// compiled as ABI anchors below.  A body whose records object stays live
// across a loop that calls out — the shape recorded for 0x0041C330 and
// 0x00447810 — earns EDI; the first anchor shape tried (a cursor, a counter and
// a released count live across the same free) earned EBX instead, and the whole
// 18-byte residual was that one register.
#include <stdarg.h>
#include <string.h>

#include "th10/platform/archive_file.hpp"

// ABI anchor declarations: the 0x0044B810 text-log entry (object in ECX, both
// arguments on the caller-cleaned stack; a fixed declaration gets the ECX part
// but a callee-cleaned RET 8, and the variadic declaration gets neither).
struct CriticalSection2 { unsigned char storage[24]; };

extern "C" {
__declspec(dllimport) void __stdcall EnterCriticalSection(
    CriticalSection2* section);
__declspec(dllimport) void __stdcall LeaveCriticalSection(
    CriticalSection2* section);
extern CriticalSection2 g_text_log_lock;
extern unsigned char g_text_log_lock_depth;
extern int __cdecl asm_vsprintf_004524a6(char* buffer, const char* format, char* arguments);
}

struct TextLog4 {
    char text[0x2000];
    char* cursor;
    unsigned char dirty;
    char* Append(char* format, ...);
};

extern "C" void __cdecl crt_free(void*);



#pragma code_seg(".text$10loadtrack")
int SoundManager2::LoadTrack(int index, const char* name) {
    if (active_track == index) MidiStop();
    if (tracks[index]) {
        crt_free(tracks[index]);
        tracks[index] = 0;
    }
    tracks[index] = 0;
    char* data = Archive_LoadFile(name, 0, 0);
    tracks[index] = data;
    if (!data) {
        ((TextLog4*)0x474F70)->Append((char*)0x46F908, name);
        return -1;
    }
    return 0;
}
#pragma code_seg()

// ABI anchors.  Neither body is recovered game code: the layout places each at
// its retail address, the caller's `call` bakes retail's displacement, and
// export_bodies never selects them.
//
// 0x0043AE20 (MIDI playback stop).  Retail's call site is a bare `call`, so the
// anchor's receiver register *is* the caller's home for `this`.  The offsets
// below are scaffolding only — what earns EDI is that the object is reached
// through a local base pointer that is still live after the loop, while the
// cursor is a loaded pointer incremented inside it.
#pragma code_seg(".text$50stop")
__declspec(noinline) void SoundManager2::MidiStop() {
    unsigned char* bytes = (unsigned char*)this;
    int count = *(int*)(bytes + 0x10C);
    unsigned char* cursor = *(unsigned char**)(bytes + 0x120);
    for (int i = 0; i < count; ++i) {
        crt_free(*(void**)(cursor + 4));
        *(void**)(cursor + 4) = 0;
        cursor += 0x10;
    }
    crt_free(cursor);
    *(void**)(bytes + 0x120) = 0;
    crt_free(*(void**)(bytes + 0x108));
    *(void**)(bytes + 0x108) = 0;
}
#pragma code_seg()

// 0x0044B810 (text-log report).  Variadic, so no declaration decides where the
// log object travels; a minimal body keeps the cdecl form.  This body is the
// entry's own shape, and the deciding property is that the log object stays
// live across the anchor's own calls.
#pragma code_seg(".text$70append")
__declspec(noinline) char* TextLog4::Append(char* format, ...) {
    char staging[0x2000];
    va_list arguments;
    va_start(arguments, format);

    EnterCriticalSection(&g_text_log_lock);
    ++g_text_log_lock_depth;
    asm_vsprintf_004524a6(staging, format, arguments);

    unsigned int length = strlen(staging);
    char* destination = cursor;
    if ((unsigned int)(destination + length) <
        (unsigned int)((char*)this + 0x1FFF)) {
        strcpy(cursor, staging);
        cursor = (char*)((unsigned int)cursor + length);
        *cursor = 0;
    }

    LeaveCriticalSection(&g_text_log_lock);
    --g_text_log_lock_depth;
    return format;
}
#pragma code_seg()

#include "th10/platform/midi_sequencer.hpp"
#include <string.h>

extern "C" void* __cdecl entry_malloc(unsigned int);
extern "C" void __cdecl crt_free(void*);

struct MidiChunkHeader {
    char tag[4];
    unsigned int length;
};

struct MidiFileHeader {
    unsigned short format;
    unsigned short track_count;
    unsigned short division;
};

// 0x0043AA60: release the copied tracks while retaining the loaded files.
#pragma code_seg(".text$20release")
void MidiSequencer::ReleaseTracks() {
    for (int index = 0; index < track_count; ++index) {
        if (tracks[index].data) {
            crt_free(tracks[index].data);
            tracks[index].data = 0;
        }
    }
    if (tracks) {
        crt_free(tracks);
        tracks = 0;
    }
    tracks = 0;
    track_count = 0;
}

#pragma code_seg(".text$30parse")
static inline unsigned int Swap32(unsigned int value) {
    union {
        unsigned int value;
        unsigned char bytes[4];
    } result;
    result.bytes[0] = reinterpret_cast<const unsigned char*>(&value)[3];
    result.bytes[1] = reinterpret_cast<const unsigned char*>(&value)[2];
    result.bytes[2] = reinterpret_cast<const unsigned char*>(&value)[1];
    result.bytes[3] = reinterpret_cast<const unsigned char*>(&value)[0];
    return result.value;
}

static inline unsigned short Swap16(unsigned short value) {
    union {
        unsigned short value;
        unsigned char bytes[2];
    } result;
    result.bytes[0] = reinterpret_cast<const unsigned char*>(&value)[1];
    result.bytes[1] = reinterpret_cast<const unsigned char*>(&value)[0];
    return result.value;
}

// 0x0043AAD0: parse a loaded MIDI file and copy each track into owned storage.
int MidiSequencer::ParseLoadedFile(int slot) {
    ReleaseTracks();
    unsigned char* cursor = file_buffers[slot];
    if (!cursor)
        return -1;

    MidiChunkHeader chunk;
    memcpy(&chunk, cursor, sizeof(chunk));
    cursor += sizeof(chunk);
    unsigned int chunk_size = Swap32(chunk.length);
    MidiFileHeader* header = reinterpret_cast<MidiFileHeader*>(cursor);
    cursor += chunk_size;
    format = Swap16(header->format);
    ticks_per_quarter_note = Swap16(header->division);
    track_count = Swap16(header->track_count);

    tracks = static_cast<MidiTrack*>(entry_malloc(track_count * sizeof(MidiTrack)));
    memset(tracks, 0, track_count * sizeof(MidiTrack));
    for (int index = 0; index < track_count; ++index) {
        MidiChunkHeader* track_header = reinterpret_cast<MidiChunkHeader*>(cursor);
        cursor += sizeof(*track_header);
        chunk_size = Swap32(track_header->length);
        tracks[index].byte_count = chunk_size;
        tracks[index].data = static_cast<unsigned char*>(entry_malloc(chunk_size));
        tracks[index].active = 1;
        memcpy(tracks[index].data, cursor, chunk_size);
        cursor += chunk_size;
    }
    current_file_slot = slot;
    tempo_microseconds = 1000000;
    return 0;
}
#pragma code_seg()

// 0x0044B360: load a named file either from the packed archive index or from disk.
#include "th10/platform/archive_file.hpp"

struct ArchiveEntry {
    const char* name;       // +0x00
    unsigned int unknown;   // +0x04
    unsigned int size;      // +0x08
    unsigned int unknown2;  // +0x0C
};

struct ArchiveReader {
    char* Read(const void* table, char* block);
};

extern "C" ArchiveEntry* g_archive;
extern "C" int data_00497994;
extern "C" unsigned char g_file_lock_depth;
extern "C" unsigned char g_file_lock[];

extern "C" void (__stdcall *imp_EnterCriticalSection)(void*);
extern "C" void (__stdcall *imp_LeaveCriticalSection)(void*);
extern "C" void* (__stdcall *imp_CreateFileA)(const char*, unsigned int, unsigned int, void*,
                                            unsigned int, unsigned int, void*);
extern "C" int (__stdcall *imp_CloseHandle)(void*);
extern "C" int (__stdcall *imp_ReadFile)(void*, void*, unsigned int, unsigned int*, void*);
extern "C" unsigned int (__stdcall *imp_GetFileSize)(void*, unsigned int*);

extern "C" char* __cdecl asm_strrchr_00452930(const char*, int);
extern "C" int __cdecl asm_stricmp_0046054e(const char*, const char*);
extern "C" void* __cdecl asm_malloc_00452706(unsigned int);

#pragma code_seg(".text$60archive")
extern "C" __declspec(noinline) char* __stdcall Archive_LoadFile(const char* name, int* outSize,
                                                                 int fromDisk) {
    char* buffer;
    unsigned int size;
    imp_EnterCriticalSection(g_file_lock);
    ++g_file_lock_depth;
    if (!fromDisk) {
        const char* slash = asm_strrchr_00452930(name, '\\');
        const char* base = (slash == 0) ? name : slash + 1;
        const char* forward = asm_strrchr_00452930(base, '/');
        if (forward == 0) forward = name; else ++forward;
        base = forward;

        if (g_archive != 0 && data_00497994 > 0) {
            ArchiveEntry* entry = g_archive;
            int remaining = data_00497994;
            do {
                if (asm_stricmp_0046054e(base, entry->name) == 0) {
                    size = entry->size;
                    goto looked_up;
                }
                --remaining;
                entry = (ArchiveEntry*)((char*)entry + 16);
            } while (remaining > 0);
        }
        size = 0;
looked_up:
        if (outSize)
            *outSize = size;
        if (!size)
            goto failed;
        buffer = (char*)asm_malloc_00452706(size);
        if (!buffer)
            goto failed;
        ((ArchiveReader*)base)->Read(&g_archive, buffer);
        goto done;
    }

    {
        void* file = imp_CreateFileA(name, 0x80000000, 1, 0, 3, 0x8000080, 0);
        if (file == (void*)-1)
            goto failed;
        size = imp_GetFileSize(file, 0);
        buffer = (char*)asm_malloc_00452706(size);
        if (!buffer) {
            imp_CloseHandle(file);
            goto failed;
        }
        imp_ReadFile(file, buffer, size, &size, 0);
        if (outSize)
            *outSize = size;
        imp_CloseHandle(file);
    }
done:
    imp_LeaveCriticalSection(g_file_lock);
    --g_file_lock_depth;
    return buffer;
failed:
    imp_LeaveCriticalSection(g_file_lock);
    --g_file_lock_depth;
    return 0;
}
#pragma code_seg()
