// Behavioral recovery of the complete 145-byte routine at 0x0044D440.
// Retail takes the stream in EAX and priority/flags on the stack (RET 8).
#include "sound_wave_types.hpp"

extern "C" int __stdcall SoundStream_FillBuffer_0044d110(
    SoundStream*, WaveSecondaryBuffer*, unsigned int loop);

extern "C" int __stdcall SoundStream_Start_0044d440(
        SoundStream* stream, unsigned int priority, unsigned int flags) {
    if (!stream->buffers)
        return static_cast<int>(0x800401f0u);
    WaveSecondaryBuffer* buffer = stream->FindAvailable();
    if (!buffer)
        return static_cast<int>(0x80004005u);
    unsigned int restored;
    int result = buffer->RestoreIfLost(&restored);
    if (result < 0)
        return result;
    if (restored) {
        result = SoundStream_FillBuffer_0044d110(stream, buffer, 0);
        if (result < 0)
            return result;
        stream->RewindBuffers();
    }
    stream->fade_mode = 0;
    stream->fade_remaining = 0;
    stream->fade_duration = 0;
    stream->SetVolume(0);
    stream->playing = 1;
    stream->play_priority = priority;
    stream->play_flags = flags;
    stream->unknown_2c = 0;
    // The selected interface remains cached even if callbacks replace the
    // array or stream's first buffer. Play failure does not roll back state.
    return buffer->methods->play(buffer, 0, priority, flags);
}
