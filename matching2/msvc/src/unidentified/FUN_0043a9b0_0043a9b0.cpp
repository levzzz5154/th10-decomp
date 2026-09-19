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
struct CriticalSection_0044b810 { unsigned char storage[24]; };

extern "C" {
__declspec(dllimport) void __stdcall EnterCriticalSection(
    CriticalSection_0044b810* section);
__declspec(dllimport) void __stdcall LeaveCriticalSection(
    CriticalSection_0044b810* section);
extern CriticalSection_0044b810 data_004922bc;
extern unsigned char data_0049231f;
extern int __cdecl asm_vsprintf_004524a6(char* buffer, const char* format, char* arguments);
}

struct TextLog_0044b810 {
    char text[0x2000];
    char* cursor;
    unsigned char dirty;
    char* Append(char* format, ...);
};

extern "C" void __cdecl entry_free_00452422(void*);

struct SoundManager_0043a9b0 {
    unsigned char reserved_000[0x10];
    int active_track;
    void* playing_blocks[32];
    int released_count;
    char* tracks[32];

    __declspec(noinline) void MidiStop();
    __declspec(noinline) int LoadTrack(int index, const char* name);
};

#pragma code_seg(".text$03zn9b0track")
int SoundManager_0043a9b0::LoadTrack(int index, const char* name) {
    if (active_track == index) MidiStop();
    if (tracks[index]) {
        entry_free_00452422(tracks[index]);
        tracks[index] = 0;
    }
    tracks[index] = 0;
    char* data = Archive_LoadFile(name, 0, 0);
    tracks[index] = data;
    if (!data) {
        ((TextLog_0044b810*)0x474F70)->Append((char*)0x46F908, name);
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
#pragma code_seg(".text$03zpanchor")
__declspec(noinline) void SoundManager_0043a9b0::MidiStop() {
    unsigned char* bytes = (unsigned char*)this;
    int count = *(int*)(bytes + 0x10C);
    unsigned char* cursor = *(unsigned char**)(bytes + 0x120);
    for (int i = 0; i < count; ++i) {
        entry_free_00452422(*(void**)(cursor + 4));
        *(void**)(cursor + 4) = 0;
        cursor += 0x10;
    }
    entry_free_00452422(cursor);
    *(void**)(bytes + 0x120) = 0;
    entry_free_00452422(*(void**)(bytes + 0x108));
    *(void**)(bytes + 0x108) = 0;
}
#pragma code_seg()

// 0x0044B810 (text-log report).  Variadic, so no declaration decides where the
// log object travels; a minimal body keeps the cdecl form.  This body is the
// entry's own shape, and the deciding property is that the log object stays
// live across the anchor's own calls.
#pragma code_seg(".text$09append")
__declspec(noinline) char* TextLog_0044b810::Append(char* format, ...) {
    char staging[0x2000];
    va_list arguments;
    va_start(arguments, format);

    EnterCriticalSection(&data_004922bc);
    ++data_0049231f;
    asm_vsprintf_004524a6(staging, format, arguments);

    unsigned int length = strlen(staging);
    char* destination = cursor;
    if ((unsigned int)(destination + length) <
        (unsigned int)((char*)this + 0x1FFF)) {
        strcpy(cursor, staging);
        cursor = (char*)((unsigned int)cursor + length);
        *cursor = 0;
    }

    LeaveCriticalSection(&data_004922bc);
    --data_0049231f;
    return format;
}
#pragma code_seg()
