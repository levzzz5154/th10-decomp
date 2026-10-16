// 0x0044CF20: throw a streaming sound's buffers away and create them again
// from its stored description, giving each sixteen evenly spaced position
// notifications on the stream's event. Native LTCG passes the stream in ESI.
#include "th10/game/sound_stream_fill_model.hpp"

void* __cdecl operator new(unsigned int size);
void __cdecl operator delete(void* block);
// IID_IDirectSoundNotify.
extern "C" const unsigned char g_iid_idirectsoundbuffer[16];

#pragma code_seg(".text$00recreate")
extern "C" __declspec(noinline) int __stdcall SoundStream_RecreateBuffers2(
        SoundStreamState* stream) {
    unsigned int i;
    stream->last_play_position = 0;
    for (i = 0; i < stream->buffer_count; ++i) {
        if (stream->buffers[i]) {
            stream->buffers[i]->methods->release(stream->buffers[i]);
            stream->buffers[i] = 0;
        }
    }
    if (stream->buffers) {
        delete[] stream->buffers;
        stream->buffers = 0;
    }

    SoundNotify* notify = 0;
    stream->buffers = new WaveBuffer*[stream->buffer_count];
    for (i = 0; i < stream->buffer_count; ++i) {
        SoundDevice* device = stream->owner->device;
        if (device->methods->create_sound_buffer(device, stream->buffer_description,
                &stream->buffers[i], 0) < 0)
            return 0x80004005;
        WaveBuffer* buffer = stream->buffers[i];
        if (buffer->methods->query_interface(buffer, g_iid_idirectsoundbuffer,
                reinterpret_cast<void**>(&notify)) < 0)
            return 0x80004005;

        SoundNotifyPosition* positions = new SoundNotifyPosition[16];
        if (!positions)
            return 0x8007000E;
        for (unsigned int j = 0; j < 16; ++j) {
            positions[j].offset = stream->notify_bytes * (j + 1) - 1;
            positions[j].event = stream->notify_event;
        }
        if (notify->methods->set_notification_positions(notify, 16, positions) < 0) {
            if (notify) {
                notify->methods->release(notify);
                notify = 0;
            }
            delete positions;
            return 0x80004005;
        }
        if (notify) {
            notify->methods->release(notify);
            notify = 0;
        }
        delete positions;
    }
    return 0;
}
#pragma code_seg()
