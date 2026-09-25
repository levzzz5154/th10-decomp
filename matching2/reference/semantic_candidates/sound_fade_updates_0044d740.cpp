#include "th10/platform/sound_buffer.hpp"

// This is the same class name and declaration used by the recovered
// 0x0044D4E0 volume helper. Its first two fields match SoundBuffer.
struct PlatformD4E0Entry;
struct PlatformInterfaceState_0044D4E0 {
    unsigned char unknown_000[4];
    PlatformD4E0Entry** entries_004;
    __declspec(noinline) int SetOperationDeadline(int deadline);
};

namespace {

__forceinline void SetFadeVolume(SoundBuffer* owner, int volume) {
    reinterpret_cast<PlatformInterfaceState_0044D4E0*>(owner)
        ->SetOperationDeadline(volume);
}

} // namespace

// 0x0044D740..0x0044D782: fade mode 1 stops the first buffer when complete.
extern "C" int __fastcall SoundFade_UpdateMode1_0044d740(
    SoundBuffer* owner) {
    if (owner->fade_mode != 1)
        return 0;
    const int remaining = --owner->fade_remaining;
    if (remaining <= 0) {
        owner->fade_mode = 0;
        DirectSoundBuffer* buffer = owner->buffers[0];
        buffer->vtable->stop(buffer);
        return 1;
    }
    SetFadeVolume(owner, remaining * 5000 / owner->fade_duration - 5000);
    return 0;
}

// 0x0044D790..0x0044D7C2: fade mode 2 approaches zero volume.
extern "C" int __fastcall SoundFade_UpdateMode2_0044d790(
    SoundBuffer* owner) {
    if (owner->fade_mode != 2)
        return 0;
    const int remaining = --owner->fade_remaining;
    if (remaining <= 0) {
        owner->fade_mode = 0;
        return 1;
    }
    SetFadeVolume(owner, remaining * -5000 / owner->fade_duration);
    return 0;
}

// 0x0044D7D0..0x0044D802: fade mode 3 uses a 1000-unit range.
extern "C" int __fastcall SoundFade_UpdateMode3_0044d7d0(
    SoundBuffer* owner) {
    if (owner->fade_mode != 3)
        return 0;
    const int remaining = --owner->fade_remaining;
    if (remaining <= 0) {
        owner->fade_mode = 0;
        return 1;
    }
    SetFadeVolume(owner, remaining * -1000 / owner->fade_duration);
    return 0;
}

// 0x0044D810..0x0044D847: fade mode 4 rises from -1000 to zero.
extern "C" int __fastcall SoundFade_UpdateMode4_0044d810(
    SoundBuffer* owner) {
    if (owner->fade_mode != 4)
        return 0;
    const int remaining = --owner->fade_remaining;
    if (remaining <= 0) {
        owner->fade_mode = 0;
        return 1;
    }
    SetFadeVolume(owner, remaining * 1000 / owner->fade_duration - 1000);
    return 0;
}
