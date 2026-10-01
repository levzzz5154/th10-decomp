#pragma code_seg(".text$01factory")
// 0x0044CBF0, 651 retail bytes: build a stream over an existing PCM buffer.
// Retail uses output in ECX, flags in EDX, eleven stack arguments (RET 44).
// Complete native diagnostic caller with genuine construction and cleanup.
// Its frame and body do not yet match the original 651-byte factory.
#include "sound_wave_types.hpp"
#include "sound_memory_words.hpp"

extern "C" {
    extern const unsigned char g_wave_notification_iid[16];

}

void* __cdecl operator new(unsigned int bytes);
void __cdecl operator delete(void* pointer);
int __fastcall SoundStream_CreateMemory_0044cbf0(SoundStreamingState** output, unsigned int flags,
        WaveDirectSoundDevice** owner, unsigned char* pcm, unsigned int pcm_bytes, MusicTrackRecord* record,
        WaveGuidImage algorithm,
        unsigned int segment_count, unsigned int segment_bytes, void* notification_event) {
    if (!*owner)
        return static_cast<int>(0x800401f0u);
    WaveSecondaryBuffer* buffer = 0;
    WaveNotification* notification = 0;
    MusicReadCursor* reader = static_cast<MusicReadCursor*>(::operator new(sizeof(MusicReadCursor)));
    if (reader) {
        reader->record = 0;
        reader->methods = 0;
        reader->total_pcm_bytes = 0;
        reader->buffered = 0;
    }
    // A failed cursor allocation still reaches these writes in retail.
    reader->record = record;
    reader->memory_end = pcm_bytes;
    reader->buffer_begin = pcm;
    reader->position = pcm;
    reader->buffered = 1;

    WaveBufferDescription description = {};
    unsigned int buffer_bytes = segment_count * segment_bytes;
    description.size = sizeof description;
    description.flags = flags | 0x18188;
    description.bytes = buffer_bytes;
    description.format = &reader->record->format;
    description.algorithm = algorithm;
    WaveDirectSoundDevice* device = *owner;
    int result = device->methods->create_buffer(device, &description, &buffer, 0);
    if (result < 0)
        return static_cast<int>(0x80004005u);
    result = buffer->methods->query_interface(buffer, g_wave_notification_iid, &notification);
    if (result < 0)
        return static_cast<int>(0x80004005u);

    volatile WaveNotificationPosition* positions =
        static_cast<WaveNotificationPosition*>(::operator new(segment_count * 8));
    if (!positions)
        return static_cast<int>(0x8007000eu);
    unsigned int offset = segment_bytes - 1;
    for (unsigned int index = 0; index < segment_count; ++index) {
        positions[index].event = notification_event;
        positions[index].offset = offset;
        offset += segment_bytes;
    }
    result = notification->methods->set_positions(notification, segment_count,
        const_cast<const WaveNotificationPosition*>(positions));
    if (notification) {
        notification->methods->release(notification);
        notification = 0;
    }
    ::operator delete(const_cast<WaveNotificationPosition*>(positions));
    if (result < 0)
        return static_cast<int>(0x80004005u);

    SoundStreamingState* stream = new SoundStreamingState(buffer,buffer_bytes,reader,segment_bytes);
    SoundStreamingState* volatile* published = output;
    *published = stream;
    // The descriptor escaped to CreateSoundBuffer; preserve callback edits and
    // copy in the original forward-word order, including a null publication.
    stream->description = description;
    (*published)->device_owner = owner;
    (*published)->notification_event = notification_event;
    (*published)->servicing = 0;

    return 0;
}

#pragma code_seg()
