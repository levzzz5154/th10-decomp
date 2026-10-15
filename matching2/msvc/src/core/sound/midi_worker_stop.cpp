#include "th10/platform/native_sound_shutdown.hpp"
#pragma code_seg(".text$a02stop")
void WaveSoundManager::StopMusicWorker() {
    if (!music) return;
    music->Aggregate();
    if (thread) {
        const SoundPost post=imp_PostThreadMessageA;
        post(thread_id,0x12,0,0);
        const SoundWait wait=imp_WaitForSingleObject;
        unsigned int result=wait(thread,0x100);
        while (result!=0) {
            post(thread_id,0x12,0,0);
            result=wait(thread,0x100);
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
#include "../../../build_support/layout/ltcg/native_sound_shutdown/aggregate.cpp"
