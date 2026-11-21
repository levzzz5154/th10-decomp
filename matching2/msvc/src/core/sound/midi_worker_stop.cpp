// 0x0043DAB0: WaveSoundManager::StopMusicWorker
#include "th10/platform/native_sound_shutdown.hpp"
enum MidiWorkerStopConst {
    MIDI_WM_QUIT = 0x12,
    MIDI_STOP_WAIT_MS = 256
};

#pragma code_seg(".text$a02stop")
void WaveSoundManager::StopMusicWorker() {
    if (!music) return;
    music->Aggregate();
    if (thread) {
        const SoundPost post=imp_PostThreadMessageA;
        post(thread_id,MIDI_WM_QUIT,0,0);
        const SoundWait wait=imp_WaitForSingleObject;
        unsigned int result=wait(thread,MIDI_STOP_WAIT_MS);
        while (result!=0) {
            post(thread_id,MIDI_WM_QUIT,0,0);
            result=wait(thread,MIDI_STOP_WAIT_MS);
        }
        const SoundClose close=imp_CloseHandle;
        close(thread);
        close(event);
        thread=0;
    }
    SoundStream* output=music;
    if (output) {
        output->Destroy(1);
        music=0;
    }
}
#pragma code_seg()
