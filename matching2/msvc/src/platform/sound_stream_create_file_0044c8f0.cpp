// Native compiler model: only its allocation cleanup and EH handler are
// selected. This complete factory emits 692 bytes versus retail 702.
// The export preserves the observed public fastcall ABI in the caller rig;
// it is not selected into the final executable.
// 0x0044C8F0: create a streaming sound that plays one track out of the music
// file. Opens a read cursor on the track, creates a secondary buffer of
// segment_count segments, asks for a position notification at the end of each
// segment and wraps the buffer in a streaming sound. The compiler-generated
// cleanup at 0x00465330 frees the sound's block if its constructor throws.
#include "../../layout/ltcg/sound_interfaces_dependencies/sound_wave_types.hpp"

#include <string.h>
#pragma intrinsic(memset)
void* __cdecl operator new(unsigned int bytes);
void __cdecl operator delete(void* pointer);
extern "C" {
    extern const unsigned char g_wave_notification_iid[16];
    extern int (__stdcall* data_004660cc)(void*);
}

// The read cursor as the factory creates and discards it.
struct MusicFileCursor : MusicReadCursor {
    MusicFileCursor() {
        record = 0;
        methods = 0;
        total_pcm_bytes = 0;
        buffered = 0;
    }
    ~MusicFileCursor() {
        if (open_mode == 1) {
            data_004660cc(file);
            file = reinterpret_cast<void*>(-1);
        }
    }
};

template <class T> inline void SafeDelete(T*& object) {
    if (object) {
        delete object;
        object = 0;
    }
}

#pragma code_seg(".text$02factory")
__declspec(dllexport) int __fastcall SoundStream_CreateFile_0044c8f0(SoundStreamingState** output, unsigned int flags,
        WaveDirectSoundDevice** owner, const char* name, WaveGuidImage algorithm,
        unsigned int segment_count, unsigned int segment_bytes, void* notification_event,
        MusicTrackRecord* record) {
    if (!*owner)
        return 0x800401F0;
    WaveSecondaryBuffer* buffer = 0;
    unsigned int buffer_bytes = 0;
    MusicFileCursor* reader = 0;
    WaveNotificationPosition* positions = 0;
    WaveNotification* notification = 0;

    reader = new MusicFileCursor;
    if (reader->Open(name, record, 1) != 0) {
        SafeDelete(reader);
        return 0x80004005;
    }

    buffer_bytes = segment_bytes * segment_count;
    WaveBufferDescription description;
    memset(&description, 0, sizeof description);
    description.size = sizeof description;
    description.flags = flags | 0x18188;
    description.bytes = buffer_bytes;
    description.algorithm = algorithm;
    description.format = &reader->record->format;
    if ((*owner)->methods->create_buffer(*owner, &description, &buffer, 0) < 0)
        return 0x80004005;
    if (buffer->methods->query_interface(buffer, g_wave_notification_iid, &notification) < 0)
        return 0x80004005;

    positions = new WaveNotificationPosition[segment_count];
    if (!positions)
        return 0x8007000E;
    for (unsigned int i = 0; i < segment_count; ++i) {
        positions[i].offset = segment_bytes * i + segment_bytes - 1;
        positions[i].event = notification_event;
    }
    if (notification->methods->set_positions(notification, segment_count, positions) < 0) {
        if (notification) {
            notification->methods->release(notification);
            notification = 0;
        }
        delete positions;
        return 0x80004005;
    }
    if (notification) {
        notification->methods->release(notification);
        notification = 0;
    }
    delete positions;

    *output = new SoundStreamingState(buffer, buffer_bytes, reader, segment_bytes);
    (*output)->description = description;
    (*output)->device_owner = owner;
    (*output)->notification_event = notification_event;
    (*output)->servicing = 0;
    return 0;
}
#pragma code_seg()
