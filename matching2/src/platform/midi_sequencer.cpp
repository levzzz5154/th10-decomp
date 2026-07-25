#include "th10/platform/midi_sequencer.hpp"

// 0x0043AF30 and 0x0043B110 - the MIDI sequencer pump and its event
// dispatcher. See th10/platform/midi_sequencer.hpp for the field map, the
// tick-clock model and the evidence that identified the subsystem.

// Retail inlines __allmul(tick_scale, counter), a second __allmul by 1000 and
// an unsigned __aulldiv by the tempo. The unsigned divide is preserved
// deliberately: a negative tempo would wrap here exactly as it does in the
// original.
long long MidiSequencer_ElapsedTicks(const MidiSequencer* sequencer) {
	long long counter =
	    (long long)(((unsigned long long)sequencer->frame_counter_hi << 32) |
	                (unsigned long long)sequencer->frame_counter_lo);
	long long product = (long long)sequencer->tick_scale * counter;
	product *= 1000;
	return (long long)((unsigned long long)product /
	                   (unsigned long long)(long long)sequencer->tempo);
}

long long MidiSequencer_CurrentTick(const MidiSequencer* sequencer) {
	return MidiSequencer_ElapsedTicks(sequencer) + sequencer->base_ticks;
}

// 0x0043B110 - decode and perform one event on a single track.
void MidiSequencer_DispatchEvent(MidiSequencer* sequencer, MidiTrack* track,
                                 MidiSequencerEnv* env) {
	unsigned char status = *track->cursor;
	unsigned char data1 = 0;
	unsigned char data2 = 0;

	// Running status: a byte below 0x80 is already the first data byte, so
	// the cached status is reused and the cursor is left alone.
	if (status < 0x80)
		status = track->running_status;
	else
		++track->cursor;

	unsigned char channel = (unsigned char)(status & 0x0Fu);

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
			int length = env->read_varint(track);

			// Retail zeroes all sixteen dwords of the MIDIHDR here.
			header->data = 0;
			header->buffer_length = 0;
			header->flags = 0;

			// The 0xF0 status is re-emitted as the first payload byte, so
			// the buffer is one byte longer than the declared length.
			unsigned char* buffer = env->allocate_buffer(length + 1);
			header->data = buffer;
			buffer[0] = 0xF0;
			header->flags = 0;
			header->buffer_length = (unsigned int)(length + 1);
			for (int index = 0; index < length; ++index) {
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
			unsigned char meta_type = *track->cursor;
			++track->cursor;
			int length = env->read_varint(track);

			if (meta_type == 0x2F) {
				// End of track. Retires the track and returns without
				// storing running status or reading a delta time; this is
				// what breaks the pump's re-dispatch loop.
				track->active = 0;
				return;
			}
			if (meta_type == 0x51) {
				// Set tempo: fold the ticks played at the old tempo into
				// the base, restart the frame counter, then accumulate the
				// new tempo.
				sequencer->base_ticks += MidiSequencer_ElapsedTicks(sequencer);
				sequencer->frame_counter_lo = 0;
				sequencer->frame_counter_hi = 0;
				sequencer->tempo = 0;
				// Retail multiplies by 0x101 rather than 0x100 on each
				// byte. Reproduced verbatim; see the header's open item.
				for (; length > 0; --length) {
					sequencer->tempo =
					    sequencer->tempo * 0x101 + (int)*track->cursor;
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
			data1 = (unsigned char)(data1 + sequencer->transpose);
			sequencer->channels[channel].notes[data1 >> 3] |=
			    (unsigned char)(1u << (data1 & 7u));
			break;
		}
		// Velocity zero is a note-off; retail falls into the 0x80 case.
		[[fallthrough]];
	case 0x80:
		data1 = (unsigned char)(data1 + sequencer->transpose);
		sequencer->channels[channel].notes[data1 >> 3] &=
		    (unsigned char)~(1u << (data1 & 7u));
		break;
	case 0xB0:
		switch (data1) {
		case 0:
			sequencer->channels[channel].bank = data2;
			break;
		case 2:
			// Loop point: snapshot every track cursor plus the clock.
			for (int index = 0; index < sequencer->track_count; ++index) {
				sequencer->tracks[index].saved_cursor =
				    sequencer->tracks[index].cursor;
				sequencer->tracks[index].saved_next_event_tick =
				    sequencer->tracks[index].next_event_tick;
			}
			sequencer->loop_tempo = sequencer->tempo;
			sequencer->loop_counter_lo = sequencer->frame_counter_lo;
			sequencer->loop_counter_hi = sequencer->frame_counter_hi;
			sequencer->loop_base_ticks = sequencer->base_ticks;
			break;
		case 4:
			// Loop back: restore the snapshot taken by CC 2.
			for (int index = 0; index < sequencer->track_count; ++index) {
				sequencer->tracks[index].cursor =
				    sequencer->tracks[index].saved_cursor;
				sequencer->tracks[index].next_event_tick =
				    sequencer->tracks[index].saved_next_event_tick;
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
			int scaled = env->volume_from_cc((int)data2);
			if (scaled < 0) {
				state->volume_effective = 0;
				data2 = 0;
			} else {
				if (scaled > 0x7F)
					scaled = 0x7F;
				data2 = (unsigned char)scaled;
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
		                    (unsigned int)status |
		                        ((unsigned int)data1 << 8) |
		                        ((unsigned int)data2 << 16));
	}

	track->running_status = status;

	// Delta time to the next event, as a variable-length quantity.
	int delta = 0;
	unsigned char byte;
	do {
		byte = *track->cursor;
		++track->cursor;
		delta = delta * 0x80 + (int)(byte & 0x7Fu);
	} while ((signed char)byte < 0);
	track->next_event_tick += delta;
}

// 0x0043AF30 - one pump step per frame.
void MidiSequencer_Pump(MidiSequencer* sequencer, MidiSequencerEnv* env) {
	bool any_track_registered = false;
	long long now = MidiSequencer_CurrentTick(sequencer);

	if (sequencer->fade_enabled != 0) {
		if (sequencer->fade_current >= sequencer->fade_total) {
			// Ramp finished: clear the level and stop pumping entirely, so
			// no events fire and the frame counter does not advance.
			sequencer->fade_level = 0.0f;
			return;
		}
		sequencer->fade_level = 1.0f - (float)sequencer->fade_current /
		                                   (float)sequencer->fade_total;

		// Retail converts the level twice through _ftol and only pushes the
		// device when the integer level actually changed.
		int level = env->volume_from_fade(sequencer->fade_level);
		if (level != sequencer->fade_volume_cached)
			env->apply_volume(0);
		sequencer->fade_volume_cached =
		    env->volume_from_fade(sequencer->fade_level);
		sequencer->fade_current += 1;
	}

	for (int index = 0; index < sequencer->track_count; ++index) {
		MidiTrack* track = &sequencer->tracks[index];
		if (track->active == 0)
			continue;

		// Retail marks the pump busy for any occupied track, whether or not
		// it fires this step.
		any_track_registered = true;
		do {
			if ((unsigned long long)now <
			    (unsigned long long)(long long)track->next_event_tick)
				break;
			MidiSequencer_DispatchEvent(sequencer, track, env);
			// A tempo change inside the callback rebases the clock, so the
			// position is re-read before every comparison.
			now = MidiSequencer_CurrentTick(sequencer);
		} while (track->active != 0);
	}

	unsigned int previous = sequencer->frame_counter_lo;
	sequencer->frame_counter_lo = previous + 1;
	if (previous > 0xFFFFFFFEu)
		sequencer->frame_counter_hi += 1;

	if (!any_track_registered)
		env->idle();
}
