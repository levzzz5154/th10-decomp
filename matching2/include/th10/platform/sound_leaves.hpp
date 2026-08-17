#pragma once

#include <cstdint>

// 0x00420C30 - Play the random voice cue: draw a 64-bit random value
// (retail 0x00463B2C) and pass its low half to the sound-play edge
// (retail 0x0043E460) with an empty name and mode 5. Always returns 0.
uint32_t Sound_PlayRandomVoice(uint64_t (*random)(),
                               void (*play)(const char* name, int32_t mode,
                                            int32_t value));

// Sound-buffer base vtable image (retail 0x004705D4; the host test
// provides the symbol).
extern const void* PTR_FUN_004705d4;

// 0x0044D730 - Sound-buffer destructor leaf: install the base vtable
// pointer and run the shared release body (retail 0x0044D080, injected).
void SoundBuffer_DestructBase(void** object, void (*release)(void** object));
