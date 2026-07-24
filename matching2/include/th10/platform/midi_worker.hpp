#pragma once

// MIDI worker message pump and channel volume application (retail 0x0043E3A0, 0x0043B7A0).
#include "th10/util/scalars.hpp"

// MIDI worker fields the message loop reads (retail worker +0x30/+0x74).
struct MidiWorker {
    int streaming;
    int busy;
};

int MidiWorker_MessageLoop(MidiWorker** worker_slot,
                           unsigned int (*wait)(void),
                           int (*peek_message)(unsigned int* message_out),
                           void (*service)(MidiWorker* worker));

struct MidiOutput {
	int stream_mode; // +0x2d4, nonzero means streamed BGM owns the volume
	void* handle;    // +0x13c midiOut handle, may be null
};

struct MidiEnv {
	int (*read_base_volume)(int channel);
	void (*send_short_message)(void* handle, Word message);
};

void MidiOutput_ApplyChannelVolumes(MidiOutput* midi, int delta,
                                    MidiEnv* env);
