#pragma once

// x86 REP transfers make one unaligned 32-bit access at a time, followed by
// remaining bytes. Packed volatile words keep those widths and that order,
// including overlap and partially completed transfers at a memory fault.
#pragma pack(push, 1)
struct SoundMemoryWord { unsigned int value; };
#pragma pack(pop)

__forceinline void CopySoundWords(unsigned int destination, unsigned int source, unsigned int bytes) {
    while (bytes >= 4) {
        unsigned int word = reinterpret_cast<const volatile SoundMemoryWord*>(source)->value;
        reinterpret_cast<volatile SoundMemoryWord*>(destination)->value = word;
        source += 4;
        destination += 4;
        bytes -= 4;
    }
    while (bytes--) {
        unsigned char byte = *reinterpret_cast<const volatile unsigned char*>(source++);
        *reinterpret_cast<volatile unsigned char*>(destination++) = byte;
    }
}

__forceinline void FillSoundBytes(unsigned int destination, unsigned int bytes, unsigned char value) {
    const unsigned int word = static_cast<unsigned int>(value) * 0x01010101u;
    while (bytes >= 4) {
        reinterpret_cast<volatile SoundMemoryWord*>(destination)->value = word;
        destination += 4;
        bytes -= 4;
    }
    while (bytes--)
        *reinterpret_cast<volatile unsigned char*>(destination++) = value;
}
