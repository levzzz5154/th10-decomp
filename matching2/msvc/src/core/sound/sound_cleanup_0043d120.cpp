// 0x0043D120: release loaded sound data, both buffer banks and streaming state.
#include "th10/platform/native_sound_shutdown.hpp"
#pragma code_seg(".text$a00cleanup")
int WaveSoundManager::Cleanup() {
    if (loaded) {
        entry_free_00452422(loaded);
        loaded=0;
    }
    for (unsigned int index=0;index<128;++index) {
        SoundBuffer* buffer=secondary[index+128];
        if (buffer) {
            buffer->methods->Release(buffer);
            secondary[index+128]=0;
        }
        buffer=secondary[index];
        if (buffer) {
            buffer->methods->Release(buffer);
            secondary[index]=0;
        }
    }
    for (unsigned int index=0;index<37;++index) {
        if (pending[index]) {
            entry_free_00452422(pending[index]);
            pending[index]=0;
        }
    }
    if (owner) {
        data_00466214(window,1);
        StopMusicWorker();
        SoundBuffer* buffer=stream_buffer;
        device=0;
        buffer->methods->Stop(buffer);
        buffer=stream_buffer;
        if (buffer) {
            buffer->methods->Release(buffer);
            stream_buffer=0;
        }
        SoundStream* output=music;
        if (output) {
            output->Destroy(1);
            music=0;
        }
        SoundDevice** cell=owner;
        if (cell) {
            SoundDevice* current=*cell;
            if (current) {
                current->methods->Release(current);
                *cell=0;
            }
            owner_free_004524a1(cell);
            owner=0;
        }
        for (unsigned int index=0;index<16;++index) {
            if (cached[index]) {
                entry_free_00452422(cached[index]);
                cached[index]=0;
            }
        }
    }
    return 0;
}
#pragma code_seg()
