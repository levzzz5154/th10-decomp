// =============================================================================
// sound_commands.hpp - Sound worker command queue and BGM streamer surfaces
// Retail functions: 0x0043DDF0, 0x0043D950, 0x0043D7D0, 0x0043D120,
//                   0x0043A910, 0x0044CBF0, 0x0044CF20, 0x0044D110, 0x0044DAD0
// =============================================================================
#ifndef TH10_PLATFORM_SOUND_COMMANDS_HPP
#define TH10_PLATFORM_SOUND_COMMANDS_HPP

// One queued command (retail stride 0x43 dwords at ctx+0x7E2).
struct SoundCommand {
    int code;        // 1 load, 2 play, 3 stop, 4 shutdown, 5 volume,
                     // 6 pause, 7 resume, 8 flush
    int argument;    // track index / slot
    int phase;       // multi-step commands store their step here
};

enum SoundCommandLimits {
    SOUND_COMMAND_QUEUE_CAPACITY = 0x1F,
    SOUND_SFX_SLOT_COUNT = 12,
    SOUND_BGM_SLOT_COUNT = 0x10,
};

struct SoundWorkerState {
    int initialized;                     // ctx[0x184]
    int active_track;                    // ctx[0x7E0]
    int stream_from_archive;             // !(DAT_00491D78 & 0x10)
    int bgm_enabled;                     // DAT_00491D63
    int sfx_enabled;                     // DAT_00491D64
    int queue_length;
    SoundCommand queue[SOUND_COMMAND_QUEUE_CAPACITY];
};

struct SoundWorkerHooks {
    void* context;
    int (*preload_track)(void* context, int slot);        // 0x0043D7D0
    void (*stop_midi)(void* context);                      // 0x0043DAB0
    int (*start_stream)(void* context, int track);        // 0x0043D950
    int (*stop_stream)(void* context);                     // 0x0044D550
    int (*post_worker_quit)(void* context);                // PostThreadMessage
    int (*join_worker)(void* context);                     // WaitForSingleObject
    void (*close_worker_handles)(void* context);
    void (*apply_master_volume)(void* context);            // command 5
    void (*pause_stream)(void* context);                   // 0x0044D5B0
    void (*resume_stream)(void* context);                  // 0x0044D5D0
    void (*flush_stream)(void* context);                   // 0x0044D4E0
    void (*play_effect)(void* context, int slot);
    int (*effect_pending)(void* context, int slot);
};

int SoundWorker_DrainCommands(SoundWorkerState* state,
                              const SoundWorkerHooks* hooks);

struct SoundShutdownHooks {
    void* context;
    void (*release_buffer)(void* context, int slot);   // COM Release (+0x8)
    void (*release_track_table)(void* context);        // free(ctx[0x7E1])
    void (*release_bgm_headers)(void* context);        // 0x25 header frees
    void (*kill_update_timer)(void* context);          // KillTimer(.., 1)
    void (*stop_midi)(void* context);                  // 0x0043DAB0
    void (*release_direct_sound)(void* context);       // ctx[0x182] chain
    void (*destroy_streamer)(void* context);           // ctx[0x1482] vtable
    void (*release_notify_event)(void* context);       // ctx[0x184] inner
    void (*release_name_slots)(void* context);         // 0x10 name frees
};

void SoundManager_Shutdown(int has_update_timer,
                           const SoundShutdownHooks* hooks);

struct MidiShutdownHooks {
    void* context;
    void (*stop_playback)(void* context);      // 0x0043AE20
    void (*reset_queues)(void* context);        // 0x0043AA60
    void (*release_track_blocks)(void* context);// obj[0x26..0x45] frees
    void (*close_midi_out)(void* context);      // midiOutReset + Close
    void (*kill_timer_event)(void* context);    // timeKillEvent(obj[1])
    void (*end_time_period)(void* context);     // timeEndPeriod x2
};

void MidiPlayer_Shutdown(const MidiShutdownHooks* hooks);

// --- BGM streamer -----------------------------------------------------------

struct StreamerFormat {
    unsigned int data_bytes;      // dword(fmt+0x24)
    unsigned int block_align;     // ushort(fmt+0x2C)
    unsigned int bits_per_sample; // ushort(fmt+0x2E)
};

struct StreamerHooks {
    void* context;
    int (*create_sound_buffer)(void* context, int index);   // dsound +0xC
    void (*release_sound_buffer)(void* context, int index); // buffer +0x8
    int (*set_notification_positions)(void* context, int count,
                                      const unsigned int* offsets);
    void* (*alloc)(void* context, unsigned int size);
    void (*release)(void* context, void* memory);
    void (*seek_reader_to_data)(void* context);   // SetFilePointer path
    unsigned int (*read_pcm)(void* context, unsigned char* out,
                             unsigned int bytes);
    int (*advance_reader_block)(void* context);   // 0x0044DD40
    int (*lock_buffer)(void* context, unsigned int bytes,
                       unsigned char** pcm_out, unsigned int* size_out);
    void (*unlock_buffer)(void* context);
    void (*rewind_buffer)(void* context);          // SetCurrentPosition(0)
    int (*restore_buffer)(void* context);          // Restore (+0x24)
    int (*prime_buffer_chain)(void* context);      // 0x0044D300
};

int Streamer_Create(unsigned int notify_count, unsigned int notify_stride,
                    const StreamerFormat* format, const StreamerHooks* hooks);
int Streamer_RebuildBuffers(int buffer_count, unsigned int notify_stride,
                            unsigned int notify_tail,
                            const StreamerHooks* hooks);
int Streamer_FillBuffer(unsigned int bytes, const StreamerFormat* format,
                        const StreamerHooks* hooks);
int Streamer_Restart(int refill, unsigned int bytes,
                     const StreamerFormat* format,
                     const StreamerHooks* hooks);

// --- BGM control ------------------------------------------------------------

struct BgmStartHooks {
    void* context;
    int (*play_preloaded)(void* context, int track);   // 0x0043D790 path
    int (*track_loaded)(void* context, int track);     // ctx[track+0x7B0]
    const StreamerFormat* (*track_format)(void* context, int track);
    int (*create_notify_event)(void* context);
    int (*spawn_worker_thread)(void* context);         // 0x0043E3A0 proc
    int (*create_streamer)(void* context, int track,
                           unsigned int buffer_bytes); // 0x0044CBF0
};

int Bgm_StartStream(int track, int initialized, int bgm_enabled,
                    int stream_from_file, const BgmStartHooks* hooks);

struct BgmPreloadHooks {
    void* context;
    int (*slot_matches)(void* context, int slot, const char* name);
    void (*store_name)(void* context, int slot, const char* name);
    void (*release_old)(void* context, int slot);
    int (*open_archive)(void* context);              // CreateFileA path
    int (*locate_track)(void* context, const char* name); // 0x0043D2A0
    int (*read_header_and_data)(void* context, int slot, int track_index);
};

int Bgm_PreloadTrack(const char* name, int slot, int stream_from_file,
                     int archive_open, const BgmPreloadHooks* hooks);

#endif // TH10_PLATFORM_SOUND_COMMANDS_HPP
