#include "th10/source_views/process_00435c_0.hpp"
#include "th10/source_views/process_00435c_1.hpp"
int __fastcall Platform_InvokeInterface(SoundBuffer* sound_buffer) {
    DirectSoundBuffer** const buffers = sound_buffer->buffers;
    if (buffers == 0)
        return (int)0x800401F0u;

    sound_buffer->is_playing = 0;
    DirectSoundBuffer* const buffer = buffers[0];
    return buffer->vtable->stop(buffer);
}
