#pragma once
#include <stddef.h>

// A value record leaves both indices on the stack under MSVC fastcall.
// The flag word remains in ECX; no synthetic EDX argument is needed.
struct JoystickSelection {
    int binding_set;
    // Retail reloads the stack index after polling external APIs.
    volatile int device;
};

enum JoystickAction {
    JoystickFire = 0x001, JoystickBomb = 0x002,
    JoystickSlow = 0x004, JoystickEscape = 0x008,
    JoystickUp = 0x010, JoystickDown = 0x020,
    JoystickLeft = 0x040, JoystickRight = 0x080,
    JoystickControl = 0x100
};

struct JoystickPosition {
    unsigned long size, flags;
    unsigned long x, y, z, r, u, v;
    unsigned long buttons, button_number, pov, reserved1, reserved2;
};

struct JoystickCapabilities {
    unsigned short manufacturer, product;
    char name[32];
    unsigned int x_min, x_max, y_min, y_max, z_min, z_max;
    unsigned int buttons, period_min, period_max;
    unsigned int r_min, r_max, u_min, u_max, v_min, v_max;
    unsigned int capabilities, max_axes, axes, max_buttons;
    char registry_key[32], oem_driver[260];
};

struct JoystickBindings {
    unsigned char reserved_000[0x58];
    short fire, bomb, slow, escape;
    unsigned char reserved_060[8];
    short control;
};

// DIJOYSTATE2: button indices refer to the 128-byte button array, not the
// beginning of the complete device-state record.
struct JoystickDeviceState {
    long x, y, z, rx, ry, rz, sliders[2];
    unsigned long pov[4];
    unsigned char buttons[128];
    long vx, vy, vz, vrx, vry, vrz, velocity_sliders[2];
    long ax, ay, az, arx, ary, arz, acceleration_sliders[2];
    long fx, fy, fz, frx, fry, frz, force_sliders[2];
};

struct JoystickDevice;
struct JoystickDeviceVtable {
    void* preceding_acquire[7];
    long (__stdcall *Acquire)(JoystickDevice*);
    void* unacquire;
    long (__stdcall *GetState)(JoystickDevice*, unsigned int, void*);
    void* preceding_poll[15];
    long (__stdcall *Poll)(JoystickDevice*);
};
struct JoystickDevice { JoystickDeviceVtable* vtable; };

typedef char PositionSize[sizeof(JoystickPosition) == 0x34 ? 1 : -1];
typedef char CapabilitiesSize[sizeof(JoystickCapabilities) == 0x194 ? 1 : -1];
typedef char CapabilitiesXOffset[offsetof(JoystickCapabilities, x_min) == 0x24 ? 1 : -1];
typedef char BindingSize[sizeof(JoystickBindings) == 0x6a ? 1 : -1];
typedef char DeviceStateSize[sizeof(JoystickDeviceState) == 0x110 ? 1 : -1];
typedef char ButtonsOffset[offsetof(JoystickDeviceState, buttons) == 0x30 ? 1 : -1];
typedef char AcquireOffset[offsetof(JoystickDeviceVtable, Acquire) == 0x1c ? 1 : -1];
typedef char GetStateOffset[offsetof(JoystickDeviceVtable, GetState) == 0x24 ? 1 : -1];
typedef char PollOffset[offsetof(JoystickDeviceVtable, Poll) == 0x64 ? 1 : -1];

extern "C" {
extern unsigned int (__stdcall *data_00466280)(unsigned int, JoystickPosition*);
extern unsigned int data_00491ff4;
extern JoystickBindings data_00474e30[];
extern JoystickCapabilities data_004918b8[];
extern JoystickDevice* data_00491c3c[];
extern short data_00491d5e, data_00491d60;
unsigned short __fastcall JoystickReadBindings(unsigned int flags, JoystickSelection selection);
}
