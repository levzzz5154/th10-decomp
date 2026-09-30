// Typed recovery of 0x0044D370 (103 bytes), with explicit ordering across
// rand. The maintained source's single subscript expression permits Clang
// to cache the array before rand; retail reloads count and array afterward.
#include "sound_wave_types.hpp"

extern "C" int __cdecl asm_rand_0045371b();

WaveSecondaryBuffer* SoundStream::FindAvailable() {
    if (!buffers)
        return 0;
    unsigned int index = 0;
    for (; index < buffer_count; ++index) {
        WaveSecondaryBuffer* buffer = buffers[index];
        if (buffer) {
            unsigned int status = 0;
            buffer->methods->get_status(buffer, &status);
            if (!(status & 1))
                break;
        }
    }
    if (index != buffer_count)
        return buffers[index];
    const unsigned int random = static_cast<unsigned int>(asm_rand_0045371b());
    const unsigned int selected = random % buffer_count;
    return buffers[selected];
}
