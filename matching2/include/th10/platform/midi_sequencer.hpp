#pragma once

// MIDI sequencer pump and event dispatcher (retail 0x0043AF30, 0x0043B110).
//
// Evidence chain that identified the subsystem:
// - 0x0043B110 calls midiOutPrepareHeader, midiOutLongMsg and
//   midiOutShortMsg on the HMIDIOUT stored at seq+0x13C, so the pair is the
//   MIDI playback engine and not the window/message helper the tracking
//   names suggested.
// - 0x0043AF30 is the only caller of 0x0043B110. It walks seq+0x138 in
//   0x20-byte strides; the CC 2 / CC 4 handlers inside 0x0043B110
//   independently confirm that stride by stepping the same array eight
//   dwords at a time.
// - The per-channel state blocks are 0x17 bytes starting at seq+0x154.
//   Sixteen of them end at 0x154 + 16 * 0x17 = 0x2C4, which is exactly the
//   transpose byte the note handlers read - so the channel count is 16 and
//   the block layout below is bounded on both sides.
// - Meta 0x2F (End of Track) clears track+0x00, which is what terminates
//   the re-dispatch loop in 0x0043AF30. The two functions cannot be tested
//   independently and land as one batch.
//
// Clock model. seq+0x130 is a 64-bit tick base, seq+0x128/+0x12C a 64-bit
// frame counter, seq+0x120 a precomputed (frame period * PPQN) scale and
// seq+0x124 the tempo in microseconds per quarter note as written by meta
// 0x51. The pump's position is therefore in MIDI ticks:
//   now = base + tick_scale * frames * 1000 / tempo
// Meta 0x51 rebases that clock (base += elapsed, counter = 0, tempo = new),
// which is the behaviour that fixes this reading of the fields.
//
// Open item: the tempo bytes accumulate as `tempo = tempo * 0x101 + byte`,
// not the standard `* 0x100`. A compiler will not emit an imul by 257 for a
// shift by 8, so this looks like genuine retail behaviour rather than a
// decompiler artifact, and the reconstruction reproduces it. Confirm against
// ida/th10.exe.asm before treating the value as authoritative.

// ---------------------------------------------------------------------------
// 0x0043B110 - sequencer event dispatch
// ---------------------------------------------------------------------------

// The MIDIHDR slice the SysEx path touches. Retail mallocs the full
// 0x40-byte structure and zeroes all sixteen dwords before filling it in.
struct MidiHeader {
	unsigned char* data;        // MIDIHDR.lpData
	unsigned int buffer_length; // MIDIHDR.dwBufferLength
	unsigned int flags;         // MIDIHDR.dwFlags
};

// Logical view of a 0x20-byte track record from the seq+0x138 array.
// Pointers are wider than the retail dwords on a 64-bit host; only the field
// roles are reconstructed, not the byte layout.
struct MidiTrack {
	int active;                        // +0x00 (meta 0x2F clears this)
	int next_event_tick;               // +0x04 (delta times accumulate here)
	int reserved_08;                   // +0x08 (untouched by this pair)
	unsigned char running_status;      // +0x0C (low byte of the dword)
	int reserved_10;                   // +0x10 (untouched by this pair)
	const unsigned char* cursor;       // +0x14 (event stream read pointer)
	const unsigned char* saved_cursor; // +0x18 (CC 2 snapshot of +0x14)
	int saved_next_event_tick;         // +0x1C (CC 2 snapshot of +0x04)
};

// 0x17-byte per-channel block at seq+0x154 + channel * 0x17.
struct MidiChannelState {
	unsigned char notes[16];        // +0x00 note-on bitmap, 128 notes
	unsigned char program;          // +0x10 program change
	unsigned char bank;             // +0x11 CC 0
	unsigned char pan;              // +0x12 CC 10
	unsigned char cc_5b;            // +0x13 CC 0x5B
	unsigned char cc_5d;            // +0x14 CC 0x5D
	unsigned char volume_raw;       // +0x15 CC 7 as written by the stream
	unsigned char volume_effective; // +0x16 CC 7 after master scaling
};

struct MidiSequencer {
	MidiHeader* sysex_headers[32];  // +0x14 round-robin SysEx headers
	int sysex_index;                // +0x94 (advances modulo 32)
	int track_count;                // +0x118
	int tick_scale;                 // +0x120 frame period * PPQN
	int tempo;                      // +0x124 microseconds per quarter note
	unsigned int frame_counter_lo;  // +0x128 frames since the last rebase
	unsigned int frame_counter_hi;  // +0x12C
	long long base_ticks;           // +0x130 tick base at the last rebase
	MidiTrack* tracks;              // +0x138 (0x20 stride)
	void* midi_out;                 // +0x13C HMIDIOUT (null = no device)
	MidiChannelState channels[16];  // +0x154
	signed char transpose;          // +0x2C4 added to every note number
	float fade_level;               // +0x2C8 published ramp, 1 -> 0
	int fade_volume_cached;         // +0x2CC last integer level pushed
	int fade_enabled;               // +0x2E0
	int fade_total;                 // +0x2E4 ramp length in pump steps
	int fade_current;               // +0x2E8 current ramp step
	int loop_tempo;                 // +0x2EC CC 2 snapshot of +0x124
	unsigned int loop_counter_lo;   // +0x2F0 CC 2 snapshot of +0x128
	unsigned int loop_counter_hi;   // +0x2F4 CC 2 snapshot of +0x12C
	long long loop_base_ticks;      // +0x2F8/+0x2FC snapshot of +0x130
};

struct MidiSequencerEnv {
	// 0x0043A730: reads a variable-length quantity from the track cursor and
	// leaves the cursor past it.
	int (*read_varint)(MidiTrack* track);
	// 0x0043AEB0: unprepares and frees the SysEx header in the given slot.
	void (*release_sysex)(int slot, MidiSequencer* sequencer);

	// _malloc(0x40) / _malloc(length + 1) and their matching frees.
	MidiHeader* (*allocate_header)();
	void (*release_header)(MidiHeader* header);
	unsigned char* (*allocate_buffer)(int size);
	void (*release_buffer)(unsigned char* buffer);

	// midiOutPrepareHeader / midiOutLongMsg return an MMRESULT; nonzero is a
	// failure and triggers the cleanup path. midiOutShortMsg takes the packed
	// status | data1 << 8 | data2 << 16 word.
	int (*midi_prepare_header)(void* midi_out, MidiHeader* header, int size);
	int (*midi_long_msg)(void* midi_out, MidiHeader* header, int size);
	void (*midi_short_msg)(void* midi_out, unsigned int message);

	// Both of these are retail 0x00463B2C (_ftol). Ghidra dropped the
	// floating-point operand in each case, so the exact master-volume
	// multiplier is not recoverable from the pseudocode and has to come from
	// the asm. The reconstruction keeps them as two hooks because the CC 7
	// path scales a stream byte while the fade path converts the ramp.
	int (*volume_from_cc)(int raw_value);
	int (*volume_from_fade)(float level);

	// 0x0043B7A0: pushes the current fade level to the device.
	void (*apply_volume)(int reason);
	// 0x0043ACE0: idle/yield taken when no track is registered at all.
	void (*idle)();
};

// Ticks accumulated since the last tempo rebase (retail's inlined
// __allmul/__aulldiv chain, without the base).
long long MidiSequencer_ElapsedTicks(const MidiSequencer* sequencer);

// Absolute tick position: base + elapsed.
long long MidiSequencer_CurrentTick(const MidiSequencer* sequencer);

// Decodes and performs exactly one event on the given track, honouring
// running status, then consumes the following delta time into
// track->next_event_tick. Meta 0x2F returns early without a delta read.
void MidiSequencer_DispatchEvent(MidiSequencer* sequencer, MidiTrack* track,
                                 MidiSequencerEnv* env);

// ---------------------------------------------------------------------------
// 0x0043AF30 - sequencer pump, one call per frame
// ---------------------------------------------------------------------------
// Advances the fade ramp, drains every due event on every active track, then
// increments the 64-bit frame counter. Calls env->idle() only when no track
// is registered - an occupied but not-yet-due track suppresses it.
void MidiSequencer_Pump(MidiSequencer* sequencer, MidiSequencerEnv* env);
