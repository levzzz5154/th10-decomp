// Complete 702-byte file-stream factory: 0x0044C8F0 and 0x0044CAD0. Retail
// receives output in ECX, flags in EDX and ten stack arguments (RET 40).
// This explicit stdcall candidate still needs native ABI/frame/byte matching.
#include "sound_wave_types.hpp"
#include "sound_memory_words.hpp"
#include "pending_sound_stream.hpp"

typedef int (__stdcall* MusicCloseFile)(void*);
extern "C" {
    void* __cdecl SoundBuffer_Allocate(unsigned int bytes);
    extern MusicCloseFile g_music_close_file;
    extern const unsigned char g_wave_notification_iid[16];
    SoundStreamingState* __stdcall SoundStream_InitializeSingle_0044d6a0(SoundStreamingState*,
        WaveSecondaryBuffer*, unsigned int bytes, MusicReadCursor*, unsigned int segment_bytes);
}

extern "C" int __stdcall SoundStream_CreateFile_0044c8f0(SoundStreamingState** output, unsigned int flags,
        WaveDirectSoundDevice** owner, const char* filename,
        unsigned int algorithm_0, unsigned int algorithm_1, unsigned int algorithm_2, unsigned int algorithm_3,
        unsigned int segment_count, unsigned int segment_bytes, void* notification_event, MusicTrackRecord* record) {
    if (!*owner)
        return static_cast<int>(0x800401f0u);
    WaveSecondaryBuffer* buffer = 0;
    WaveNotification* notification = 0;
    MusicReadCursor* reader = static_cast<MusicReadCursor*>(SoundBuffer_Allocate(sizeof(MusicReadCursor)));
    if (reader) {
        reader->record = 0;
        reader->methods = 0;
        reader->total_pcm_bytes = 0;
        reader->buffered = 0;
    }
    int result = MusicCursor_Open_0044dbf0(reader, 1, filename, record);
    if (result != 0) {
        if (reader) {
            if (reader->open_mode == 1) {
                g_music_close_file(reader->file);
                reader->file = reinterpret_cast<void*>(0xffffffffu);
            }
            SoundBuffer_Free(reader);
        }
        return static_cast<int>(0x80004005u);
    }

    WaveBufferDescription description = {};
    unsigned int buffer_bytes = segment_count * segment_bytes;
    description.size = sizeof description;
    description.flags = flags | 0x18188;
    description.bytes = buffer_bytes;
    description.format = &reader->record->format;
    unsigned int algorithm[4] = {algorithm_0, algorithm_1, algorithm_2, algorithm_3};
    CopySoundWords(reinterpret_cast<unsigned int>(description.algorithm), reinterpret_cast<unsigned int>(algorithm), 16);
    WaveDirectSoundDevice* device = *owner;
    result = device->methods->create_buffer(device, &description, &buffer, 0);
    if (result < 0)
        return static_cast<int>(0x80004005u);
    result = buffer->methods->query_interface(buffer, g_wave_notification_iid, &notification);
    if (result < 0)
        return static_cast<int>(0x80004005u);

    volatile WaveNotificationPosition* positions =
        static_cast<WaveNotificationPosition*>(SoundBuffer_Allocate(segment_count * 8));
    if (!positions)
        return static_cast<int>(0x8007000eu);
    unsigned int offset = segment_bytes - 1;
    for (unsigned int index = 0; index < segment_count; ++index) {
        positions[index].offset = offset;
        positions[index].event = notification_event;
        offset += segment_bytes;
    }
    result = notification->methods->set_positions(notification, segment_count,
        const_cast<const WaveNotificationPosition*>(positions));
    if (notification) {
        notification->methods->release(notification);
        notification = 0;
    }
    SoundBuffer_Free(const_cast<WaveNotificationPosition*>(positions));
    if (result < 0)
        return static_cast<int>(0x80004005u);

    SoundStreamingState* storage = static_cast<SoundStreamingState*>(SoundBuffer_Allocate(sizeof(SoundStreamingState)));
    PendingSoundStream pending(storage);
    SoundStreamingState* stream = storage ?
        SoundStream_InitializeSingle_0044d6a0(storage, buffer, buffer_bytes, reader, segment_bytes) : 0;
    SoundStreamingState* volatile* published = output;
    *published = stream;
    CopySoundWords(reinterpret_cast<unsigned int>(stream) + 0x34, reinterpret_cast<unsigned int>(&description), 36);
    (*published)->device_owner = owner;
    (*published)->notification_event = notification_event;
    (*published)->servicing = 0;
    pending.Publish();
    return 0;
}
