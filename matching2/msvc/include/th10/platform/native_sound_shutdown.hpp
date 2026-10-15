#pragma once
#include <stddef.h>
struct SoundBuffer;
struct SoundDevice;
struct SoundBufferMethods {
    void* query_interface;
    void* add_reference;
    unsigned long (__stdcall* Release)(SoundBuffer*);
    void* before_position[10];
    long (__stdcall* SetPosition)(SoundBuffer*,unsigned int);
    void* before_stop[4];
    long (__stdcall* Stop)(SoundBuffer*);
};
struct SoundBuffer { SoundBufferMethods* methods; };
struct SoundDeviceMethods {
    void* query_interface;
    void* add_reference;
    unsigned long (__stdcall* Release)(SoundDevice*);
};
struct SoundDevice { SoundDeviceMethods* methods; };
struct SoundStream {
    virtual void* Destroy(unsigned int flags)=0;
    SoundBuffer** buffers;
    unsigned char reserved_008[8];
    unsigned int count;
    unsigned char reserved_014[8];
    unsigned int active;
    unsigned char reserved_020[0x10];
    unsigned int operation;
    __declspec(noinline) int Aggregate();
};
struct WaveSoundManager {
    SoundDevice* device;
    unsigned int reserved_004;
    SoundBuffer* secondary[256];
    unsigned char reserved_408[0x608-0x408];
    SoundBuffer* stream_buffer;
    void* window;
    SoundDevice** owner;
    unsigned int thread_id;
    void* thread;
    unsigned char reserved_61c[0x1ec0-0x61c];
    void* cached[16];
    unsigned char reserved_1f00[0x1f84-0x1f00];
    void* loaded;
    unsigned char reserved_1f88[0x5208-0x1f88];
    SoundStream* music;
    void* event;
    unsigned char reserved_5210[0x20];
    void* pending[37];
    __declspec(noinline) void StopMusicWorker();
    __declspec(noinline) int Cleanup();
};
typedef char StopSlot[offsetof(SoundBufferMethods,Stop)==0x48?1:-1];
typedef char PositionSlot[offsetof(SoundBufferMethods,SetPosition)==0x34?1:-1];
typedef char ManagerThreadOffset[offsetof(WaveSoundManager,thread)==0x618?1:-1];
typedef char ManagerMusicOffset[offsetof(WaveSoundManager,music)==0x5208?1:-1];
typedef char ManagerLoadedOffset[offsetof(WaveSoundManager,loaded)==0x1f84?1:-1];
typedef char ManagerPendingOffset[offsetof(WaveSoundManager,pending)==0x5230?1:-1];
typedef int (__stdcall* SoundPost)(unsigned int,unsigned int,unsigned int,unsigned int);
typedef unsigned int (__stdcall* SoundWait)(void*,unsigned int);
typedef int (__stdcall* SoundClose)(void*);
extern "C" {
extern SoundPost imp_PostThreadMessageA;
extern SoundWait imp_WaitForSingleObject;
extern SoundClose imp_CloseHandle;
extern int (__stdcall* imp_KillTimer)(void*,unsigned int);
void __cdecl crt_free(void*);
void __cdecl owner_free_004524a1(void*);
}
