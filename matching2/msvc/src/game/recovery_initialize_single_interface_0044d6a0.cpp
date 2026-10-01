void* __cdecl operator new(unsigned int bytes);
#pragma code_seg(".text$05single")
// 0x0044D6A0: streaming constructor, 109 original bytes.
// The native compiler supplies the ESI receiver and four argument stack slots.
// Allocation is unchecked; callback results are ignored and current buffer
// ownership is reloaded after refill. Native proof includes real caller EH.
#include "../../layout/ltcg/sound_interfaces_dependencies/sound_wave_types.hpp"

extern "C" {
    extern SoundStreamMethods g_sound_base_methods;
    extern SoundStreamMethods g_sound_streaming_methods;
    int __stdcall SoundStreamFill(SoundStream*, WaveSecondaryBuffer*, unsigned int);
}

SoundStreamingState::SoundStreamingState(
        WaveSecondaryBuffer* buffer, unsigned int bytes, MusicReadCursor* reader, unsigned int segment_bytes) {
    this->methods = &g_sound_base_methods;
    this->buffers = static_cast<WaveSecondaryBuffer**>(::operator new(4));
    this->buffers[0] = buffer;
    this->buffer_bytes = bytes;
    this->reader = reader;
    this->buffer_count = 1;
    SoundStreamFill(this, this->buffers[0], 0);
    buffer = this->buffers[0];
    buffer->methods->set_position(buffer, 0);
    this->playing = 0;
    this->last_play_position = 0;
    this->played_bytes = 0;
    this->write_offset = 0;
    this->end_of_stream = 0;
    this->methods = &g_sound_streaming_methods;
    this->segment_bytes = segment_bytes;

}

#pragma code_seg()
