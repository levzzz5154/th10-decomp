// Behavioral recovery of 0x0044C7E0 (260 bytes), historically misidentified
// as a joystick-property setter. Retail receives bits in CX, channels in BX,
// sample rate in EDI and a device-owner cell on the stack (RET 4).
#include "sound_wave_types.hpp"

extern "C" int __stdcall Sound_SetPrimaryFormat_0044c7e0(unsigned short bits,
        unsigned short channels, unsigned int rate, WaveDirectSoundDevice** owner) {
    WaveDirectSoundDevice* device = *owner;
    if (!device)
        return static_cast<int>(0x800401F0);

    WaveSecondaryBuffer* primary = 0;
    WaveBufferDescription description = {};
    description.size = sizeof description;
    description.flags = 1;
    int result = device->methods->create_buffer(device, &description, &primary, 0);
    if (result < 0)
        return result;

    const unsigned short alignment = static_cast<unsigned short>((bits >> 3) * channels);
    WaveFormatImage format = {1, channels, rate, alignment * rate, alignment, bits, 0};
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
