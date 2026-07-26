#include "th10/platform/midi_sequencer.hpp"

#include <cstring>

namespace {

uint16_t ReadBig16(const uint8_t* bytes) {
    return static_cast<uint16_t>(
        (static_cast<uint16_t>(bytes[0]) << 8) | bytes[1]);
}

uint32_t ReadBig32(const uint8_t* bytes) {
    return (static_cast<uint32_t>(bytes[0]) << 24) |
           (static_cast<uint32_t>(bytes[1]) << 16) |
           (static_cast<uint32_t>(bytes[2]) << 8) |
           bytes[3];
}

void ReleaseFileTracks(MidiFileState* state, const MidiFileMemory* memory) {
    if (state->tracks == nullptr)
        return;
    for (uint32_t index = 0; index < state->track_count; ++index)
        if (state->tracks[index].data != nullptr)
            memory->release(memory->context, state->tracks[index].data);
    memory->release(memory->context, state->tracks);
    state->tracks = nullptr;
    state->track_count = 0;
}

} // namespace

// 0x0043A730 - Read one standard MIDI variable-length quantity:
// accumulate seven payload bits per byte while the continuation bit
// (0x80) is set, advancing the cursor past every byte read.
int32_t Midi_ReadVariableLength(const uint8_t** cursor) {
    int32_t value = 0;
    uint8_t byte;
    do {
        byte = **cursor;
        *cursor += 1;
        value = value * 0x80 + (byte & 0x7F);
    } while ((byte & 0x80) != 0);
    return value;
}

// 0x0043ACE0 - Rewind the sequencer. Retail clears the elapsed pair at
// +0x2DC/+0x2E0 and the four position words at +0x128..+0x134, resets
// the tempo scale at +0x2C8 to 1.0, and walks the track table at +0x138
// (count at +0x118): each track's cursor and loop pointer rewind to the
// chunk start, the active word becomes 1, and the first event delta is
// primed with the inlined variable-length read (the same loop as
// 0x0043A730).
void MidiSequencer_ResetTracks(MidiSequencer* sequencer) {
    sequencer->tempo_scale = 1.0f;
    sequencer->elapsed_low = 0;
    sequencer->elapsed_high = 0;
    sequencer->position = 0;
    sequencer->position_2 = 0;
    sequencer->position_3 = 0;
    sequencer->position_4 = 0;
    for (int32_t index = 0; index < sequencer->track_count; ++index) {
        MidiTrack* track = &sequencer->tracks[index];
        track->cursor = track->data;
        track->loop_start = track->data;
        track->active = 1;
        track->next_event_delta = Midi_ReadVariableLength(&track->cursor);
    }
}

// Semantic reconstruction 0x0043AAD0 - load an in-memory SMF image.
int MidiFile_Load(MidiFileState* state, const uint8_t* image,
                  uint32_t image_size, int source_slot,
                  const MidiFileMemory* memory) {
    ReleaseFileTracks(state, memory);
    if (image == nullptr || image_size < 14 ||
        std::memcmp(image, "MThd", 4) != 0)
        return -1;
    const uint32_t header_size = ReadBig32(image + 4);
    if (header_size < 6 || header_size > image_size - 8)
        return -1;
    const uint32_t track_count = ReadBig16(image + 10);
    state->format = ReadBig16(image + 8);
    state->division = ReadBig16(image + 12);
    MidiFileTrack* tracks = static_cast<MidiFileTrack*>(
        memory->allocate(memory->context,
                         track_count * sizeof(MidiFileTrack)));
    if (track_count != 0 && tracks == nullptr)
        return -1;
    if (tracks != nullptr)
        std::memset(tracks, 0, track_count * sizeof(MidiFileTrack));
    state->tracks = tracks;
    state->track_count = track_count;

    uint32_t cursor = 8 + header_size;
    for (uint32_t index = 0; index < track_count; ++index) {
        if (cursor > image_size || image_size - cursor < 8 ||
            std::memcmp(image + cursor, "MTrk", 4) != 0) {
            ReleaseFileTracks(state, memory);
            return -1;
        }
        const uint32_t length = ReadBig32(image + cursor + 4);
        cursor += 8;
        if (length > image_size - cursor) {
            ReleaseFileTracks(state, memory);
            return -1;
        }
        uint8_t* copy = static_cast<uint8_t*>(
            memory->allocate(memory->context, length));
        if (length != 0 && copy == nullptr) {
            ReleaseFileTracks(state, memory);
            return -1;
        }
        if (length != 0)
            std::memcpy(copy, image + cursor, length);
        tracks[index].active = 1;
        tracks[index].data_size = length;
        tracks[index].data = copy;
        cursor += length;
    }
    state->source_slot = source_slot;
    state->tempo_microseconds = 1000000;
    return 0;
}

// Semantic reconstruction 0x0043AF30 - advance the MIDI event scheduler.
int MidiPlayback_Tick(MidiPlaybackState* state,
                      const MidiPlaybackHooks* hooks) {
    auto playback_time = [state]() -> uint64_t {
        if (state->time_divisor == 0)
            return state->time_base;
        return state->time_base +
               1000ull * state->time_numerator * state->tick /
                   state->time_divisor;
    };
    uint64_t current_time = playback_time();

    if (state->fade_active != 0) {
        if (state->fade_position >= state->fade_duration) {
            state->fade_volume = 0.0f;
            return static_cast<int>(state->fade_position);
        }
        state->fade_volume =
            state->fade_duration == 0
                ? 0.0f
                : 1.0f - static_cast<float>(state->fade_position) /
                             static_cast<float>(state->fade_duration);
        const uint32_t volume_step =
            static_cast<uint32_t>(state->fade_volume * 128.0f);
        if (volume_step != state->fade_volume_step)
            hooks->apply_channel_volumes(hooks->context, 0);
        state->fade_volume_step = volume_step;
        ++state->fade_position;
    }

    int any_active = 0;
    for (uint32_t index = 0; index < state->track_count; ++index) {
        MidiPlaybackTrack* track = &state->tracks[index];
        if (track->active == 0)
            continue;
        any_active = 1;
        while (track->active != 0 &&
               track->next_event_time <= current_time) {
            hooks->process_event(hooks->context, state, track);
            current_time = playback_time();
        }
    }
    ++state->tick;
    if (any_active == 0) {
        hooks->rewind(hooks->context, state);
        return 0;
    }
    return 1;
}
