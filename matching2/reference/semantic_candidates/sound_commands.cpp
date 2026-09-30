// Complete 0x0043DDF0 dispatcher: 1,452-byte manifest region, including its
// jump table and interior alignment. Retail and candidate both use stdcall.
// Native MSVC frame/byte matching is pending; there is no inline assembly.
#include "sound_wave_types.hpp"
#include "sound_memory_words.hpp"
#include "sound_effect_support.hpp"

struct PathName_0043d2a0 {
    char text[1];
    int FindBasenameSlot_0043d2a0(void*);
};
typedef int (__stdcall* CommandPostMessage)(unsigned int, unsigned int, unsigned int, unsigned int);
typedef unsigned int (__stdcall* CommandWait)(void*, unsigned int);
typedef int (__stdcall* CommandClose)(void*);

extern "C" {
    extern volatile unsigned char g_sound_mode_flags;
    extern volatile unsigned char g_music_enabled;
    extern volatile unsigned char g_sound_effects_enabled;
    extern SoundStream* g_sound_fade_stream;
    extern int g_sound_effects_volume;
    extern const float g_sound_fade_scale;
    extern const float g_sound_volume_scale;
    extern const float g_sound_volume_one;
    extern CommandPostMessage g_sound_post_thread_message;
    extern CommandWait g_sound_wait_for_object;
    extern CommandClose g_sound_close_handle;
    int __stdcall Sound_CacheMusic_0043d7d0(const char*, WaveSoundManager*, int);
    int __stdcall SoundStream_LaunchCached_0043d950(WaveSoundManager*, unsigned int);
    int __stdcall SoundStream_Restart_0044dad0(SoundStreamingState*);
    int __stdcall SoundStream_RecreateBuffers_0044cf20(SoundStreamingState*);
    int __stdcall SoundStream_FillBuffer_0044d110(SoundStream*, WaveSecondaryBuffer*, unsigned int);
    int __fastcall SoundStream_StopFirst_0044d5b0(SoundStream*);
}

namespace {
__forceinline SoundStreamingState* Streaming(WaveSoundManager* manager) {
    return static_cast<SoundStreamingState*>(manager->music_stream);
}

__forceinline WaveSecondaryBuffer* FirstBuffer(SoundStream* stream) {
    WaveSecondaryBuffer** buffers = stream->buffers;
    return buffers && stream->buffer_count ? buffers[0] : 0;
}

__forceinline WaveSecondaryBuffer* EffectBuffer(WaveSoundManager* manager, unsigned int index) {
    unsigned int address = reinterpret_cast<unsigned int>(manager) + 0x208 + index * 4;
    return *reinterpret_cast<WaveSecondaryBuffer**>(address);
}

__forceinline MusicCommand* NextCommand(MusicCommand* command) {
    return reinterpret_cast<MusicCommand*>(reinterpret_cast<unsigned int>(command) + sizeof(MusicCommand));
}

}

extern "C" unsigned int __stdcall Sound_ProcessCommands_0043ddf0(WaveSoundManager* manager) {
    if (!manager->device_owner)
        return 0;
    MusicCommand* command = manager->music_commands;
    bool advance;
    bool remove;
    bool inspect_tail;
    do {
        advance = false;
        remove = false;
        inspect_tail = false;
        unsigned int kind = command->kind;
        switch (kind) {
        case 1: {
            bool cached = (g_sound_mode_flags & 0x10) != 0;
            if (cached && command->step != 0) {
                advance = true;
                break;
            }
            if (cached)
                Sound_StopMusicWorker_0043dab0(manager);
            Sound_CacheMusic_0043d7d0(command->name, manager, command->argument);
            remove = inspect_tail = true;
            break;
        }
        case 2:
            if ((g_sound_mode_flags & 0x10) && command->argument >= 0) {
                int step = static_cast<int>(command->step);
                if (step == 0) {
                    advance = SoundStream_LaunchCached_0043d950(manager,
                        static_cast<unsigned int>(command->argument)) == 0;
                    remove = !advance;
                } else if (step == 2) {
                    SoundStreamingState* stream = Streaming(manager);
                    advance = !stream || SoundStream_Restart_0044dad0(stream) >= 0;
                    remove = !advance;
                } else if (step == 5) {
                    SoundStream* stream = manager->music_stream;
                    WaveSecondaryBuffer* buffer = FirstBuffer(stream);
                    unsigned int repeat = stream->reader->record->loop_end != 0;
                    command->argument = repeat;
                    advance = SoundStream_FillBuffer_0044d110(manager->music_stream, buffer, repeat) >= 0;
                    remove = !advance;
                } else if (step == 7) {
                    SoundStream_Start_0044d440(manager->music_stream, 0, 1);
                    advance = true;
                } else {
                    advance = step < 20;
                    remove = !advance;
                }
            } else {
                SoundStreamingState* stream = Streaming(manager);
                if (!stream) {
                    remove = true;
                    break;
                }
                int step = static_cast<int>(command->step);
                if (step == 0) {
                    manager->music_stream->StopAndRewind();
                    advance = true;
                } else if (step == 1) {
                    if (!Streaming(manager)->servicing) {
                        SoundStream_RecreateBuffers_0044cf20(Streaming(manager));
                        advance = true;
                    }
                } else if (step == 2) {
                    int index = command->argument;
                    unsigned int name = index < 0 ? reinterpret_cast<unsigned int>(command->name) :
                        reinterpret_cast<unsigned int>(manager) + 0x4108 + static_cast<unsigned int>(index) * 256;
                    unsigned int record_index = static_cast<unsigned int>(
                        reinterpret_cast<PathName_0043d2a0*>(name)->FindBasenameSlot_0043d2a0(manager));
                    MusicTrackRecord* record = reinterpret_cast<MusicTrackRecord*>(
                        reinterpret_cast<unsigned int>(manager->loaded_music_data) + record_index * 52);
                    manager->music_stream->reader->SelectRecord(record);
                    advance = true;
                } else if (step == 3) {
                    WaveSecondaryBuffer* buffer = FirstBuffer(stream);
                    SoundStream_Restart_0044dad0(stream);
                    unsigned int repeat = manager->music_stream->reader->record->loop_end != 0;
                    command->argument = repeat;
                    advance = SoundStream_FillBuffer_0044d110(manager->music_stream, buffer, repeat) >= 0;
                    remove = !advance;
                } else if (step == 4) {
                    SoundStream_Start_0044d440(manager->music_stream, 0, 1);
                    advance = true;
                } else {
                    advance = step < 7;
                    remove = !advance;
                }
            }
            break;
        case 3:
            if (!manager->music_stream || command->step == 1)
                remove = true;
            else {
                if (command->step == 0)
                    manager->music_stream->StopAndRewind();
                advance = true;
            }
            break;
        case 4:
            if (!manager->music_stream) {
                remove = true;
                break;
            }
            switch (command->step) {
            case 0:
                manager->music_stream->StopAndRewind();
                advance = true;
                break;
            case 1:
                if (manager->music_thread) {
                    g_sound_post_thread_message(manager->music_thread_id, 0x12, 0, 0);
                    advance = true;
                } else
                    remove = true;
                break;
            case 2:
                if (g_sound_wait_for_object(manager->music_thread, 0x100) == 0)
                    manager->music_thread = 0;
                else {
                    g_sound_post_thread_message(manager->music_thread_id, 0x12, 0, 0);
                    --command->step;
                }
                advance = true;
                break;
            case 3: {
                const CommandClose close = g_sound_close_handle;
                close(manager->music_thread);
                close(manager->music_worker_event);
                SoundStream* stream = manager->music_stream;
                manager->music_thread = 0;
                if (stream) {
                    stream->methods->destroy(stream, 1);
                    manager->music_stream = 0;
                }
                manager->music_stream = 0;
                advance = true;
                break;
            }
            case 10:
                remove = true;
                break;
            default:
                advance = true;
            }
            break;
        case 5: {
            SoundStream* stream = g_sound_fade_stream;
            int duration = command->argument;
            if (stream) {
                stream->fade_mode = 1;
                int frames = static_cast<int>(TruncatedSoundLowWord(static_cast<long double>(duration) * g_sound_fade_scale));
                stream->fade_remaining = frames;
                stream->fade_duration = frames;
            }
            remove = true;
            break;
        }
        case 6:
        case 7: {
            if (g_music_enabled == 1) {
                SoundStreamingState* stream = Streaming(manager);
                if (stream->servicing)
                    break;
                if (stream) {
                    if (kind == 6)
                        SoundStream_StopFirst_0044d5b0(stream);
                    else
                        stream->ResumeConfigured();
                }
            }
            remove = true;
            break;
        }
        case 8:
            if (manager->music_stream)
                manager->music_stream->SetVolume(static_cast<int>(manager->volume_a));
            remove = true;
            break;
        }
        if (advance)
            ++command->step;
        if (remove) {
            unsigned int copied = 0;
            while (copied < 31 && command->kind) {
                MusicCommand* next = NextCommand(command);
                CopySoundWords(reinterpret_cast<unsigned int>(command), reinterpret_cast<unsigned int>(next), sizeof(MusicCommand));
                command = next;
                ++copied;
            }
        }
        // Retail resumes at the end of the shifted range, not the queue head.
    } while (inspect_tail);

    if (g_sound_effects_enabled) {
        for (unsigned int pending = 0; pending < 12; ++pending) {
            int index = manager->pending_sound_indices[pending];
            if (index < 0)
                break;
            int count = manager->pending_pan_count[pending];
            manager->pending_sound_indices[pending] = -1;
            if (count < 0) {
                WaveSecondaryBuffer* buffer = EffectBuffer(manager, static_cast<unsigned int>(index));
                if (buffer)
                    buffer->methods->stop(buffer);
                manager->pending_pan_count[pending] = 0;
            } else {
                unsigned int sum = 0;
                if (count > 0) {
                    unsigned int remaining = static_cast<unsigned int>(manager->pending_pan_count[pending]);
                    unsigned int address = reinterpret_cast<unsigned int>(&manager->pending_pan[pending][0]);
                    do {
                        sum += *reinterpret_cast<const volatile unsigned int*>(address);
                        address += 4;
                    } while (--remaining);
                }
                // Division precedes even the null-buffer check. Keep it as an
                // unconditional observable evaluation, including count zero.
                volatile int pan = static_cast<int>(sum) / count;
                manager->pending_pan_count[pending] = 0;
                WaveSecondaryBuffer* buffer = EffectBuffer(manager, static_cast<unsigned int>(index));
                if (buffer) {
                    buffer->methods->stop(buffer);
                    buffer = EffectBuffer(manager, static_cast<unsigned int>(index));
                    buffer->methods->set_position(buffer, 0);
                    buffer = EffectBuffer(manager, static_cast<unsigned int>(index));
                    buffer->methods->set_pan(buffer, pan);
                    int volume = g_sound_effects_volume;
                    buffer = EffectBuffer(manager, static_cast<unsigned int>(index));
                    if (volume) {
                        int base_volume = g_sound_effect_settings[index].volume;
                        WaveBufferMethods* methods = buffer->methods;
                        long double factor = static_cast<long double>(g_sound_volume_one) -
                            static_cast<long double>(volume) * g_sound_volume_scale;
                        unsigned int adjusted = TruncatedSoundLowWord((static_cast<long double>(g_sound_volume_one) -
                            factor * factor * factor) * (base_volume + 5000));
                        buffer = EffectBuffer(manager, static_cast<unsigned int>(index));
                        methods->set_volume(buffer, static_cast<int>(adjusted - 5000));
                    } else
                        buffer->methods->set_volume(buffer, -10000);
                    buffer = EffectBuffer(manager, static_cast<unsigned int>(index));
                    buffer->methods->play(buffer, 0, 0, 0);
                }
            }
        }
    }
    return manager->music_commands[0].kind;
}
