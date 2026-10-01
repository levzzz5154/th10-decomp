#include "th10/platform/native_game_input.hpp"
#include "th10/platform/text_log.hpp"
extern "C" TextLog_0044b810 data_00474f70;
#pragma code_seg(".text$a10input")
int GameInputSystem::InitializeDevices() {
    void* instance=(void*)data_0046621c(window,-6);
    if (flags&8U) return -1;
    if (DirectInput8Create_0045071e(instance,0x800,&data_00467aac,&direct_input,0)<0) {
        direct_input=0;
        data_00474f70.Append(data_0046f9e0);
        return -1;
    }
    if (direct_input->vtable->CreateDevice(direct_input,&data_0046793c,&keyboard,0)<0) {
        if (direct_input) {
            direct_input->vtable->Release(direct_input);
            direct_input=0;
        }
        data_00474f70.Append(data_0046f9e0);
        return -1;
    }
    if (keyboard->vtable->SetDataFormat(keyboard,&data_004664fc)<0) {
        if (keyboard) {
            keyboard->vtable->Release(keyboard);
            keyboard=0;
        }
        if (direct_input) {
            direct_input->vtable->Release(direct_input);
            direct_input=0;
        }
        data_00474f70.Append(data_0046f9b0);
        return -1;
    }
    if (keyboard->vtable->SetCooperativeLevel(keyboard,window,0x16)<0) {
        if (keyboard) {
            keyboard->vtable->Release(keyboard);
            keyboard=0;
        }
        ReleaseInput();
        data_00474f70.Append(data_0046f97c);
        return -1;
    }
    keyboard->vtable->Acquire(keyboard);
    data_00474f70.Append(data_0046f954);
    direct_input->vtable->EnumDevices(direct_input,4,&GameInput_EnumDevice_0043baf0,0,1);
    if (joystick) {
        joystick->vtable->SetDataFormat(joystick,&data_00466704);
        joystick->vtable->SetCooperativeLevel(joystick,window,10);
        data_00491c28.capabilities.size=44;
        joystick->vtable->GetCapabilities(joystick,&data_00491c28.capabilities);
        joystick->vtable->EnumObjects(joystick,&GameInput_EnumObject_0043bb30,0,0);
        data_00474f70.Append(data_0046f934);
    }
    return 0;
}
#pragma code_seg()
