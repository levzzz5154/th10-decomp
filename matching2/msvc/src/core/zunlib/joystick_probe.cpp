// 0x0044A0C0..0x0044A128: probe the two WinMM joystick slots and report when
// neither device responds.  The import variables are deliberately typed as
// function pointers: retail loads each slot once and reuses the first pointer
// for both position queries.
struct JoystickInfoEx_0044a0c0 {
    unsigned int dwSize;
    unsigned int dwFlags;
    unsigned int values[11];
};

typedef unsigned int (__stdcall *JoyGetPosExFn_0044a0c0)(
        unsigned int device, JoystickInfoEx_0044a0c0* info);
typedef unsigned int (__stdcall *JoyGetDevCapsFn_0044a0c0)(
        unsigned int device, void* capabilities, unsigned int size);

extern "C" JoyGetPosExFn_0044a0c0 imp_joyGetPosEx;
extern "C" JoyGetDevCapsFn_0044a0c0 imp_joyGetDevCapsA;

struct TextLog_0044b810 {
    char text[0x2000];
    char* cursor;
    unsigned char dirty;
    char* Append(char* format, ...);
};

#pragma code_seg(".text$80joystick")
short __stdcall Joystick_Probe_0044a0c0() {
    JoystickInfoEx_0044a0c0 info;
    info.dwSize = sizeof(info);
    info.dwFlags = 0xFF;

    JoyGetPosExFn_0044a0c0 get_position = imp_joyGetPosEx;
    if (get_position(0, &info) && get_position(1, &info)) {
        ((TextLog_0044b810*)0x00474F70)->Append(
                (char*)0x00470580);
        return 1;
    }

    imp_joyGetDevCapsA(0, (void*)0x004918B8, 0x194);
    return 0;
}
#pragma code_seg()
