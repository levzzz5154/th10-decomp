#include "th10/platform/native_sound_shutdown.hpp"
#pragma code_seg(".text$a02stop")
void WaveSoundManager::StopMusicWorker() {
    if (!music) return;
    music->Aggregate();
    if (thread) {
        const SoundPost post=data_00466210;
        post(thread_id,0x12,0,0);
        const SoundWait wait=data_0046611c;
        unsigned int result=wait(thread,0x100);
        while (result!=0) {
            post(thread_id,0x12,0,0);
            result=wait(thread,0x100);
        }
        const SoundClose close=data_004660cc;
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
