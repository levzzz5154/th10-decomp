// Compiler context only: a stand-in for the file stream factory 0x0044C8F0
// without its exception frame, so the pass sees a callee body and derives the
// launcher's argument order from the factory's parameter list. Never selected.
#include "../sound_interfaces_dependencies/sound_wave_types.hpp"

extern "C" {
    extern const unsigned char g_wave_notification_iid[16];
    void __stdcall SoundStream_Construct_0044d6a0(SoundStreamingState*, WaveSecondaryBuffer*,
        unsigned int, MusicReadCursor*, unsigned int);
}
void* __cdecl operator new(unsigned int bytes);
void __cdecl operator delete(void* pointer);

#pragma code_seg(".text$87factory")
int SoundDeviceOwner::CreateFileStream(SoundStreamingState** output, unsigned int flags,
        const char* name, WaveGuidImage algorithm, unsigned int segment_count,
        unsigned int segment_bytes, void* notification_event, MusicTrackRecord* record) {
    if (!device)
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
    if (reader->Open(name, record, 1) != 0) {
        ::operator delete(reader);
        return static_cast<int>(0x80004005u);
    }

    WaveBufferDescription description = {};
    unsigned int buffer_bytes = segment_count * segment_bytes;
    description.size = sizeof description;
    description.flags = flags | 0x18188;
    description.bytes = buffer_bytes;
    description.format = &reader->record->format;
    description.algorithm = algorithm;
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

    SoundStreamingState* stream = static_cast<SoundStreamingState*>(::operator new(sizeof(SoundStreamingState)));
    if (stream)
        SoundStream_Construct_0044d6a0(stream, buffer, buffer_bytes, reader, segment_bytes);
    SoundStreamingState* volatile* published = output;
    *published = stream;
    // The descriptor escaped to CreateSoundBuffer; preserve callback edits and
    // copy in the original forward-word order, including a null publication.
    stream->description = description;
    (*published)->device_owner = &device;
    (*published)->notification_event = notification_event;
    (*published)->servicing = 0;

    return 0;
}

#pragma code_seg()

// 0x0044DBF0, from src/game/archive_cursor_open.cpp: the cursor's open step,
// so the factory stand-in calls it the way retail does.
extern "C" unsigned int (__stdcall* data_004660c8)(void* file, int distance, int* high,
    unsigned int method);
extern "C" unsigned int data_004977a4;
extern "C" void* (__stdcall* data_004660c4)(const char* path, unsigned long access, unsigned long share, void* security, unsigned long disposition, unsigned long flags, void* template_file);
#pragma code_seg(".text$92open")
int MusicReadCursor::Open(const char* path, MusicTrackRecord* entry, unsigned int mode) {
    MusicReadCursor* cursor = this;
    cursor->open_mode = mode;
    cursor->buffered = 0;
    if (mode == 1) {
        if (!path) return 0x80070057;
        cursor->file = data_004660c4(path, 0x80000000, 1, 0, 3, 0x08000080, 0);
        if (cursor->file == (void*)-1) return 0x80004005;
        cursor->record = entry;
        if (cursor->buffered) {
            cursor->position = cursor->buffer_begin;
            if (entry->loop_end > 0) cursor->memory_end = entry->loop_end;
        } else if (cursor->file) {
            data_004660c8(cursor->file, entry->file_offset + data_004977a4, 0, 0);
            cursor->file_remaining = cursor->record->loop_end;
        }
        cursor->total_pcm_bytes = cursor->file_remaining;
    }
    return 0;
}
#pragma code_seg()
