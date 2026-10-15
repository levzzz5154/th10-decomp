#include "th10/platform/native_sound_shutdown.hpp"
#pragma code_seg(".text$a04aggregate")
int SoundStream::Aggregate() {
    if (!buffers) return (int)0x800401f0U;
    int result=0;
    operation=0;
    for (unsigned int index=0;index<count;++index) {
        SoundBuffer* buffer=buffers[index];
        result|=buffer->methods->Stop(buffer);
        buffer=buffers[index];
        result|=buffer->methods->SetPosition(buffer,0);
    }
    active=0;
    return result;
}
#pragma code_seg()
