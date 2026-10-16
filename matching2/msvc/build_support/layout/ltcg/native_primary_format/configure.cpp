#include "th10/platform/native_primary_format.hpp"
#pragma code_seg(".text$a04configure")
int NativeDeviceOwner::Configure(void* window, unsigned int level, unsigned short bits, unsigned short channels, unsigned int rate) {
    WaveDirectSoundDevice* current=device;
    if (current) {
        current->methods->release(current);
        device=0;
    }
    int result=Ordinal_112(0,&device,0);
    if (result>=0) {
        current=device;
        result=current->methods->set_cooperative_level(current,window,level);
        if (result>=0) {
            Sound_SetPrimaryFormat(bits,channels,rate,&device);
            result=0;
        }
    }
    return result;
}
#pragma code_seg()
