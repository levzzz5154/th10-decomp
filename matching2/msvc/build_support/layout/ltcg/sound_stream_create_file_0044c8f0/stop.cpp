// Unselected native ABI anchors from src/core/sound/midi_worker_stop.cpp and
// build_support/layout/ltcg/native_sound_shutdown/aggregate.cpp. Only the shared type view
// and placement sections differ.
struct SoundStreamDestroyView { virtual void* Destroy(unsigned int flags) = 0; };
extern "C" {
    extern int (__stdcall* data_00466210)(unsigned int, unsigned int, unsigned int, unsigned int);
    extern unsigned int (__stdcall* data_0046611c)(void*, unsigned int);
    extern int (__stdcall* data_004660cc)(void*);
}
#pragma code_seg(".text$01stop")
void WaveSoundManager::StopMusicWorker() {
    if (!music_stream) return;
    music_stream->StopAndRewind();
    if (music_thread) {
        int (__stdcall* const post)(unsigned int, unsigned int, unsigned int, unsigned int) = data_00466210;
        post(music_thread_id, 0x12, 0, 0);
        unsigned int (__stdcall* const wait)(void*, unsigned int) = data_0046611c;
        unsigned int result = wait(music_thread, 0x100);
        while (result != 0) {
            post(music_thread_id, 0x12, 0, 0);
            result = wait(music_thread, 0x100);
        }
        int (__stdcall* const close)(void*) = data_004660cc;
        close(music_thread);
        close(music_worker_event);
        music_thread = 0;
    }
    SoundStream* output = music_stream;
    if (output) {
        reinterpret_cast<SoundStreamDestroyView*>(output)->Destroy(1);
        music_stream = 0;
    }
}
#pragma code_seg(".text$04aggregate")
__declspec(noinline) int SoundStream::StopAndRewind() {
    if (!buffers) return (int)0x800401f0U;
    int result = 0;
    playing = 0;
    for (unsigned int index = 0; index < buffer_count; ++index) {
        WaveSecondaryBuffer* buffer = buffers[index];
        result |= buffer->methods->stop(buffer);
        buffer = buffers[index];
        result |= buffer->methods->set_position(buffer, 0);
    }
    fade_mode = 0;
    return result;
}
#pragma code_seg()
