// Tests for the MIDI sequencer: 0x0043A730 variable-length read, 0x0043ACE0
// rewind, 0x0043B110 event dispatch and the 0x0043AF30 per-frame pump.
#include "th10/platform/midi_sequencer.hpp"
#include <cstdio>
#include <cstring>

static int g_failures = 0;
#define CHECK(condition)                                                     \
	do {                                                                     \
		if (!(condition)) {                                                  \
			std::printf("CHECK failed at line %d: %s\n", __LINE__,           \
			            #condition);                                         \
			++g_failures;                                                    \
		}                                                                    \
	} while (0)

// ---------------------------------------------------------------------------
// Recording hooks
// ---------------------------------------------------------------------------

static int g_device_dummy;

static uint32_t g_messages[16];
static int g_message_count;
static void HookShortMsg(void*, uint32_t message) {
	if (g_message_count < 16)
		g_messages[g_message_count] = message;
	++g_message_count;
}

static int g_release_sysex_calls;
static int32_t g_release_sysex_slot;
static void HookReleaseSysex(int32_t slot, MidiSequencer*) {
	++g_release_sysex_calls;
	g_release_sysex_slot = slot;
}

static MidiHeader g_header_pool[4];
static int g_header_alloc_count;
static MidiHeader* HookAllocateHeader() {
	int index = g_header_alloc_count < 3 ? g_header_alloc_count : 3;
	++g_header_alloc_count;
	// Pre-dirty the header so the zeroing step is observable.
	g_header_pool[index].data = (uint8_t*)0x1;
	g_header_pool[index].buffer_length = 0xAAAA;
	g_header_pool[index].flags = 0xBBBB;
	return &g_header_pool[index];
}

static int g_header_free_count;
static void HookReleaseHeader(MidiHeader*) { ++g_header_free_count; }

static uint8_t g_buffer_pool[4][64];
static int g_buffer_alloc_count;
static int32_t g_buffer_alloc_size;
static uint8_t* HookAllocateBuffer(int32_t size) {
	int index = g_buffer_alloc_count < 3 ? g_buffer_alloc_count : 3;
	++g_buffer_alloc_count;
	g_buffer_alloc_size = size;
	std::memset(g_buffer_pool[index], 0, sizeof(g_buffer_pool[index]));
	return g_buffer_pool[index];
}

static int g_buffer_free_count;
static void HookReleaseBuffer(uint8_t*) { ++g_buffer_free_count; }

static int32_t g_prepare_result;
static int g_prepare_calls;
static int32_t g_prepare_size;
static int32_t HookPrepareHeader(void*, MidiHeader*, int32_t size) {
	++g_prepare_calls;
	g_prepare_size = size;
	return g_prepare_result;
}

static int32_t g_long_result;
static int g_long_calls;
static int32_t HookLongMsg(void*, MidiHeader*, int32_t) {
	++g_long_calls;
	return g_long_result;
}

static int32_t g_cc_scale_return;
static int g_cc_scale_calls;
static int32_t g_cc_scale_input;
static int32_t HookVolumeFromCc(int32_t raw_value) {
	++g_cc_scale_calls;
	g_cc_scale_input = raw_value;
	return g_cc_scale_return;
}

static int g_fade_scale_calls;
static float g_fade_scale_input;
static int32_t HookVolumeFromFade(float level) {
	++g_fade_scale_calls;
	g_fade_scale_input = level;
	return (int32_t)(level * 127.0f);
}

static int g_apply_volume_calls;
static void HookApplyVolume(int32_t) { ++g_apply_volume_calls; }

// ---------------------------------------------------------------------------
// Fixtures
// ---------------------------------------------------------------------------

static MidiSequencer g_seq;
static MidiTrack g_tracks[4];
static MidiSequencerEnv g_env;

static void MakeEnv() {
	std::memset(&g_env, 0, sizeof(g_env));
	g_env.release_sysex = HookReleaseSysex;
	g_env.allocate_header = HookAllocateHeader;
	g_env.release_header = HookReleaseHeader;
	g_env.allocate_buffer = HookAllocateBuffer;
	g_env.release_buffer = HookReleaseBuffer;
	g_env.midi_prepare_header = HookPrepareHeader;
	g_env.midi_long_msg = HookLongMsg;
	g_env.midi_short_msg = HookShortMsg;
	g_env.volume_from_cc = HookVolumeFromCc;
	g_env.volume_from_fade = HookVolumeFromFade;
	g_env.apply_volume = HookApplyVolume;

	g_message_count = 0;
	g_release_sysex_calls = 0;
	g_header_alloc_count = 0;
	g_header_free_count = 0;
	g_buffer_alloc_count = 0;
	g_buffer_free_count = 0;
	g_prepare_calls = 0;
	g_prepare_result = 0;
	g_long_calls = 0;
	g_long_result = 0;
	g_cc_scale_calls = 0;
	g_cc_scale_return = 0;
	g_fade_scale_calls = 0;
	g_apply_volume_calls = 0;
}

// A one-track sequencer whose clock ticks once per pump step
// (tick_scale * 1000 / tempo == 1).
static MidiTrack* MakeSequencer(const uint8_t* stream) {
	std::memset(&g_seq, 0, sizeof(g_seq));
	std::memset(g_tracks, 0, sizeof(g_tracks));
	g_seq.tracks = g_tracks;
	g_seq.track_count = 1;
	g_seq.tick_scale = 1;
	g_seq.tempo = 1000;
	g_seq.midi_out = &g_device_dummy;
	g_tracks[0].active = 1;
	g_tracks[0].data = stream;
	g_tracks[0].cursor = stream;
	return &g_tracks[0];
}

// Parks the clock so the pump never fires an event, and keeps one track
// occupied so it never rewinds either.
static void FreezeClock(MidiTrack* track) {
	g_seq.tick_scale = 0;
	track->next_event_tick = 1;
}

// ---------------------------------------------------------------------------
// 0x0043A730
// ---------------------------------------------------------------------------

static void TestReadVariableLength() {
	static const uint8_t kOne[] = {0x7F};
	const uint8_t* cursor = kOne;
	CHECK(Midi_ReadVariableLength(&cursor) == 127);
	CHECK(cursor == kOne + 1);

	static const uint8_t kTwo[] = {0x81, 0x00};
	cursor = kTwo;
	CHECK(Midi_ReadVariableLength(&cursor) == 128);
	CHECK(cursor == kTwo + 2);

	static const uint8_t kThree[] = {0xFF, 0xFF, 0x7F};
	cursor = kThree;
	CHECK(Midi_ReadVariableLength(&cursor) == 0x1FFFFF);
	CHECK(cursor == kThree + 3);
}

// ---------------------------------------------------------------------------
// 0x0043ACE0
// ---------------------------------------------------------------------------

static void TestResetTracks() {
	static const uint8_t kFirst[] = {0x81, 0x00, 0x92, 60, 100};
	static const uint8_t kSecond[] = {0x05, 0x92, 62, 100};
	MakeEnv();
	MakeSequencer(kFirst);
	g_seq.track_count = 2;
	g_tracks[1].data = kSecond;

	// Dirty everything the rewind is supposed to clear.
	g_seq.volume_scale = 0.25f;
	g_seq.reset_scratch_2dc = 9;
	g_seq.fade_enabled = 1;
	g_seq.frame_counter_lo = 1234;
	g_seq.frame_counter_hi = 7;
	g_seq.base_ticks = 555;
	g_tracks[0].active = 0;
	g_tracks[1].active = 0;
	g_tracks[0].cursor = kFirst + 4;

	MidiSequencer_ResetTracks(&g_seq);

	CHECK(g_seq.volume_scale == 1.0f);
	CHECK(g_seq.reset_scratch_2dc == 0);
	// The second half of the cleared pair is the pump's fade enable.
	CHECK(g_seq.fade_enabled == 0);
	CHECK(g_seq.frame_counter_lo == 0);
	CHECK(g_seq.frame_counter_hi == 0);
	CHECK(g_seq.base_ticks == 0);

	// Each track is re-armed and its first delta is primed from the leading
	// variable-length quantity.
	CHECK(g_tracks[0].active == 1);
	CHECK(g_tracks[0].loop_start == kFirst);
	CHECK(g_tracks[0].cursor == kFirst + 2);
	CHECK(g_tracks[0].next_event_tick == 128);
	CHECK(g_tracks[1].active == 1);
	CHECK(g_tracks[1].loop_start == kSecond);
	CHECK(g_tracks[1].cursor == kSecond + 1);
	CHECK(g_tracks[1].next_event_tick == 5);
}

// ---------------------------------------------------------------------------
// Channel voice messages
// ---------------------------------------------------------------------------

static void TestNoteOnOffAndTranspose() {
	static const uint8_t kStream[] = {0x92, 60, 100, 0x00};
	MakeEnv();
	MidiTrack* track = MakeSequencer(kStream);
	g_seq.transpose = 2;
	MidiSequencer_DispatchEvent(&g_seq, track, &g_env);
	// Note 60 + transpose 2 = 62 -> byte 7, bit 6.
	CHECK(g_seq.channels[2].notes[7] == (uint8_t)(1u << 6));
	CHECK(g_seq.channels[0].notes[7] == 0);
	// The transposed note is what reaches the device.
	CHECK(g_message_count == 1);
	CHECK(g_messages[0] == (0x92u | (62u << 8) | (100u << 16)));
	CHECK(track->running_status == 0x92);

	static const uint8_t kOff[] = {0x82, 60, 0, 0x00};
	track->cursor = kOff;
	MidiSequencer_DispatchEvent(&g_seq, track, &g_env);
	CHECK(g_seq.channels[2].notes[7] == 0);
}

static void TestVelocityZeroIsNoteOff() {
	static const uint8_t kOn[] = {0x90, 64, 100, 0x00};
	static const uint8_t kZero[] = {0x90, 64, 0, 0x00};
	MakeEnv();
	MidiTrack* track = MakeSequencer(kOn);
	MidiSequencer_DispatchEvent(&g_seq, track, &g_env);
	CHECK(g_seq.channels[0].notes[8] == (uint8_t)(1u << 0));
	track->cursor = kZero;
	MidiSequencer_DispatchEvent(&g_seq, track, &g_env);
	// A 0x90 with velocity 0 clears the bit through the 0x80 path.
	CHECK(g_seq.channels[0].notes[8] == 0);
	CHECK(g_message_count == 2);
}

static void TestRunningStatus() {
	static const uint8_t kStream[] = {0x92, 60, 100, 0x00, 62, 100, 0x00};
	MakeEnv();
	MidiTrack* track = MakeSequencer(kStream);
	MidiSequencer_DispatchEvent(&g_seq, track, &g_env);
	// Second event omits the status byte and reuses the cached one.
	MidiSequencer_DispatchEvent(&g_seq, track, &g_env);
	CHECK(g_message_count == 2);
	CHECK(g_messages[1] == (0x92u | (62u << 8) | (100u << 16)));
	CHECK(track->cursor == kStream + sizeof(kStream));
}

static void TestProgramChangeTakesOneDataByte() {
	static const uint8_t kStream[] = {0xC3, 42, 0x00};
	MakeEnv();
	MidiTrack* track = MakeSequencer(kStream);
	MidiSequencer_DispatchEvent(&g_seq, track, &g_env);
	CHECK(g_seq.channels[3].program == 42);
	CHECK(g_message_count == 1);
	CHECK(g_messages[0] == (0xC3u | (42u << 8)));
	CHECK(track->cursor == kStream + sizeof(kStream));
}

static void TestControllerState() {
	static const uint8_t kStream[] = {0xB1, 0,    9, 0x00, 0xB1, 10,   64, 0x00,
	                                 0xB1, 0x5B, 7, 0x00, 0xB1, 0x5D, 5,  0x00};
	MakeEnv();
	MidiTrack* track = MakeSequencer(kStream);
	for (int index = 0; index < 4; ++index)
		MidiSequencer_DispatchEvent(&g_seq, track, &g_env);
	CHECK(g_seq.channels[1].bank == 9);
	CHECK(g_seq.channels[1].pan == 64);
	CHECK(g_seq.channels[1].cc_5b == 7);
	CHECK(g_seq.channels[1].cc_5d == 5);
	CHECK(g_message_count == 4);
}

static void TestVolumeScalingRewritesMessage() {
	static const uint8_t kStream[] = {0xB4, 7, 100, 0x00};
	MakeEnv();
	MidiTrack* track = MakeSequencer(kStream);
	g_cc_scale_return = 200; // above the MIDI range
	MidiSequencer_DispatchEvent(&g_seq, track, &g_env);
	CHECK(g_cc_scale_calls == 1);
	CHECK(g_cc_scale_input == 100);
	CHECK(g_seq.channels[4].volume_raw == 100);
	// Clamped to 0x7F, and the clamped value is what is sent.
	CHECK(g_seq.channels[4].volume_effective == 0x7F);
	CHECK(g_messages[0] == (0xB4u | (7u << 8) | (0x7Fu << 16)));

	// A negative scale zeroes both the state and the outgoing byte.
	MakeEnv();
	track = MakeSequencer(kStream);
	g_cc_scale_return = -1;
	MidiSequencer_DispatchEvent(&g_seq, track, &g_env);
	CHECK(g_seq.channels[4].volume_raw == 100);
	CHECK(g_seq.channels[4].volume_effective == 0);
	CHECK(g_messages[0] == (0xB4u | (7u << 8)));
}

static void TestLoopSnapshotAndRestore() {
	static const uint8_t kSave[] = {0xB0, 2, 0, 0x00};
	static const uint8_t kRestore[] = {0xB0, 4, 0, 0x00};
	MakeEnv();
	MidiTrack* track = MakeSequencer(kSave);
	g_seq.tempo = 500000;
	g_seq.frame_counter_lo = 11;
	g_seq.frame_counter_hi = 1;
	g_seq.base_ticks = 4242;
	track->next_event_tick = 77;
	MidiSequencer_DispatchEvent(&g_seq, track, &g_env);
	// The snapshot is taken inside the CC handler, before the trailing delta
	// time is consumed, so it points at the delta byte of the CC 2 event
	// itself and not at the following event.
	CHECK(track->loop_start == kSave + 3);
	CHECK(track->cursor == kSave + 4);
	CHECK(track->loop_next_event_tick == 77);
	CHECK(g_seq.loop_tempo == 500000);
	CHECK(g_seq.loop_counter_lo == 11);
	CHECK(g_seq.loop_counter_hi == 1);
	CHECK(g_seq.loop_base_ticks == 4242);

	// Move the clock and the cursor on, then loop back.
	track->cursor = kRestore;
	track->next_event_tick = 900;
	g_seq.tempo = 250000;
	g_seq.frame_counter_lo = 99;
	g_seq.frame_counter_hi = 7;
	g_seq.base_ticks = 1;
	MidiSequencer_DispatchEvent(&g_seq, track, &g_env);
	// The restore rewinds the cursor, and the delta read at the end of the
	// same event then consumes from the restored position.
	CHECK(track->cursor == kSave + 4);
	CHECK(track->next_event_tick == 77);
	CHECK(g_seq.tempo == 500000);
	CHECK(g_seq.frame_counter_lo == 11);
	CHECK(g_seq.frame_counter_hi == 1);
	CHECK(g_seq.base_ticks == 4242);
}

// ---------------------------------------------------------------------------
// Meta events
// ---------------------------------------------------------------------------

static void TestEndOfTrackRetires() {
	static const uint8_t kStream[] = {0xFF, 0x2F, 0x00};
	MakeEnv();
	MidiTrack* track = MakeSequencer(kStream);
	track->next_event_tick = 5;
	track->running_status = 0x92;
	MidiSequencer_DispatchEvent(&g_seq, track, &g_env);
	CHECK(track->active == 0);
	// Returns before the running-status store and the delta read.
	CHECK(track->running_status == 0x92);
	CHECK(track->next_event_tick == 5);
	CHECK(g_message_count == 0);
}

static void TestSetTempoRebasesClock() {
	static const uint8_t kStream[] = {0xFF, 0x51, 0x03, 0x07, 0xA1, 0x20, 0x00};
	MakeEnv();
	MidiTrack* track = MakeSequencer(kStream);
	g_seq.base_ticks = 5;
	g_seq.frame_counter_lo = 10;
	g_seq.frame_counter_hi = 0;
	// Elapsed at the old tempo: 1 * 10 * 1000 / 1000 == 10 ticks.
	CHECK(MidiSequencer_ElapsedTicks(&g_seq) == 10);
	MidiSequencer_DispatchEvent(&g_seq, track, &g_env);
	CHECK(g_seq.base_ticks == 15);
	CHECK(g_seq.frame_counter_lo == 0);
	CHECK(g_seq.frame_counter_hi == 0);
	// Retail accumulates with *0x101, not *0x100: a standard 0x07A120
	// (500000 us) payload lands on 503752 instead. Pinned deliberately so a
	// later "fix" to *0x100 shows up as a test failure.
	CHECK(g_seq.tempo == 503752);
	CHECK(track->cursor == kStream + sizeof(kStream));
}

static void TestUnknownMetaIsSkipped() {
	static const uint8_t kStream[] = {0xFF, 0x03, 0x04, 'n',
	                                 'a',  'm',  'e',  0x00};
	MakeEnv();
	MidiTrack* track = MakeSequencer(kStream);
	MidiSequencer_DispatchEvent(&g_seq, track, &g_env);
	CHECK(track->active == 1);
	CHECK(g_message_count == 0);
	CHECK(track->cursor == kStream + sizeof(kStream));
}

// ---------------------------------------------------------------------------
// System exclusive
// ---------------------------------------------------------------------------

static void TestSysExEmitsLongMessage() {
	static const uint8_t kStream[] = {0xF0, 0x03, 0x11, 0x22, 0x33, 0x00};
	MakeEnv();
	MidiTrack* track = MakeSequencer(kStream);
	MidiSequencer_DispatchEvent(&g_seq, track, &g_env);
	CHECK(g_header_alloc_count == 1);
	CHECK(g_buffer_alloc_count == 1);
	// The 0xF0 status is re-emitted, so the buffer is length + 1.
	CHECK(g_buffer_alloc_size == 4);
	MidiHeader* header = g_seq.sysex_headers[0];
	CHECK(header == &g_header_pool[0]);
	CHECK(header->buffer_length == 4);
	CHECK(header->flags == 0);
	CHECK(header->data[0] == 0xF0);
	CHECK(header->data[1] == 0x11);
	CHECK(header->data[2] == 0x22);
	CHECK(header->data[3] == 0x33);
	CHECK(g_prepare_calls == 1);
	CHECK(g_prepare_size == 0x40);
	CHECK(g_long_calls == 1);
	// A successful send keeps the header parked in the slot.
	CHECK(g_buffer_free_count == 0);
	CHECK(g_header_free_count == 0);
	// No short message for a system message.
	CHECK(g_message_count == 0);
	CHECK(g_seq.sysex_index == 1);
	CHECK(track->cursor == kStream + sizeof(kStream));
}

static void TestSysExFailureFreesAndClearsSlot() {
	static const uint8_t kStream[] = {0xF0, 0x01, 0x7E, 0x00};
	MakeEnv();
	MidiTrack* track = MakeSequencer(kStream);
	g_prepare_result = 1; // midiOutPrepareHeader fails
	MidiSequencer_DispatchEvent(&g_seq, track, &g_env);
	CHECK(g_prepare_calls == 1);
	// Short-circuit: the long message is never attempted.
	CHECK(g_long_calls == 0);
	CHECK(g_buffer_free_count == 1);
	CHECK(g_header_free_count == 1);
	CHECK(g_seq.sysex_headers[0] == 0);
	CHECK(g_seq.sysex_index == 1);
}

static void TestSysExReleasesOccupiedSlotAndWraps() {
	static const uint8_t kStream[] = {0xF0, 0x01, 0x7E, 0x00};
	MakeEnv();
	MidiTrack* track = MakeSequencer(kStream);
	g_seq.sysex_index = 31;
	g_seq.sysex_headers[31] = &g_header_pool[3]; // slot already in use
	MidiSequencer_DispatchEvent(&g_seq, track, &g_env);
	CHECK(g_release_sysex_calls == 1);
	CHECK(g_release_sysex_slot == 31);
	// Round-robin wraps back to 0 after slot 31.
	CHECK(g_seq.sysex_index == 0);
}

// ---------------------------------------------------------------------------
// Delta times
// ---------------------------------------------------------------------------

static void TestMultiByteDeltaTime() {
	static const uint8_t kStream[] = {0x92, 60, 100, 0x81, 0x00};
	MakeEnv();
	MidiTrack* track = MakeSequencer(kStream);
	track->next_event_tick = 10;
	MidiSequencer_DispatchEvent(&g_seq, track, &g_env);
	// 0x81 0x00 == 128, accumulated onto the existing position.
	CHECK(track->next_event_tick == 138);
	CHECK(track->cursor == kStream + sizeof(kStream));
}

// ---------------------------------------------------------------------------
// 0x0043AF30 pump
// ---------------------------------------------------------------------------

static void TestClockFormula() {
	static const uint8_t kStream[] = {0xFF, 0x2F, 0x00};
	MakeEnv();
	MakeSequencer(kStream);
	g_seq.tick_scale = 3;
	g_seq.tempo = 500;
	g_seq.base_ticks = 7;
	g_seq.frame_counter_lo = 200;
	// 3 * 200 * 1000 / 500 == 1200 ticks past the base.
	CHECK(MidiSequencer_ElapsedTicks(&g_seq) == 1200);
	CHECK(MidiSequencer_CurrentTick(&g_seq) == 1207);
}

static void TestPumpDrainsDueEvents() {
	static const uint8_t kStream[] = {0x92, 60,   100,  0x00, 0x92, 62,
	                                 100,  0x00, 0xFF, 0x2F, 0x00};
	MakeEnv();
	MidiTrack* track = MakeSequencer(kStream);
	MidiSequencer_Pump(&g_seq, &g_env);
	// Both zero-delta events fire in one step, then end-of-track stops the
	// re-dispatch loop.
	CHECK(g_message_count == 2);
	CHECK(track->active == 0);
	// The track was occupied on entry, so this step does not rewind.
	CHECK(g_seq.frame_counter_lo == 1);
}

static void TestPumpWaitsForDueTime() {
	// A nonzero delta is required: a zero-delta event on a track that stays
	// active re-arms itself at the same tick and the pump would dispatch it
	// again in the same step, which is why real streams always terminate a
	// track with meta 0x2F.
	static const uint8_t kStream[] = {0x92, 60, 100, 0x02};
	MakeEnv();
	MidiTrack* track = MakeSequencer(kStream);
	track->next_event_tick = 5;
	MidiSequencer_Pump(&g_seq, &g_env);
	CHECK(g_message_count == 0);
	// An occupied but not-yet-due track is left alone, not rewound.
	CHECK(track->active == 1);
	CHECK(track->cursor == kStream);

	// Wind the clock past the due time; the event then fires.
	g_seq.frame_counter_lo = 5;
	MidiSequencer_Pump(&g_seq, &g_env);
	CHECK(g_message_count == 1);
	CHECK(track->next_event_tick == 7);
}

static void TestPumpRewindsWhenAllTracksFinish() {
	// A track chunk starts with a delta time, which the rewind primes.
	static const uint8_t kStream[] = {0x00, 0x92, 60, 100, 0x02};
	MakeEnv();
	MidiTrack* track = MakeSequencer(kStream);
	track->active = 0; // every track has hit its end-of-track marker
	g_seq.frame_counter_lo = 7;
	g_seq.base_ticks = 3;
	g_seq.volume_scale = 0.25f;
	MidiSequencer_Pump(&g_seq, &g_env);
	// The pump rewinds through 0x0043ACE0, which is what makes playback loop.
	CHECK(track->active == 1);
	CHECK(track->cursor == kStream + 1);
	CHECK(track->loop_start == kStream);
	CHECK(track->next_event_tick == 0);
	CHECK(g_seq.volume_scale == 1.0f);
	// The rewind runs after the counter advance and zeroes the clock again.
	CHECK(g_seq.frame_counter_lo == 0);
	CHECK(g_seq.base_ticks == 0);
	CHECK(g_message_count == 0);
}

static void TestPumpCounterCarry() {
	static const uint8_t kStream[] = {0x92, 60, 100, 0x00};
	MakeEnv();
	MidiTrack* track = MakeSequencer(kStream);
	FreezeClock(track);
	g_seq.frame_counter_lo = 0xFFFFFFFEu;
	g_seq.frame_counter_hi = 5;
	MidiSequencer_Pump(&g_seq, &g_env);
	CHECK(g_seq.frame_counter_lo == 0xFFFFFFFFu);
	CHECK(g_seq.frame_counter_hi == 5);
	MidiSequencer_Pump(&g_seq, &g_env);
	// The 64-bit counter carries into the high dword on wrap.
	CHECK(g_seq.frame_counter_lo == 0u);
	CHECK(g_seq.frame_counter_hi == 6);
	CHECK(g_message_count == 0);
}

static void TestPumpFadeRamp() {
	static const uint8_t kStream[] = {0x92, 60, 100, 0x00};
	MakeEnv();
	MidiTrack* track = MakeSequencer(kStream);
	FreezeClock(track);
	g_seq.fade_enabled = 1;
	g_seq.fade_total = 4;
	g_seq.fade_current = 1;
	g_seq.volume_cached = 0;
	MidiSequencer_Pump(&g_seq, &g_env);
	// level = 1 - 1/4
	CHECK(g_seq.volume_scale == 0.75f);
	CHECK(g_fade_scale_input == 0.75f);
	CHECK(g_apply_volume_calls == 1);
	CHECK(g_seq.volume_cached == (int32_t)(0.75f * 127.0f));
	CHECK(g_seq.fade_current == 2);
	// Retail converts the level twice per step.
	CHECK(g_fade_scale_calls == 2);

	// An unchanged integer level does not touch the device.
	MakeEnv();
	g_seq.fade_current = 2;
	g_seq.volume_cached = (int32_t)(0.5f * 127.0f);
	MidiSequencer_Pump(&g_seq, &g_env);
	CHECK(g_seq.volume_scale == 0.5f);
	CHECK(g_apply_volume_calls == 0);
	CHECK(g_seq.fade_current == 3);

	// Ramp complete: level cleared, and the step returns before the track
	// walk, the counter advance and the rewind check.
	MakeEnv();
	g_seq.fade_current = 4;
	g_seq.fade_total = 4;
	g_seq.frame_counter_lo = 20;
	MidiSequencer_Pump(&g_seq, &g_env);
	CHECK(g_seq.volume_scale == 0.0f);
	CHECK(g_seq.frame_counter_lo == 20);
	CHECK(g_message_count == 0);
}

int main() {
	TestReadVariableLength();
	TestResetTracks();
	TestNoteOnOffAndTranspose();
	TestVelocityZeroIsNoteOff();
	TestRunningStatus();
	TestProgramChangeTakesOneDataByte();
	TestControllerState();
	TestVolumeScalingRewritesMessage();
	TestLoopSnapshotAndRestore();
	TestEndOfTrackRetires();
	TestSetTempoRebasesClock();
	TestUnknownMetaIsSkipped();
	TestSysExEmitsLongMessage();
	TestSysExFailureFreesAndClearsSlot();
	TestSysExReleasesOccupiedSlotAndWraps();
	TestMultiByteDeltaTime();
	TestClockFormula();
	TestPumpDrainsDueEvents();
	TestPumpWaitsForDueTime();
	TestPumpRewindsWhenAllTracksFinish();
	TestPumpCounterCarry();
	TestPumpFadeRamp();

	if (g_failures != 0) {
		std::printf("%d check(s) failed\n", g_failures);
		return 1;
	}
	std::printf("midi_sequencer_test passed\n");
	return 0;
}
