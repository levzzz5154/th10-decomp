// =============================================================================
// sound_commands.cpp - Sound worker command queue, BGM control, streamer
// =============================================================================
#include "th10/platform/sound_commands.hpp"

namespace {

void PopCommand(SoundWorkerState* state) {
    for (int index = 1; index < state->queue_length; ++index)
        state->queue[index - 1] = state->queue[index];
    state->queue_length -= 1;
}

} // namespace

// 0x0043DDF0 - SoundWorker_DrainCommands: execute the head of the command
// queue (retail entries are 0x43 dwords at ctx+0x7E2, up to 0x1F pending).
// Returns the code of the command left at the head (0 when idle), which the
// boot/teardown paths poll until the queue reports empty.
int SoundWorker_DrainCommands(SoundWorkerState* state,
                              const SoundWorkerHooks* hooks) {
    if (state->initialized == 0)
        return 0;

    while (state->queue_length > 0) {
        SoundCommand* command = &state->queue[0];
        switch (command->code) {
        case 1: // BGM preload: file path needs the MIDI worker stopped first
            if (state->stream_from_archive == 0 && command->phase == 0) {
                hooks->stop_midi(hooks->context);
                command->phase = 1;
                return command->code;
            }
            hooks->preload_track(hooks->context, command->argument);
            break;
        case 2: // BGM play state machine
            if (command->phase == 0) {
                hooks->stop_stream(hooks->context);
                command->phase = 1;
                return command->code;
            }
            hooks->start_stream(hooks->context, command->argument);
            state->active_track = command->argument;
            break;
        case 3: // stop
            hooks->stop_stream(hooks->context);
            break;
        case 4: // shutdown sequence, one step per drain call
            switch (command->phase) {
            case 0: hooks->stop_stream(hooks->context); break;
            case 1: hooks->post_worker_quit(hooks->context); break;
            case 2:
                if (hooks->join_worker(hooks->context) != 0)
                    return command->code; // retry until the thread exits
                break;
            default:
                hooks->close_worker_handles(hooks->context);
                state->initialized = 0;
                PopCommand(state);
                return 0;
            }
            command->phase += 1;
            return command->code;
        case 5:
            hooks->apply_master_volume(hooks->context);
            break;
        case 6:
            if (state->bgm_enabled != 0)
                hooks->pause_stream(hooks->context);
            break;
        case 7:
            if (state->bgm_enabled != 0)
                hooks->resume_stream(hooks->context);
            break;
        case 8:
            hooks->flush_stream(hooks->context);
            break;
        default:
            break;
        }
        PopCommand(state);
    }

    // SFX flush: restart every queued effect buffer (12 retail slots).
    if (state->sfx_enabled != 0)
        for (int slot = 0; slot < SOUND_SFX_SLOT_COUNT; ++slot)
            if (hooks->effect_pending(hooks->context, slot) != 0)
                hooks->play_effect(hooks->context, slot);
    return state->queue_length > 0 ? state->queue[0].code : 0;
}

// 0x0043D120 - SoundManager_Shutdown: release every DirectSound object the
// manager owns, stop the MIDI worker, and destroy the streamer.
void SoundManager_Shutdown(int has_update_timer,
                           const SoundShutdownHooks* hooks) {
    hooks->release_track_table(hooks->context);
    for (int slot = 0; slot < 0x80; ++slot)
        hooks->release_buffer(hooks->context, slot);
    hooks->release_bgm_headers(hooks->context);
    if (has_update_timer != 0) {
        hooks->kill_update_timer(hooks->context);
        hooks->stop_midi(hooks->context);
        hooks->release_direct_sound(hooks->context);
    }
    hooks->destroy_streamer(hooks->context);
    hooks->release_notify_event(hooks->context);
    hooks->release_name_slots(hooks->context);
}

// 0x0043A910 - MidiPlayer_Shutdown: destructor body for the MIDI player.
// Stops playback, frees the 0x20 track blocks, closes the midiOut handle,
// then kills the timer callback and ends both timer periods.
void MidiPlayer_Shutdown(const MidiShutdownHooks* hooks) {
    hooks->stop_playback(hooks->context);
    hooks->reset_queues(hooks->context);
    hooks->release_track_blocks(hooks->context);
    hooks->close_midi_out(hooks->context);
    hooks->kill_timer_event(hooks->context);
    hooks->end_time_period(hooks->context);
}

// 0x0044CBF0 - Streamer_Create: build the double-buffered streaming object.
// Creates the DirectSound buffer, attaches notification positions every
// `notify_stride` bytes (retail 0x10 marks), and primes the format copy.
int Streamer_Create(unsigned int notify_count, unsigned int notify_stride,
                    const StreamerFormat* format, const StreamerHooks* hooks) {
    if (format == 0 || format->block_align == 0)
        return -1;
    if (hooks->create_sound_buffer(hooks->context, 0) != 0)
        return -0x7FFB; // retail 0x80004005 route
    unsigned int* offsets = static_cast<unsigned int*>(
        hooks->alloc(hooks->context, notify_count * 2u * 4u));
    if (offsets == 0)
        return -0x7FF2; // retail 0x8007000E route
    for (unsigned int index = 0; index < notify_count; ++index) {
        offsets[index * 2 + 0] = (index + 1u) * notify_stride - 1u;
        offsets[index * 2 + 1] = 0; // event slot, bound by the host layer
    }
    int status = hooks->set_notification_positions(
        hooks->context, static_cast<int>(notify_count), offsets);
    hooks->release(hooks->context, offsets);
    return status == 0 ? 0 : -0x7FFB;
}

// 0x0044CF20 - Streamer_RebuildBuffers: drop and recreate the buffer array
// with fresh notification marks (retail rebuilds all 0x10 positions).
int Streamer_RebuildBuffers(int buffer_count, unsigned int notify_stride,
                            unsigned int notify_tail,
                            const StreamerHooks* hooks) {
    for (int index = 0; index < buffer_count; ++index)
        hooks->release_sound_buffer(hooks->context, index);
    for (int index = 0; index < buffer_count; ++index)
        if (hooks->create_sound_buffer(hooks->context, index) != 0)
            return -0x7FFB;
    unsigned int* offsets = static_cast<unsigned int*>(
        hooks->alloc(hooks->context, 0x80));
    if (offsets == 0)
        return -0x7FF2;
    for (unsigned int index = 0; index < 0x10; ++index) {
        offsets[index * 2 + 0] = (index + 1u) * notify_stride - 1u;
        offsets[index * 2 + 1] = notify_tail;
    }
    int status = hooks->set_notification_positions(hooks->context, 0x10,
                                                   offsets);
    hooks->release(hooks->context, offsets);
    return status == 0 ? 0 : -0x7FFB;
}

// 0x0044D110 - Streamer_FillBuffer: lock the playback buffer, pull PCM from
// the reader until the lock is satisfied, and pad any shortfall with silence
// (0x80 for 8-bit samples, 0 for 16-bit).
int Streamer_FillBuffer(unsigned int bytes, const StreamerFormat* format,
                        const StreamerHooks* hooks) {
    if (hooks->restore_buffer(hooks->context) != 0)
        return -1;
    unsigned char* pcm = 0;
    unsigned int locked = 0;
    if (hooks->lock_buffer(hooks->context, bytes, &pcm, &locked) != 0)
        return -1;
    unsigned int filled = 0;
    while (filled < locked) {
        unsigned int got = hooks->read_pcm(hooks->context, pcm + filled,
                                           locked - filled);
        if (got == 0) {
            if (hooks->advance_reader_block(hooks->context) != 0)
                break; // no more source data: pad below
            continue;
        }
        filled += got;
    }
    unsigned char silence =
        format->bits_per_sample == 8 ? 0x80 : 0x00;
    for (unsigned int index = filled; index < locked; ++index)
        pcm[index] = silence;
    hooks->unlock_buffer(hooks->context);
    return 0;
}

// 0x0044DAD0 - Streamer_Restart: rewind the reader to the start of the PCM
// data, optionally refill the front buffer, and park the play cursor at 0.
int Streamer_Restart(int refill, unsigned int bytes,
                     const StreamerFormat* format,
                     const StreamerHooks* hooks) {
    int status = hooks->prime_buffer_chain(hooks->context);
    if (refill != 0) {
        hooks->seek_reader_to_data(hooks->context);
        Streamer_FillBuffer(bytes, format, hooks);
    }
    hooks->rewind_buffer(hooks->context);
    return status;
}

// 0x0043D950 - Bgm_StartStream: start one BGM track. Preloaded (archive)
// tracks route to the wave player; file streaming builds the notify event,
// worker thread, and streamer sized to the format's data block.
int Bgm_StartStream(int track, int initialized, int bgm_enabled,
                    int stream_from_file, const BgmStartHooks* hooks) {
    if (initialized == 0 || bgm_enabled == 0)
        return -1;
    if (stream_from_file == 0)
        return hooks->play_preloaded(hooks->context, track);
    if (hooks->track_loaded(hooks->context, track) == 0)
        return -1;
    const StreamerFormat* format = hooks->track_format(hooks->context, track);
    if (format == 0 || format->block_align == 0)
        return -1;
    unsigned int bytes = ((format->data_bytes * format->block_align) &
                          0x3FFFFFFFu) >> 2;
    bytes -= bytes % format->block_align;
    if (hooks->create_notify_event(hooks->context) != 0 ||
        hooks->spawn_worker_thread(hooks->context) != 0)
        return -1;
    return hooks->create_streamer(hooks->context, track, bytes) >= 0 ? 0 : -1;
}

// 0x0043D7D0 - Bgm_PreloadTrack: cache one BGM file into its slot. Skips
// work when the slot already holds the same name; the file-streaming path
// re-reads header + data from the open archive handle.
int Bgm_PreloadTrack(const char* name, int slot, int stream_from_file,
                     int archive_open, const BgmPreloadHooks* hooks) {
    if (hooks->slot_matches(hooks->context, slot, name) != 0)
        return 0;
    hooks->store_name(hooks->context, slot, name);
    if (stream_from_file != 0 && archive_open != 0) {
        hooks->release_old(hooks->context, slot);
        if (hooks->open_archive(hooks->context) == 0)
            return -1;
        int track_index = hooks->locate_track(hooks->context, name);
        if (track_index < 0)
            return -1;
        if (hooks->read_header_and_data(hooks->context, slot,
                                        track_index) != 0)
            return -1;
    }
    return 0;
}
