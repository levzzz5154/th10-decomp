#pragma once
#include <stddef.h>
struct GameInputGuid { unsigned int word[4]; };
struct GameInputDataFormat;
struct GameInputDeviceInstance;
struct GameInputDeviceObject;
struct GameInputCapabilities { unsigned int size,remaining[10]; };
typedef int (__stdcall *GameInputDeviceCallback)(const GameInputDeviceInstance*,void*);
typedef int (__stdcall *GameInputObjectCallback)(const GameInputDeviceObject*,void*);
struct GameInputDevice;
struct GameDirectInput;
struct GameDirectInputVtable {
    void* query_interface;
    void* add_reference;
    unsigned long (__stdcall *Release)(GameDirectInput*);
    long (__stdcall *CreateDevice)(GameDirectInput*,const GameInputGuid*,GameInputDevice**,void*);
    long (__stdcall *EnumDevices)(GameDirectInput*,unsigned int,GameInputDeviceCallback,void*,unsigned int);
};
struct GameDirectInput { GameDirectInputVtable* vtable; };
struct GameInputDeviceVtable {
    void* query_interface;
    void* add_reference;
    unsigned long (__stdcall *Release)(GameInputDevice*);
    long (__stdcall *GetCapabilities)(GameInputDevice*,GameInputCapabilities*);
    long (__stdcall *EnumObjects)(GameInputDevice*,GameInputObjectCallback,void*,unsigned int);
    void* get_property;
    void* set_property;
    long (__stdcall *Acquire)(GameInputDevice*);
    void* unacquire;
    void* get_device_state;
    void* get_device_data;
    long (__stdcall *SetDataFormat)(GameInputDevice*,const GameInputDataFormat*);
    void* set_event_notification;
    long (__stdcall *SetCooperativeLevel)(GameInputDevice*,void*,unsigned int);
};
struct GameInputDevice { GameInputDeviceVtable* vtable; };
struct GameInputSystem {
    unsigned char reserved_000[0xC];
    GameDirectInput* direct_input;
    GameInputDevice* keyboard;
    GameInputDevice* joystick;
    unsigned char reserved_018[4];
    GameInputCapabilities capabilities;
    void* window;
    unsigned char reserved_04c[0x150-0x4c];
    unsigned int flags;
    __declspec(noinline) void ReleaseInput();
    __declspec(noinline) int InitializeDevices();
};
typedef char GameInputDirectOffset[offsetof(GameInputSystem,direct_input)==0xC?1:-1];
typedef char GameInputKeyboardOffset[offsetof(GameInputSystem,keyboard)==0x10?1:-1];
typedef char GameInputJoystickOffset[offsetof(GameInputSystem,joystick)==0x14?1:-1];
typedef char GameInputCapsOffset[offsetof(GameInputSystem,capabilities)==0x1C?1:-1];
typedef char GameInputWindowOffset[offsetof(GameInputSystem,window)==0x48?1:-1];
typedef char GameInputFlagsOffset[offsetof(GameInputSystem,flags)==0x150?1:-1];
typedef char GameInputFormatOffset[offsetof(GameInputDeviceVtable,SetDataFormat)==0x2C?1:-1];
typedef char GameInputCooperativeOffset[offsetof(GameInputDeviceVtable,SetCooperativeLevel)==0x34?1:-1];
typedef char GameInputCapabilitiesSize[sizeof(GameInputCapabilities)==44?1:-1];
extern "C" {
extern GameInputSystem data_00491c28;
extern unsigned int data_00491ff4;
extern const GameInputGuid data_00467aac,data_0046793c;
extern const GameInputDataFormat data_004664fc,data_00466704;
extern char data_0046f9e0[],data_0046f9b0[],data_0046f97c[],data_0046f954[],data_0046f934[];
extern long (__stdcall* data_0046621c)(void*,int);
long __stdcall DirectInput8Create_0045071e(void*,unsigned int,const GameInputGuid*,GameDirectInput**,void*);
int __stdcall GameInput_EnumDevice_0043baf0(const GameInputDeviceInstance*,void*);
int __stdcall GameInput_EnumObject_0043bb30(const GameInputDeviceObject*,void*);
__declspec(noinline) unsigned int __cdecl Input_InitThread();
}
