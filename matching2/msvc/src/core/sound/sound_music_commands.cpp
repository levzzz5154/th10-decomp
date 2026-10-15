// 0x0043DDF0: run the music command queue and the pending sound effects.
#include "../../../build_support/layout/ltcg/sound_interfaces_dependencies/sound_wave_types.hpp"
#include "th10/app/supervisor.hpp"
#include "th10/platform/sound_fade_0044d4e0.hpp"
#include <string.h>

struct SoundEffectSetting {
    int source;
    short volume;
    short priority;
};
struct PathName {
    int FindBasenameSlot(void* owner);
};
struct PlatformInterfaceState_0044D5D0 {
    int InvokeConfigured();
};
struct PlatformStreamRecord;
struct PlatformStreamState {
    int Select(PlatformStreamRecord* record);
};
struct SoundBuffer;
struct SoundStreamObject {
    virtual ~SoundStreamObject();
};
int __fastcall Platform_InvokeInterface(SoundBuffer* stream);

extern "C" {
__declspec(dllimport) int __stdcall PostThreadMessageA(unsigned int thread_id,
    unsigned int message, unsigned int wparam, unsigned int lparam);
__declspec(dllimport) unsigned int __stdcall WaitForSingleObject(void* handle,
    unsigned int milliseconds);
__declspec(dllimport) int __stdcall CloseHandle(void* handle);
extern WaveSoundManager g_wave_sound_manager;
extern SoundEffectSetting g_sound_effect_settings[];
int __stdcall SoundStream_Restart(SoundStreamingState* stream);
int __stdcall SoundStream_RecreateBuffers_0044cf20(SoundStreamingState* stream);
int __stdcall SoundStreamFill(SoundStream* stream, WaveSecondaryBuffer* buffer,
    unsigned int repeat);
int __stdcall SoundStreamStart(SoundStream* stream, unsigned int priority, unsigned int flags);
}

static inline WaveSecondaryBuffer* GetBuffer(SoundStream* stream, unsigned int index) {
    if (!stream->buffers)
        return 0;
    if (index >= stream->buffer_count)
        return 0;
    return stream->buffers[index];
}

static inline void FadeOut(SoundStream* stream, float seconds) {
    if (stream) {
        stream->fade_mode = 1;
        int frames = static_cast<int>(seconds * 60.0f);
        stream->fade_remaining = frames;
        stream->fade_duration = frames;
    }
}

#pragma code_seg(".text$a03commands")
unsigned int WaveSoundManager::ProcessCommands() {
    if (!device_owner)
        return 0;

    MusicCommand* first = music_commands;
    MusicCommand* command = first;
    int again;
top:
    {
        again = 0;
        switch (command->kind) {
        case 8:
            if (music_stream)
                reinterpret_cast<PlatformInterfaceState_0044D4E0*>(music_stream)
                    ->SetOperationDeadline(volume_a);
            break;

        case 1:
            if (g_supervisor.flags & 0x10) {
                if (command->step != 0)
                    goto advance;
                StopMusicWorker();
                CacheMusic(command->argument, command->name);
                again = 1;
            } else {
                CacheMusic(command->argument, command->name);
                again = 1;
            }
            break;

        case 2:
            if (!(g_supervisor.flags & 0x10) || command->argument < 0) {
                if (!music_stream)
                    break;
                if (command->step == 0) {
                    music_stream->Aggregate();
                    goto advance;
                } else if (command->step == 1) {
                    if (static_cast<SoundStreamingState*>(music_stream)->servicing)
                        goto done;
                    SoundStream_RecreateBuffers_0044cf20(
                        static_cast<SoundStreamingState*>(music_stream));
                    goto advance;
                } else if (command->step == 2) {
                    const char* name;
                    if (command->argument >= 0)
                        name = cached_music_names[command->argument];
                    else
                        name = command->name;
                    int index = reinterpret_cast<PathName*>(const_cast<char*>(name))
                        ->FindBasenameSlot(this);
                    reinterpret_cast<PlatformStreamState*>(music_stream->reader)->Select(
                        reinterpret_cast<PlatformStreamRecord*>(
                            &reinterpret_cast<MusicTrackRecord*>(loaded_music_data)[index]));
                    goto advance;
                } else if (command->step == 3) {
                    WaveSecondaryBuffer* buffer = GetBuffer(music_stream, 0);
                    SoundStream_Restart(static_cast<SoundStreamingState*>(music_stream));
                    command->argument = music_stream->reader->record->loop_end != 0;
                    if (SoundStreamFill(music_stream, buffer, command->argument) >= 0)
                        goto advance;
                    break;
                } else if (command->step == 4) {
                start_stream:
                    SoundStreamStart(music_stream, 0, 1);
                    goto advance;
                } else if (static_cast<int>(command->step) < 7) {
                    goto advance;
                }
            } else {
                if (command->step == 0) {
                    if (PlayCachedMusic(command->argument) == 0)
                        goto advance;
                } else if (command->step == 2) {
                    if (!music_stream)
                        goto advance;
                    if (SoundStream_Restart(
                            static_cast<SoundStreamingState*>(music_stream)) >= 0)
                        goto advance;
                } else if (command->step == 5) {
                    WaveSecondaryBuffer* buffer = GetBuffer(music_stream, 0);
                    command->argument = music_stream->reader->record->loop_end != 0;
                    if (SoundStreamFill(music_stream, buffer, command->argument) >= 0)
                        goto advance;
                    break;
                } else if (command->step == 7) {
                    goto start_stream;
                } else if (static_cast<int>(command->step) < 20) {
                    goto advance;
                }
            }
            break;

        case 4:
            if (!music_stream)
                break;
            if (command->step == 0) {
                music_stream->Aggregate();
                goto advance;
            } else if (command->step == 1) {
                if (!music_thread)
                    break;
                PostThreadMessageA(music_thread_id, 0x12, 0, 0);
                goto advance;
            } else if (command->step == 2) {
                if (WaitForSingleObject(music_thread, 0x100) != 0) {
                    PostThreadMessageA(music_thread_id, 0x12, 0, 0);
                    command->step--;
                } else {
                    music_thread = 0;
                }
                goto advance;
            } else if (command->step == 3) {
                CloseHandle(music_thread);
                CloseHandle(music_worker_event);
                music_thread = 0;
                if (music_stream) {
                    delete reinterpret_cast<SoundStreamObject*>(music_stream);
                    music_stream = 0;
                }
                music_stream = 0;
                goto advance;
            } else if (command->step != 10) {
                goto advance;
            }
            break;

        case 3:
            if (!music_stream)
                break;
            if (command->step == 0) {
                music_stream->Aggregate();
                goto advance;
            } else if (command->step != 1) {
                goto advance;
            }
            break;

        case 5:
            FadeOut(g_wave_sound_manager.music_stream, static_cast<float>(command->argument));
            break;

        case 6:
            if (g_supervisor.music_mode == 1) {
                if (static_cast<SoundStreamingState*>(music_stream)->servicing)
                    goto done;
                if (music_stream)
                    Platform_InvokeInterface(reinterpret_cast<SoundBuffer*>(music_stream));
            }
            break;

        case 7:
            if (g_supervisor.music_mode == 1) {
                if (static_cast<SoundStreamingState*>(music_stream)->servicing)
                    goto done;
                if (music_stream)
                    reinterpret_cast<PlatformInterfaceState_0044D5D0*>(music_stream)
                        ->InvokeConfigured();
            }
            break;

        default:
            goto done;
        }

        // The command is finished: close the queue over it.
        for (int i = 0; i < 31; ++i, ++command) {
            if (command->kind == 0)
                break;
            memcpy(command, command + 1, sizeof(MusicCommand));
        }
        if (again)
            goto top;
    }
    goto done;

advance:
    ++command->step;
done:
    if (!g_supervisor.effect_mode)
        return first->kind;
    {
        for (int i = 0; i < 12; ++i) {
            int index = pending_sound_indices[i];
            if (index < 0)
                break;
            int count = pending_pan_count[i];
            pending_sound_indices[i] = -1;
            if (count < 0) {
                if (secondary_buffers[index + 128])
                    secondary_buffers[index + 128]->methods->stop(secondary_buffers[index + 128]);
                pending_pan_count[i] = 0;
                continue;
            }
            int total = 0;
            for (int j = 0; j < pending_pan_count[i]; ++j)
                total += pending_pan[i][j];
            int pan = total / pending_pan_count[i];
            pending_pan_count[i] = 0;
            if (secondary_buffers[index + 128]) {
                secondary_buffers[index + 128]->methods->stop(secondary_buffers[index + 128]);
                secondary_buffers[index + 128]->methods->set_position(
                    secondary_buffers[index + 128], 0);
                secondary_buffers[index + 128]->methods->set_pan(
                    secondary_buffers[index + 128], pan);
                if (g_wave_sound_manager.volume_b) {
                    float quiet = 1.0f - static_cast<int>(g_wave_sound_manager.volume_b) * 0.01f;
                    secondary_buffers[index + 128]->methods->set_volume(
                        secondary_buffers[index + 128],
                        static_cast<int>((1.0f - quiet * quiet * quiet)
                            * (g_sound_effect_settings[index].volume + 5000)) - 5000);
                } else {
                    secondary_buffers[index + 128]->methods->set_volume(
                        secondary_buffers[index + 128], -10000);
                }
                secondary_buffers[index + 128]->methods->play(
                    secondary_buffers[index + 128], 0, 0, 0);
            }
        }
    }
    return first->kind;
}
#pragma code_seg()
