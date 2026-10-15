#pragma once

struct DirectSoundBuffer;

typedef int (__stdcall *DirectSoundBufferStop)(DirectSoundBuffer* self);
typedef int (__stdcall *DirectSoundBufferGetStatus)(
    DirectSoundBuffer* self, unsigned int* status);

// The operation used here is IDirectSoundBuffer::Stop, the nineteenth vtable
// entry (byte offset 0x48).
struct DirectSoundBufferVtable {
    void* methods_before_get_status[9];
    DirectSoundBufferGetStatus get_status;
    void* methods_between_status_and_stop[8];
    DirectSoundBufferStop stop;
};

struct DirectSoundBuffer {
    DirectSoundBufferVtable* vtable;
};

struct PlatformOwnedArray {
    void* vtable;
};

// Fields used by the platform sound-buffer leaves. The full object continues
// past is_playing; these names preserve the established offsets without
// guessing at fields that these functions do not touch.
struct SoundBuffer : PlatformOwnedArray {
    DirectSoundBuffer** buffers;       // +0x04
    unsigned int reserved_08[2];       // +0x08..+0x0F
    unsigned int buffer_count;         // +0x10
    int fade_remaining;                 // +0x14
    int fade_duration;                  // +0x18
    unsigned int fade_mode;             // +0x1C
    unsigned int reserved_20[4];       // +0x20..+0x2F
    unsigned int is_playing;           // +0x30
};

int __fastcall Platform_InvokeInterface(SoundBuffer* sound_buffer);
void __fastcall Platform_ReleaseOwnedArray(PlatformOwnedArray* owner);
void __fastcall SoundBuffer_DestructBaseRetail(SoundBuffer* sound_buffer);

extern char sound_buffer_vtable;
