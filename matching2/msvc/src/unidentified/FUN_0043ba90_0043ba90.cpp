#include "th10/platform/native_game_input.hpp"
// Real underlying thread entry: no arguments, final flags in EAX, plain RET.
#pragma code_seg(".text$a12game")
extern "C" unsigned int __cdecl GameWorker_0043ba90() {
    data_00491ff4&=~0x600U;
    data_00491c28.InitializeDevices();
    unsigned int flags=data_00491ff4;
    flags^=(((unsigned int)(data_00491c28.keyboard!=0)<<9)^flags)&0x200U;
    flags^=(((unsigned int)(data_00491c28.joystick!=0)<<10)^flags)&0x400U;
    data_00491ff4=flags;
    return flags;
}
#pragma code_seg()
