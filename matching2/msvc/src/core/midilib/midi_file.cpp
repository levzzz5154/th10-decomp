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
#pragma code_seg(".text$10release")
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
