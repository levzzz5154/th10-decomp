#include "th10/platform/native_game_input.hpp"
#include "th10/platform/text_log.hpp"
extern "C" TextLog_0044b810 g_log;
#pragma code_seg(".text$a10input")
int GameInputSystem::InitializeDevices() {
    void* instance=(void*)imp_GetWindowLongA(window,-6);
    if (flags&8U) return -1;
    if (DirectInput8Create_0045071e(instance,0x800,&g_guid_dinput,&direct_input,0)<0) {
        direct_input=0;
        g_log.Append(str_directinput_unavailable);
        return -1;
    }
    if (direct_input->vtable->CreateDevice(direct_input,&g_guid_syskeyboard,&keyboard,0)<0) {
        if (direct_input) {
            direct_input->vtable->Release(direct_input);
            direct_input=0;
        }
        g_log.Append(str_directinput_unavailable);
        return -1;
    }
    if (keyboard->vtable->SetDataFormat(keyboard,&g_dinput_keyboard_format)<0) {
        if (keyboard) {
            keyboard->vtable->Release(keyboard);
            keyboard=0;
        }
        if (direct_input) {
            direct_input->vtable->Release(direct_input);
            direct_input=0;
        }
        g_log.Append(str_directinput_no_data_format);
        return -1;
    }
    if (keyboard->vtable->SetCooperativeLevel(keyboard,window,0x16)<0) {
        if (keyboard) {
            keyboard->vtable->Release(keyboard);
            keyboard=0;
        }
        ReleaseInput();
        g_log.Append(str_directinput_no_cooperative_level);
        return -1;
    }
    keyboard->vtable->Acquire(keyboard);
    g_log.Append(str_directinput_ok);
    direct_input->vtable->EnumDevices(direct_input,4,&GameInput_EnumDevice_0043baf0,0,1);
    if (joystick) {
        joystick->vtable->SetDataFormat(joystick,&g_dinput_joystick_format);
        joystick->vtable->SetCooperativeLevel(joystick,window,10);
        g_application.capabilities.size=44;
        joystick->vtable->GetCapabilities(joystick,&g_application.capabilities);
        joystick->vtable->EnumObjects(joystick,&GameInput_EnumObject_0043bb30,0,0);
        g_log.Append(str_pad_found);
    }
    return 0;
}
#pragma code_seg()


#include "th10/platform/native_game_input.hpp"
// 0x0043BA90: the input initialisation thread (started by 0x004201B0):
// create the keyboard and joystick devices and publish which exist. Thread entry: no arguments, final flags in EAX, plain RET.
#pragma code_seg(".text$a12game")
extern "C" unsigned int __cdecl Input_InitThread() {
    g_app_flags&=~0x600U;
    g_application.InitializeDevices();
    unsigned int flags=g_app_flags;
    flags^=(((unsigned int)(g_application.keyboard!=0)<<9)^flags)&0x200U;
    flags^=(((unsigned int)(g_application.joystick!=0)<<10)^flags)&0x400U;
    g_app_flags=flags;
    return flags;
}
#pragma code_seg()

