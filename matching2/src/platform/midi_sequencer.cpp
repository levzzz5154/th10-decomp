#include "th10/platform/midi_sequencer.hpp"

// See th10/platform/midi_sequencer.hpp for the field map, the tick-clock model
// and the evidence that identified the subsystem.

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

// 0x0043ACE0 - Rewind the sequencer. Retail clears the pair at
// +0x2DC/+0x2E0 and the four position words at +0x128..+0x134, resets
// the scale at +0x2C8 to 1.0, and walks the track table at +0x138
// (count at +0x118): each track's cursor and loop pointer rewind to the
// chunk start, the active word becomes 1, and the first event delta is
// primed with the inlined variable-length read (the same loop as
// 0x0043A730).
void MidiSequencer_ResetTracks(MidiSequencer* sequencer) {
	sequencer->volume_scale = 1.0f;
	sequencer->reset_scratch_2dc = 0;
	// The second word of the cleared pair is the pump's fade enable, so a
	// rewind also cancels an in-flight fade.
	sequencer->fade_enabled = 0;
	sequencer->frame_counter_lo = 0;
	sequencer->frame_counter_hi = 0;
	// Retail zeroes +0x130 and +0x134 as two words; they are the halves of
	// the 64-bit tick base.
	sequencer->base_ticks = 0;
	for (int32_t index = 0; index < sequencer->track_count; ++index) {
		MidiTrack* track = &sequencer->tracks[index];
		track->cursor = track->data;
		track->loop_start = track->data;
		track->active = 1;
		track->next_event_tick = Midi_ReadVariableLength(&track->cursor);
	}
}

// Retail inlines __allmul(tick_scale, counter), a second __allmul by 1000 and
// an unsigned __aulldiv by the tempo. The unsigned divide is preserved
// deliberately: a negative tempo would wrap here exactly as it does in the
// original.
int64_t MidiSequencer_ElapsedTicks(const MidiSequencer* sequencer) {
	int64_t counter =
	    (int64_t)(((uint64_t)sequencer->frame_counter_hi << 32) |
	              (uint64_t)sequencer->frame_counter_lo);
	int64_t product = (int64_t)sequencer->tick_scale * counter;
	product *= 1000;
	return (int64_t)((uint64_t)product /
	                 (uint64_t)(int64_t)sequencer->tempo);
}

int64_t MidiSequencer_CurrentTick(const MidiSequencer* sequencer) {
	return MidiSequencer_ElapsedTicks(sequencer) + sequencer->base_ticks;
}

// 0x0043B110 - decode and perform one event on a single track.
void MidiSequencer_DispatchEvent(MidiSequencer* sequencer, MidiTrack* track,
                                 MidiSequencerEnv* env) {
	uint8_t status = *track->cursor;
	uint8_t data1 = 0;
	uint8_t data2 = 0;

	// Running status: a byte below 0x80 is already the first data byte, so
	// the cached status is reused and the cursor is left alone.
	if (status < 0x80)
		status = track->running_status;
	else
		++track->cursor;

	uint8_t channel = (uint8_t)(status & 0x0Fu);

	switch (status & 0xF0u) {
	case 0x80:
	case 0x90:
	case 0xA0:
	case 0xB0:
	case 0xE0:
		data1 = track->cursor[0];
		data2 = track->cursor[1];
		track->cursor += 2;
		break;
	case 0xC0:
	case 0xD0:
		data1 = *track->cursor;
		++track->cursor;
		data2 = 0;
		break;
	case 0xF0:
		if (status == 0xF0) {
			// System exclusive: rebuild the message into a fresh MIDIHDR
			// taken from the 32-slot round-robin at seq+0x14.
			if (sequencer->sysex_headers[sequencer->sysex_index] != 0)
				env->release_sysex(sequencer->sysex_index, sequencer);

			MidiHeader* header = env->allocate_header();
			sequencer->sysex_headers[sequencer->sysex_index] = header;
			int32_t length = Midi_ReadVariableLength(&track->cursor);

			// Retail zeroes all sixteen dwords of the MIDIHDR here.
			header->data = 0;
			header->buffer_length = 0;
			header->flags = 0;

			// The 0xF0 status is re-emitted as the first payload byte, so
			// the buffer is one byte longer than the declared length.
			uint8_t* buffer = env->allocate_buffer(length + 1);
			header->data = buffer;
			buffer[0] = 0xF0;
			header->flags = 0;
			header->buffer_length = (uint32_t)(length + 1);
			for (int32_t index = 0; index < length; ++index) {
				buffer[index + 1] = *track->cursor;
				++track->cursor;
			}

			if (sequencer->midi_out != 0 &&
			    (env->midi_prepare_header(sequencer->midi_out, header,
			                              0x40) != 0 ||
			     env->midi_long_msg(sequencer->midi_out, header, 0x40) !=
			         0)) {
				// Either call failing frees the payload and the header and
				// clears the slot. A null device leaves the header parked
				// in the slot instead.
				if (header->data != 0) {
					env->release_buffer(header->data);
					header->data = 0;
				}
				env->release_header(header);
				sequencer->sysex_headers[sequencer->sysex_index] = 0;
			}

			// Retail spells this as the MSVC signed modulo-32 idiom
			// ((index + 1) & 0x8000001F with a negative fixup).
			sequencer->sysex_index = (sequencer->sysex_index + 1) % 32;
		} else if (status == 0xFF) {
			uint8_t meta_type = *track->cursor;
			++track->cursor;
			int32_t length = Midi_ReadVariableLength(&track->cursor);

			if (meta_type == 0x2F) {
				// End of track. Retires the track and returns without
				// storing running status or reading a delta time; this is
				// what breaks the pump's re-dispatch loop, and only
				// 0x0043ACE0 sets the flag back.
				track->active = 0;
				return;
			}
			if (meta_type == 0x51) {
				// Set tempo: fold the ticks played at the old tempo into
				// the base, restart the frame counter, then accumulate the
				// new tempo.
				sequencer->base_ticks +=
				    MidiSequencer_ElapsedTicks(sequencer);
				sequencer->frame_counter_lo = 0;
				sequencer->frame_counter_hi = 0;
				sequencer->tempo = 0;
				// Retail multiplies by 0x101 rather than 0x100 on each
				// byte. Reproduced verbatim; see the header's open items.
				for (; length > 0; --length) {
					sequencer->tempo =
					    sequencer->tempo * 0x101 + (int32_t)*track->cursor;
					++track->cursor;
				}
			} else {
				track->cursor += length;
			}
		}
		break;
	default:
		break;
	}

	switch (status & 0xF0u) {
	case 0x90:
		if (data2 != 0) {
			// Note on. The transpose is folded into the note number before
			// the bitmap update, and the transposed value is what goes out
			// on the wire.
			data1 = (uint8_t)(data1 + sequencer->transpose);
			sequencer->channels[channel].notes[data1 >> 3] |=
			    (uint8_t)(1u << (data1 & 7u));
			break;
		}
		// Velocity zero is a note-off; retail falls into the 0x80 case.
		[[fallthrough]];
	case 0x80:
		data1 = (uint8_t)(data1 + sequencer->transpose);
		sequencer->channels[channel].notes[data1 >> 3] &=
		    (uint8_t)~(1u << (data1 & 7u));
		break;
	case 0xB0:
		switch (data1) {
		case 0:
			sequencer->channels[channel].bank = data2;
			break;
		case 2:
			// Loop point: snapshot every track cursor plus the clock. The
			// snapshot is taken here, before the trailing delta time is
			// consumed below.
			for (int32_t index = 0; index < sequencer->track_count;
			     ++index) {
				sequencer->tracks[index].loop_start =
				    sequencer->tracks[index].cursor;
				sequencer->tracks[index].loop_next_event_tick =
				    sequencer->tracks[index].next_event_tick;
			}
			sequencer->loop_tempo = sequencer->tempo;
			sequencer->loop_counter_lo = sequencer->frame_counter_lo;
			sequencer->loop_counter_hi = sequencer->frame_counter_hi;
			sequencer->loop_base_ticks = sequencer->base_ticks;
			break;
		case 4:
			// Loop back: restore the snapshot taken by CC 2.
			for (int32_t index = 0; index < sequencer->track_count;
			     ++index) {
				sequencer->tracks[index].cursor =
				    sequencer->tracks[index].loop_start;
				sequencer->tracks[index].next_event_tick =
				    sequencer->tracks[index].loop_next_event_tick;
			}
			sequencer->tempo = sequencer->loop_tempo;
			sequencer->frame_counter_lo = sequencer->loop_counter_lo;
			sequencer->frame_counter_hi = sequencer->loop_counter_hi;
			sequencer->base_ticks = sequencer->loop_base_ticks;
			break;
		case 7: {
			// Channel volume, scaled by the master level before it is sent.
			MidiChannelState* state = &sequencer->channels[channel];
			state->volume_raw = data2;
			int32_t scaled = env->volume_from_cc((int32_t)data2);
			if (scaled < 0) {
				state->volume_effective = 0;
				data2 = 0;
			} else {
				if (scaled > 0x7F)
					scaled = 0x7F;
				data2 = (uint8_t)scaled;
				state->volume_effective = data2;
			}
			break;
		}
		case 10:
			sequencer->channels[channel].pan = data2;
			break;
		case 0x5B:
			sequencer->channels[channel].cc_5b = data2;
			break;
		case 0x5D:
			sequencer->channels[channel].cc_5d = data2;
			break;
		default:
			break;
		}
		break;
	case 0xC0:
		sequencer->channels[channel].program = data1;
		break;
	default:
		break;
	}

	// Channel messages go to the device as a packed short message. System
	// messages never do; SysEx already went out as a long message.
	if (status < 0xF0 && sequencer->midi_out != 0) {
		env->midi_short_msg(sequencer->midi_out,
		                    (uint32_t)status | ((uint32_t)data1 << 8) |
		                        ((uint32_t)data2 << 16));
	}

	track->running_status = status;

	// Delta time to the next event. Retail inlines the same loop as
	// 0x0043A730 here rather than calling it.
	int32_t delta = 0;
	uint8_t byte;
	do {
		byte = *track->cursor;
		++track->cursor;
		delta = delta * 0x80 + (byte & 0x7F);
	} while ((byte & 0x80) != 0);
	track->next_event_tick += delta;
}

// 0x0043AF30 - one pump step per frame.
void MidiSequencer_Pump(MidiSequencer* sequencer, MidiSequencerEnv* env) {
	bool any_track_registered = false;
	int64_t now = MidiSequencer_CurrentTick(sequencer);

	if (sequencer->fade_enabled != 0) {
		if (sequencer->fade_current >= sequencer->fade_total) {
			// Ramp finished: clear the level and stop pumping entirely, so
			// no events fire and the frame counter does not advance.
			sequencer->volume_scale = 0.0f;
			return;
		}
		sequencer->volume_scale = 1.0f - (float)sequencer->fade_current /
		                                     (float)sequencer->fade_total;

		// Retail converts the level twice through _ftol and only pushes the
		// device when the integer level actually changed.
		int32_t level = env->volume_from_fade(sequencer->volume_scale);
		if (level != sequencer->volume_cached)
			env->apply_volume(0);
		sequencer->volume_cached =
		    env->volume_from_fade(sequencer->volume_scale);
		sequencer->fade_current += 1;
	}

	for (int32_t index = 0; index < sequencer->track_count; ++index) {
		MidiTrack* track = &sequencer->tracks[index];
		if (track->active == 0)
			continue;

		// Retail marks the pump busy for any occupied track, whether or not
		// it fires this step.
		any_track_registered = true;
		do {
			if ((uint64_t)now < (uint64_t)(int64_t)track->next_event_tick)
				break;
			MidiSequencer_DispatchEvent(sequencer, track, env);
			// A tempo change inside the callback rebases the clock, so the
			// position is re-read before every comparison.
			now = MidiSequencer_CurrentTick(sequencer);
		} while (track->active != 0);
	}

	uint32_t previous = sequencer->frame_counter_lo;
	sequencer->frame_counter_lo = previous + 1;
	if (previous > 0xFFFFFFFEu)
		sequencer->frame_counter_hi += 1;

	// Every track has hit its end-of-track marker: rewind and start over.
	// This is what makes playback loop.
	if (!any_track_registered)
		MidiSequencer_ResetTracks(sequencer);
}
