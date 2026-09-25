#include "th10/platform/sound_buffer.hpp"

// Retail 0x0044D640..0x0044D697 receives the sound-buffer owner in EDI.
extern "C" unsigned int __cdecl SoundBuffer_AnyPlaying_0044d640(
    const SoundBuffer* owner) {
    if (owner->buffers == 0)
        return 0;

    const unsigned int playing_bit = 1;
    unsigned int any_playing = 0;
    for (unsigned int index = 0; index < owner->buffer_count; ++index) {
        DirectSoundBuffer* buffer = owner->buffers[index];
        if (buffer != 0) {
            unsigned int status = 0;
            buffer->vtable->get_status(buffer, &status);
            any_playing |= status & playing_bit;
        }
    }
    return any_playing;
}
