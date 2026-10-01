// 0x0044C7E0: configure the DirectSound primary buffer's PCM format.
// Whole native260 uses bitsCX, channelsBX, rateEDI and one owner-cell stack
// argument/RET4 through the complete genuine Configure caller.
#include "th10/platform/native_primary_format.hpp"

#pragma code_seg(".text$a06format")
extern "C" __declspec(noinline) int __fastcall Sound_SetPrimaryFormat_0044c7e0(unsigned short bits,
        unsigned short channels, unsigned int rate, WaveDirectSoundDevice** owner) {
    WaveSecondaryBuffer* primary = 0;
    WaveDirectSoundDevice* device = *owner;
    if (!device)
        return static_cast<int>(0x800401F0);

    WaveBufferDescription description = {};
    description.size = sizeof description;
    description.flags = 1;
    description.bytes = 0;
    description.format = 0;
    int result = device->methods->create_buffer(device, &description, &primary, 0);
    if (result < 0)
        return result;

    WaveFormatImage format = {};
    format.tag = 1;
    format.channels = channels;
    format.sample_rate = rate;
    format.bits_per_sample = bits;
    bits >>= 3;
    bits = static_cast<unsigned short>(bits * channels);
    format.block_alignment = bits;
    format.average_bytes_per_second = bits * rate;
    result = primary->methods->set_format(primary, &format);
    if (result < 0)
        return result;
    // The output address escaped through CreateSoundBuffer. Reload its value
    // after SetFormat, including a callback that clears/replaces the pointer.
    if (primary)
        primary->methods->release(primary);
    // Create/SetFormat failure intentionally does not release the buffer.
    return 0;
}

#pragma code_seg()
