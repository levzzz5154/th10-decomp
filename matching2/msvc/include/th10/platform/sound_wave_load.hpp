#pragma once
#include <stddef.h>

struct WaveSecondaryBuffer;
struct WaveDirectSoundDevice;
struct SoundStream;
struct MusicReadCursor;
struct WaveNotification;

#pragma pack(push, 2)
struct WaveFormatImage {
    unsigned short tag;
    unsigned short channels;
    unsigned int sample_rate;
    unsigned int average_bytes_per_second;
    unsigned short block_alignment;
    unsigned short bits_per_sample;
    unsigned short extra_bytes;
};
#pragma pack(pop)

struct MusicTrackRecord {
    char name[16];
    unsigned int file_offset;                       // +0x10
    unsigned int data_bytes;                        // +0x14
    int loop_start;
    int loop_end;
    WaveFormatImage format;                         // +0x20
};

struct WaveBufferDescription {
    unsigned int size;
    unsigned int flags;
    unsigned int bytes;
    unsigned int reserved;
    const WaveFormatImage* format;
    unsigned char algorithm[16];
};

struct WaveBufferMethods {
    int (__stdcall* query_interface)(WaveSecondaryBuffer*, const void* iid, WaveNotification** output);
    void* add_reference;
    unsigned int (__stdcall* release)(WaveSecondaryBuffer*);
    void* get_caps;
    int (__stdcall* get_position)(WaveSecondaryBuffer*, unsigned int* play, unsigned int* write);
    void* before_status[4];
    int (__stdcall* get_status)(WaveSecondaryBuffer*, unsigned int* status);
    void* initialize;
    int (__stdcall* lock)(WaveSecondaryBuffer*, unsigned int offset,
        unsigned int bytes, unsigned char** first, unsigned int* first_bytes,
        unsigned char** second, unsigned int* second_bytes, unsigned int flags);
    int (__stdcall* play)(WaveSecondaryBuffer*, unsigned int reserved,
        unsigned int priority, unsigned int flags);
    int (__stdcall* set_position)(WaveSecondaryBuffer*, unsigned int position);
    int (__stdcall* set_format)(WaveSecondaryBuffer*, const WaveFormatImage*);
    int (__stdcall* set_volume)(WaveSecondaryBuffer*, int volume);
    int (__stdcall* set_pan)(WaveSecondaryBuffer*, int pan);
    void* set_frequency;
    int (__stdcall* stop)(WaveSecondaryBuffer*);
    int (__stdcall* unlock)(WaveSecondaryBuffer*, unsigned char* first,
        unsigned int first_bytes, unsigned char* second, unsigned int second_bytes);
    int (__stdcall* restore)(WaveSecondaryBuffer*);
};

struct WaveSecondaryBuffer {
    WaveBufferMethods* methods;
    int RestoreIfLost(unsigned int* restored);       // maintained 0x0044D300
};
struct WaveNotificationPosition {
    unsigned int offset;
    void* event;
};
struct WaveNotificationMethods {
    void* query_interface;
    void* add_reference;
    unsigned int (__stdcall* release)(WaveNotification*);
    int (__stdcall* set_positions)(WaveNotification*, unsigned int count, const WaveNotificationPosition*);
};
struct WaveNotification { WaveNotificationMethods* methods; };
struct WaveDeviceMethods {
    void* query_interface;
    void* add_reference;
    unsigned int (__stdcall* release)(WaveDirectSoundDevice*);
    int (__stdcall* create_buffer)(WaveDirectSoundDevice*,
        const WaveBufferDescription*, WaveSecondaryBuffer** output, void* outer);
    void* get_caps;
    int (__stdcall* duplicate_buffer)(WaveDirectSoundDevice*, WaveSecondaryBuffer*, WaveSecondaryBuffer**);
    int (__stdcall* set_cooperative_level)(WaveDirectSoundDevice*, void* window, unsigned int level);
};
struct WaveDirectSoundDevice { WaveDeviceMethods* methods; };

struct SoundStreamMethods {
    void* destroy;
};

struct MusicReadCursor {
    void* methods;
    unsigned int unknown_04;
    volatile unsigned int file_remaining;           // +0x08
    unsigned char unknown_0c[0x2c - 0x0c];
    unsigned int total_pcm_bytes;                    // +0x2c
    unsigned char unknown_30[0x78 - 0x30];
    volatile unsigned int open_mode;                 // +0x78
    volatile unsigned int buffered;                 // +0x7c
    unsigned char* volatile buffer_begin;           // +0x80
    unsigned char* volatile position;               // +0x84
    volatile unsigned int memory_end;               // +0x88, relative to begin
    void* volatile file;                            // +0x8c
    MusicTrackRecord* volatile record;              // +0x90

    int SelectRecord(MusicTrackRecord*);             // maintained 0x0044DCA0
};

struct SoundStream {
    // Common prefix; the streaming subclass continues beyond +0x30.
    SoundStreamMethods* methods;
    WaveSecondaryBuffer** buffers;                  // +0x04
    unsigned int buffer_bytes;                      // +0x08
    MusicReadCursor* reader;                        // +0x0c
    unsigned int buffer_count;                      // +0x10
    int fade_remaining;                             // +0x14
    int fade_duration;                              // +0x18
    unsigned int fade_mode;                         // +0x1c
    unsigned int play_priority;                     // +0x20
    unsigned int play_flags;                        // +0x24
    unsigned int unknown_28;
    unsigned int unknown_2c;
    unsigned int playing;                           // +0x30

    WaveSecondaryBuffer* FindAvailable();            // maintained 0x0044D370
    int RewindBuffers();                            // maintained 0x0044D600
    int SetVolume(int volume);                      // maintained 0x0044D4E0
    int StopAndRewind();                            // maintained 0x0044D550
    int ResumeConfigured();                         // maintained 0x0044D5D0
};

struct SoundStreamingState : SoundStream {
    WaveBufferDescription description;               // +0x34
    WaveDirectSoundDevice** device_owner;             // +0x58
    unsigned int last_play_position;                // +0x5c
    unsigned int played_bytes;                      // +0x60
    unsigned int write_offset;                      // +0x64
    unsigned int end_of_stream;                     // +0x68
    unsigned int segment_bytes;                     // +0x6c
    void* notification_event;                        // +0x70
    volatile unsigned int servicing;                 // +0x74
};

struct MusicCommand {
    volatile unsigned int kind;
    volatile int argument;
    volatile unsigned int step;
    char name[256];
};

struct WaveSoundManager {
    WaveDirectSoundDevice* device;                  // +0x0000
    unsigned int unknown_0004;
    WaveSecondaryBuffer* secondary_buffers[256];   // +0x0008
    int sound_handles[128];                        // +0x0408
    WaveSecondaryBuffer* stream_buffer;             // +0x0608
    void* window;                                  // +0x060c
    WaveDirectSoundDevice** device_owner;            // +0x0610
    unsigned int music_thread_id;                    // +0x0614
    union {
        unsigned int stream_cursor;                 // +0x0618 in stream mode
        void* music_thread;                          // +0x0618 in music-worker mode
    };
    unsigned int unknown_061c;
    union {
        int music_handles[12];                      // historical name
        int pending_sound_indices[12];              // +0x0620
    };
    volatile int pending_pan_count[12];              // +0x0650
    int pending_pan[12][128];                        // +0x0680
    MusicTrackRecord* cached_music_records[16];     // +0x1e80
    unsigned char* cached_music_data[16];           // +0x1ec0
    unsigned char* music_read_cursors[16];          // +0x1f00
    unsigned int music_remaining_bytes[16];         // +0x1f40
    unsigned int selected_music_slot;               // +0x1f80
    unsigned char* loaded_music_data;               // +0x1f84
    MusicCommand music_commands[32];                 // +0x1f88
    char cached_music_names[16][256];               // +0x4108
    char music_file_name[256];                      // +0x5108
    SoundStream* music_stream;                     // +0x5208
    void* music_worker_event;                     // +0x520c
    unsigned int music_command;                     // +0x5210
    unsigned int music_file_base;                    // +0x5214
    void* volatile first_sound_worker;               // +0x5218
    void* volatile second_sound_worker;              // +0x521c
    unsigned int unknown_5220;
    volatile int preload_stop_requested;             // +0x5224
    unsigned char unknown_5228[8];
    unsigned char* volatile pending_wave[37];        // +0x5230
    unsigned int volume_a;                          // +0x52c4
    unsigned int volume_b;                          // +0x52c8
    int volume_attenuation;                         // +0x52cc

    int Initialize(void* window);
};

#include "th10/platform/text_log.hpp"

typedef char WaveFormatMustBe18Bytes[sizeof(WaveFormatImage) == 18 ? 1 : -1];
typedef char WaveDescriptionMustBe36Bytes[sizeof(WaveBufferDescription) == 36 ? 1 : -1];
typedef char WaveNoticeMustBe8Bytes[sizeof(WaveNotificationPosition) == 8 ? 1 : -1];
typedef char MusicCommandMustBe10cBytes[sizeof(MusicCommand) == 0x10c ? 1 : -1];
typedef char WavePanMustBe0680[offsetof(WaveSoundManager, pending_pan) == 0x680 ? 1 : -1];
typedef char WaveCommandsMustBe1f88[offsetof(WaveSoundManager, music_commands) == 0x1f88 ? 1 : -1];
typedef char WaveDuplicateSlotMustBe20[offsetof(WaveDeviceMethods, duplicate_buffer) == 20 ? 1 : -1];
typedef char WavePreloadWorkerMustBe5218[offsetof(WaveSoundManager, first_sound_worker) == 0x5218 ? 1 : -1];
typedef char WaveAttenuationMustBe52cc[offsetof(WaveSoundManager, volume_attenuation) == 0x52cc ? 1 : -1];
typedef char WaveStopSlotMustBe72[offsetof(WaveBufferMethods, stop) == 72 ? 1 : -1];
typedef char WavePositionSlotMustBe16[offsetof(WaveBufferMethods, get_position) == 16 ? 1 : -1];
typedef char StreamPlayingMustBe30[offsetof(SoundStream, playing) == 0x30 ? 1 : -1];
typedef char StreamStateMustBe78[sizeof(SoundStreamingState) == 0x78 ? 1 : -1];
typedef char MusicCursorRecordMustBe90[offsetof(MusicReadCursor, record) == 0x90 ? 1 : -1];
typedef char WaveThreadMustBe0618[offsetof(WaveSoundManager, music_thread) == 0x618 ? 1 : -1];
typedef char WaveMusicBuffersMustBe1ec0[offsetof(WaveSoundManager, cached_music_data) == 0x1ec0 ? 1 : -1];
typedef char MusicRecordMustBe52Bytes[sizeof(MusicTrackRecord) == 52 ? 1 : -1];
typedef char WaveMusicNamesMustBe4108[offsetof(WaveSoundManager, cached_music_names) == 0x4108 ? 1 : -1];
typedef char WaveMusicFileMustBe5108[offsetof(WaveSoundManager, music_file_name) == 0x5108 ? 1 : -1];
typedef char WaveMusicDataMustBe1f84[offsetof(WaveSoundManager, loaded_music_data) == 0x1f84 ? 1 : -1];
typedef char SoundStreamMustBe5208[offsetof(WaveSoundManager, music_stream) == 0x5208 ? 1 : -1];
typedef char WavePendingMustBe5230[offsetof(WaveSoundManager, pending_wave) == 0x5230 ? 1 : -1];

extern "C" {
    extern volatile int g_sound_shutdown_state;
    extern TextLog_0044b810 g_wave_error_log;
    int __fastcall SoundWave_LoadPending_0043d390(int index, WaveSoundManager*, const char* filename);
    void __stdcall Sound_StopMusicWorker(WaveSoundManager*);
    int __stdcall SoundStream_Start(SoundStream*, unsigned int priority, unsigned int flags);
    int __stdcall MusicCursor_Rewind(MusicReadCursor*, unsigned char loop_start);
    int __stdcall MusicCursor_Read(MusicReadCursor*, unsigned int requested,
        unsigned char* destination, unsigned int* received);
    int __stdcall MusicCursor_Open(MusicReadCursor*, unsigned int mode,
        const char* filename, MusicTrackRecord*);
}
