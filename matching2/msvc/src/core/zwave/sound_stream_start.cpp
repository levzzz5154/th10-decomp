// 0x0044D440, complete 145-byte stream start. Native LTCG assigns stream
// to EAX; priority and flags remain on the stack, with RET 8.
#include "th10/game/sound_start_context.hpp"
#pragma code_seg(".text$09start")
extern "C" __declspec(noinline) int __stdcall SoundStreamStart(SoundStream* stream,
        unsigned int priority, unsigned int flags) {
    if (!stream->buffers) return (int)0x800401f0u;
    WaveBuffer* buffer = reinterpret_cast<WaveBuffer*>(
        reinterpret_cast<PlatformInterfaceState*>(stream)->FindAvailable());
    if (!buffer) return (int)0x80004005u;
    unsigned int restored;
    int result = reinterpret_cast<PlatformD300Entry*>(buffer)->Run(&restored);
    if (result < 0) return result;
    if (restored) {
        result = SoundStreamFill(stream, buffer, 0);
        if (result < 0) return result;
        reinterpret_cast<PlatformQueryInterfaces*>(stream)->Query();
    }
    stream->fade_mode = 0;
    stream->fade_remaining = 0;
    stream->fade_duration = 0;
    reinterpret_cast<PlatformInterfaceState2*>(stream)->SetOperationDeadline(0);
    stream->playing = 1;
    stream->play_priority = priority;
    stream->play_flags = flags;
    stream->unknown2c = 0;
    // Cache the selected buffer across callbacks. A failed Play keeps the
    // published playing flag and parameters, just as the original does.
    return buffer->methods->play(buffer, 0, priority, flags);
}
#pragma code_seg()
