// Compiler context only; never selected as recovered game code.
#pragma code_seg(".text$01read")
#include "../../../src/core/zunlib/joystick_poll.cpp"

#pragma code_seg(".text$03context")
// A direct caller lets the whole-program pass move `buttons` into ECX as
// retail does.
extern "C" int __stdcall JoystickPollEntry(unsigned short buttons, int set, int pad) {
    return ReadPad(buttons, set, pad);
}
#pragma code_seg()
