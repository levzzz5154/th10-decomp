#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/platform/sound_buffer.hpp"


// 0x0044D730..0x0044D73A: restore the derived vtable, then let the shared
// owned-array base destructor release the DirectSound buffers.
void __fastcall SoundBuffer_DestructBaseRetail(SoundBuffer* sound_buffer) {
    sound_buffer->vtable = &sound_buffer_vtable_004705d4;
    Platform_ReleaseOwnedArray(sound_buffer);
}
