#pragma once

#include <cstdint>

// MIDI sequencer: variable-length reader (0x0043A730), track rewind
// (0x0043ACE0), event dispatch (0x0043B110) and the per-frame pump
// (0x0043AF30).
//
// 0x0043A730 and 0x0043ACE0 were recovered first; the dispatcher and pump were
// added afterwards and refine the field map, so the struct comments below note
// where the earlier reading has been renamed.
//
// Evidence chain for the dispatcher/pump pair:
// - 0x0043B110 calls midiOutPrepareHeader, midiOutLongMsg and
//   midiOutShortMsg on the HMIDIOUT stored at seq+0x13C, so this is the MIDI
//   playback engine and not the window/message helper the tracking names
//   suggested.
// - 0x0043AF30 is the only caller of 0x0043B110. It walks seq+0x138 in
//   0x20-byte strides; the CC 2 / CC 4 handlers inside 0x0043B110
//   independently confirm that stride by stepping the same array eight
//   dwords at a time.
// - The per-channel state blocks are 0x17 bytes starting at seq+0x154.
//   Sixteen of them end at 0x154 + 16 * 0x17 = 0x2C4, which is exactly the
//   transpose byte the note handlers read, so the channel count is 16 and
//   the block layout is bounded on both sides.
// - Meta 0x2F (End of Track) clears track+0x00, which is what terminates the
//   re-dispatch loop in 0x0043AF30, and 0x0043ACE0 is what sets it back to 1.
//   The pump calls the rewind when no track is left occupied, so the three
//   functions together are what makes playback loop seamlessly.
//
// Clock model. seq+0x130 is a 64-bit tick base, seq+0x128/+0x12C a 64-bit
// frame counter, seq+0x120 a precomputed (frame period * PPQN) scale and
// seq+0x124 the tempo in microseconds per quarter note as written by meta
// 0x51. The pump's position is therefore in MIDI ticks:
//   now = base + tick_scale * frames * 1000 / tempo
// Meta 0x51 rebases that clock (base += elapsed, counter = 0, tempo = new),
// and 0x0043ACE0 zeroes all four words, which is the behaviour that fixes
// this reading of the fields.
//
// Open items, both needing ida/th10.exe.asm to settle:
// - Meta 0x51 accumulates the tempo bytes as `tempo = tempo * 0x101 + byte`,
//   not the standard `* 0x100`. A compiler will not emit an imul by 257 for a
//   shift by 8, so this looks like genuine retail behaviour rather than a
//   decompiler artifact, and the reconstruction reproduces it.
// - 0x0043ACE0 clears a pair at +0x2DC/+0x2E0 that the earlier recovery read
//   as a second elapsed counter. +0x2E0 is the fade enable as far as the pump
//   is concerned (clearing it on rewind is consistent: a rewind cancels an
//   in-flight fade), and +0x2DC is not touched by either of the new
//   functions, so it is kept as scratch below.

// The MIDIHDR slice the SysEx path touches. Retail mallocs the full
// 0x40-byte structure and zeroes all sixteen dwords before filling it in.
struct MidiHeader {
	uint8_t* data;           // MIDIHDR.lpData
	uint32_t buffer_length;  // MIDIHDR.dwBufferLength
	uint32_t flags;          // MIDIHDR.dwFlags
};

// One sequencer track record (retail 0x20 bytes; word offsets in comments --
// the data pointers are 32-bit slots in retail).
struct MidiTrack {
	uint32_t active;               // word 0, set to 1 on reset
	int32_t next_event_tick;       // word 1, first varint of the track;
	                               // delta times accumulate onto it
	uint32_t reserved_08;          // word 2
	uint8_t running_status;        // word 3, low byte (was reserved_0c)
	const uint8_t* data;           // word 4, start of the track chunk
	const uint8_t* cursor;         // word 5, read position
	const uint8_t* loop_start;     // word 6, rewound with the cursor, and
	                               // snapshotted by CC 2
	int32_t loop_next_event_tick;  // word 7, CC 2 snapshot of word 1 (was
	                               // reserved_1c)
};

// 0x17-byte per-channel block at seq+0x154 + channel * 0x17.
struct MidiChannelState {
	uint8_t notes[16];        // +0x00 note-on bitmap, 128 notes
	uint8_t program;          // +0x10 program change
	uint8_t bank;             // +0x11 CC 0
	uint8_t pan;              // +0x12 CC 10
	uint8_t cc_5b;            // +0x13 CC 0x5B
	uint8_t cc_5d;            // +0x14 CC 0x5D
	uint8_t volume_raw;       // +0x15 CC 7 as written by the stream
	uint8_t volume_effective; // +0x16 CC 7 after master scaling
};

// Sequencer fragment (retail offsets in comments).
struct MidiSequencer {
	MidiHeader* sysex_headers[32];  // +0x14 round-robin SysEx headers
	int32_t sysex_index;            // +0x94 advances modulo 32
	int32_t track_count;            // +0x118
	int32_t tick_scale;             // +0x120 frame period * PPQN
	int32_t tempo;                  // +0x124 microseconds per quarter note
	uint32_t frame_counter_lo;      // +0x128 frames since the last rebase
	uint32_t frame_counter_hi;      // +0x12C
	int64_t base_ticks;             // +0x130/+0x134 tick base at the rebase
	MidiTrack* tracks;              // +0x138 (0x20 stride)
	void* midi_out;                 // +0x13C HMIDIOUT (null = no device)
	MidiChannelState channels[16];  // +0x154
	int8_t transpose;               // +0x2C4 added to every note number
	float volume_scale;             // +0x2C8 reset to 1.0f, ramped down by
	                                // the fade (was tempo_scale: it feeds the
	                                // volume apply, not the tick clock)
	int32_t volume_cached;          // +0x2CC last integer level pushed
	uint32_t reset_scratch_2dc;     // +0x2DC cleared by the rewind only
	int32_t fade_enabled;           // +0x2E0
	int32_t fade_total;             // +0x2E4 ramp length in pump steps
	int32_t fade_current;           // +0x2E8 current ramp step
	int32_t loop_tempo;             // +0x2EC CC 2 snapshot of +0x124
	uint32_t loop_counter_lo;       // +0x2F0 CC 2 snapshot of +0x128
	uint32_t loop_counter_hi;       // +0x2F4 CC 2 snapshot of +0x12C
	int64_t loop_base_ticks;        // +0x2F8/+0x2FC snapshot of +0x130
};

// Unrecovered callees reached by the dispatcher and the pump.
struct MidiSequencerEnv {
	// 0x0043AEB0: unprepares and frees the SysEx header in the given slot.
	void (*release_sysex)(int32_t slot, MidiSequencer* sequencer);

	// _malloc(0x40) / _malloc(length + 1) and their matching frees.
	MidiHeader* (*allocate_header)();
	void (*release_header)(MidiHeader* header);
	uint8_t* (*allocate_buffer)(int32_t size);
	void (*release_buffer)(uint8_t* buffer);

	// midiOutPrepareHeader / midiOutLongMsg return an MMRESULT; nonzero is a
	// failure and triggers the cleanup path. midiOutShortMsg takes the packed
	// status | data1 << 8 | data2 << 16 word.
	int32_t (*midi_prepare_header)(void* midi_out, MidiHeader* header,
	                               int32_t size);
	int32_t (*midi_long_msg)(void* midi_out, MidiHeader* header, int32_t size);
	void (*midi_short_msg)(void* midi_out, uint32_t message);

	// Both of these are retail 0x00463B2C (_ftol). Ghidra dropped the
	// floating-point operand in each case, so the exact master-volume
	// multiplier is not recoverable from the pseudocode and has to come from
	// the asm. They stay as two hooks because the CC 7 path scales a stream
	// byte while the fade path converts the ramp.
	int32_t (*volume_from_cc)(int32_t raw_value);
	int32_t (*volume_from_fade)(float level);

	// 0x0043B7A0: pushes the current volume level to the device.
	void (*apply_volume)(int32_t reason);
};

// 0x0043A730 - Read one standard MIDI variable-length quantity at the
// cursor, advancing it. Retail keeps the cursor pointer in ESI.
int32_t Midi_ReadVariableLength(const uint8_t** cursor);

// 0x0043ACE0 - Rewind the sequencer: reset the volume scale and the
// elapsed/position accumulators, then rewind every track's cursor and
// loop pointer to the track data start, mark it active, and prime its
// first event delta by reading the leading variable-length quantity.
void MidiSequencer_ResetTracks(MidiSequencer* sequencer);

// Ticks accumulated since the last tempo rebase (retail's inlined
// __allmul/__aulldiv chain, without the base).
int64_t MidiSequencer_ElapsedTicks(const MidiSequencer* sequencer);

// Absolute tick position: base + elapsed.
int64_t MidiSequencer_CurrentTick(const MidiSequencer* sequencer);

// 0x0043B110 - Decode and perform exactly one event on the given track,
// honouring running status, then consume the following delta time into
// track->next_event_tick. Meta 0x2F returns early without a delta read.
void MidiSequencer_DispatchEvent(MidiSequencer* sequencer, MidiTrack* track,
                                 MidiSequencerEnv* env);

// 0x0043AF30 - One pump step, called once per frame. Advances the fade ramp,
// drains every due event on every active track, increments the 64-bit frame
// counter, and rewinds the sequencer when no track is left occupied.
void MidiSequencer_Pump(MidiSequencer* sequencer, MidiSequencerEnv* env);
