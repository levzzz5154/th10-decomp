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
int SoundDeviceOwner::CreateFileStream(SoundStreamingState** output, unsigned int flags,
        const char* name, WaveGuidImage algorithm, unsigned int segment_count,
        unsigned int segment_bytes, void* notification_event, MusicTrackRecord* record) {
    if (!device)
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
    int hr;
    WaveBufferDescription description;
    memset(&description, 0, sizeof description);
    description.size = sizeof description;
    description.flags = flags | 0x18188;
    description.bytes = buffer_bytes;
    description.algorithm = algorithm;
    description.format = &reader->record->format;
    if ((hr = device->methods->create_buffer(device, &description, &buffer, 0)) < 0)
        return 0x80004005;
    if ((hr = buffer->methods->query_interface(buffer, g_wave_notification_iid, &notification)) < 0)
        return 0x80004005;

    positions = new WaveNotificationPosition[segment_count];
    if (!positions)
        return 0x8007000E;
    for (unsigned int i = 0; i < segment_count; ++i) {
        positions[i].offset = segment_bytes * i + segment_bytes - 1;
        positions[i].event = notification_event;
    }
    if ((hr = notification->methods->set_positions(notification, segment_count, positions)) < 0) {
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
    (*output)->device_owner = &device;
    (*output)->notification_event = notification_event;
    (*output)->servicing = 0;
    return 0;
}
#pragma code_seg()
