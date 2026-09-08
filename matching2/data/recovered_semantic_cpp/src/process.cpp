#include "th10/platform/sound_buffer.hpp"

// 0x0044D5B0: stop the first DirectSound buffer and clear the wrapper's
// playing flag. DirectSound methods use their stdcall COM ABI.
int __fastcall Platform_InvokeInterface(SoundBuffer* sound_buffer) {
    DirectSoundBuffer** const buffers = sound_buffer->buffers;
    if (buffers == 0)
        return (int)0x800401F0u;

    sound_buffer->is_playing = 0;
    DirectSoundBuffer* const buffer = buffers[0];
    return buffer->vtable->stop(buffer);
}
