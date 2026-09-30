// 0x0044CF20, 338 retail bytes: replace buffers and install notifications.
// Retail takes ESI and returns with plain RET; this explicit stdcall candidate
// awaits native matching. Partial failures deliberately retain retail ownership.
#include "sound_wave_types.hpp"

extern "C" {
    void* __cdecl SoundBuffer_Allocate(unsigned int bytes);
    void __cdecl SoundBuffer_Free(void* pointer);
    extern const unsigned char g_wave_notification_iid[16];
}

extern "C" int __stdcall SoundStream_RecreateBuffers_0044cf20(SoundStreamingState* stream) {
    stream->playing = 0;
    for (unsigned int index = 0; index < stream->buffer_count; ++index) {
        WaveSecondaryBuffer* buffer = stream->buffers[index];
        if (buffer) {
            buffer->methods->release(buffer);
            // Release can replace the array, so clear the current slot.
            stream->buffers[index] = 0;
        }
    }
    if (stream->buffers) {
        SoundBuffer_Free(stream->buffers);
        stream->buffers = 0;
    }
    WaveNotification* notification = 0;
    stream->buffers = static_cast<WaveSecondaryBuffer**>(SoundBuffer_Allocate(stream->buffer_count * 4));
    for (unsigned int index = 0; index < stream->buffer_count; ++index) {
        WaveDirectSoundDevice* device = *stream->device_owner;
        int result = device->methods->create_buffer(device, &stream->description, &stream->buffers[index], 0);
        if (result < 0)
            return static_cast<int>(0x80004005u);
        WaveSecondaryBuffer* buffer = stream->buffers[index];
        result = buffer->methods->query_interface(buffer, g_wave_notification_iid, &notification);
        if (result < 0)
            return static_cast<int>(0x80004005u);

        volatile WaveNotificationPosition* positions =
            static_cast<WaveNotificationPosition*>(SoundBuffer_Allocate(16 * sizeof(WaveNotificationPosition)));
        if (!positions)
            return static_cast<int>(0x8007000eu);
        const volatile SoundStreamingState* live = stream;
        for (unsigned int notice = 0; notice < 16; ++notice) {
            positions[notice].offset = live->segment_bytes * (notice + 1) - 1;
            positions[notice].event = live->notification_event;
        }
        result = notification->methods->set_positions(notification, 16,
            const_cast<const WaveNotificationPosition*>(positions));
        if (notification) {
            // The output address escaped through QueryInterface; reload after
            // SetNotificationPositions, including a replaced/cleared output.
            notification->methods->release(notification);
            notification = 0;
        }
        SoundBuffer_Free(const_cast<WaveNotificationPosition*>(positions));
        if (result < 0)
            return static_cast<int>(0x80004005u);
    }
    return 0;
}
