#include "th10/platform/midi_worker.hpp"
#include "th10/game/registered_clock.hpp"
#include "th10/util/scalars.hpp"

#include <cmath>
#include <cstring>

namespace {



} // namespace

// 0x0043E3A0 - MIDI worker message pump. The loop blocks on the worker
// event and the thread message queue (retail MsgWaitForMultipleObjects on
// one handle, mask 0xBF). A cleared worker slot ends the loop. Wait result
// 0 services a streaming worker under the busy latch (+0x74); wait result 1
// drains the queue with PeekMessage and ends the loop when a WM_QUIT-class
// message (0x12) arrives.
int MidiWorker_MessageLoop(MidiWorker** worker_slot,
                           unsigned int (*wait)(void),
                           int (*peek_message)(unsigned int* message_out),
                           void (*service)(MidiWorker* worker)) {
    int done = 0;
    do {
        unsigned int signaled = wait();
        if (*worker_slot == 0) done = 1;
        if (signaled == 0) {
            MidiWorker* worker = *worker_slot;
            if (worker != 0 && worker->streaming != 0) {
                worker->busy = 1;
                service(worker);
                worker->busy = 0;
            }
        } else if (signaled == 1) {
            unsigned int message = 0;
            while (peek_message(&message) != 0) {
                if (message == 0x12) done = 1;
            }
        }
    } while (done == 0);
    return 0;
}

// 0x0043B7A0 - midi channel volume refresh: skipped in stream mode;
// otherwise sends a controller-7 (channel volume) short message per channel
// with the base volume plus delta clamped to 0..127.
void MidiOutput_ApplyChannelVolumes(MidiOutput* midi, int delta,
                                    MidiEnv* env) {
	if (midi->stream_mode != 0) return;
	for (int channel = 0; channel < 0x10; ++channel) {
		int volume = env->read_base_volume(channel) + delta;
		if (volume < 0) {
			volume = 0;
		} else if (0x7F < volume) {
			volume = 0x7F;
		}
		if (midi->handle != 0) {
			Word message = (Word)((volume << 16) | 0x0700 |
			                                  (0xB0 + channel));
			env->send_short_message(midi->handle, message);
		}
	}
}
