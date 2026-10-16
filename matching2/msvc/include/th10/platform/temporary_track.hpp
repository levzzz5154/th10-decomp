#pragma once
#include "th10/platform/midi_sequencer.hpp"
struct SoundManager2 {
    unsigned char reserved_000[0x10];
    int active_track;
    void* playing_blocks[32];
    int released_count;
    char* tracks[32];

    __declspec(noinline) void MidiStop();
    __declspec(noinline) int LoadTrack(int index, const char* name);
};
// Identical partial declaration to the canonical LoadTrack unit; both adapters
// describe the same physical 32-bit manager. No second incompatible class exists.
typedef char TemporaryTrack_files_offset[
    offsetof(SoundManager2, tracks) == 0x98 ? 1 : -1];
typedef char TemporaryTrack_slot31_offset[
    offsetof(MidiSequencer, file_buffers) + 31 * sizeof(unsigned char*) == 0x114 ? 1 : -1];
__declspec(noinline) int __stdcall LoadTemporaryTrack(MidiSequencer*, const char*);
