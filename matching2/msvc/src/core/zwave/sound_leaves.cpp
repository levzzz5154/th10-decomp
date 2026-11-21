// 0x0044D730: SoundBuffer_DestructBase
#include "th10/runtime/asm_symbols.hpp"
#include "th10/platform/sound_buffer.hpp"


// 0x0044D730..0x0044D73A: restore the derived vtable, then let the shared
// owned-array base destructor release the DirectSound buffers.
void __fastcall SoundBuffer_DestructBase(SoundBuffer* sound_buffer) {
    sound_buffer->vtable = &sound_buffer_vtable;
    SoundBufferBase_Release(sound_buffer);
}
