#include "th10/platform/sound_leaves.hpp"

// 0x00420C30 - Play the random voice cue. The 64-bit random draw and
// the sound-play edge are injected; retail truncates the draw to its
// low 32 bits for the play argument.
uint32_t Sound_PlayRandomVoice(uint64_t (*random)(),
                               void (*play)(const char* name, int32_t mode,
                                            int32_t value)) {
    const uint64_t value = random != 0 ? random() : 0;
    if (play != 0) {
        play("", 5, (int32_t)value);
    }
    return 0;
}

// 0x0044D730 - Sound-buffer destructor leaf. Retail overwrites the
// object's vtable slot with the base image at 0x004705D4 and tail-calls
// the shared release body at 0x0044D080.
void SoundBuffer_DestructBase(void** object, void (*release)(void** object)) {
    *object = (void*)&PTR_FUN_004705d4;
    if (release != 0) {
        release(object);
    }
}
