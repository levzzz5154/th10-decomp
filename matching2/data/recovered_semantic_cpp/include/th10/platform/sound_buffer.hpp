#pragma once

struct DirectSoundBuffer;

typedef int (__stdcall *DirectSoundBufferStop)(DirectSoundBuffer* self);

// The operation used here is IDirectSoundBuffer::Stop, the nineteenth vtable
// entry (byte offset 0x48).
struct DirectSoundBufferVtable {
    void* methods_before_stop[18];
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
    unsigned int reserved_08[10];      // +0x08..+0x2F
    unsigned int is_playing;           // +0x30
};

int __fastcall Platform_InvokeInterface(SoundBuffer* sound_buffer);
void __fastcall Platform_ReleaseOwnedArray(PlatformOwnedArray* owner);
void __fastcall SoundBuffer_DestructBaseRetail(SoundBuffer* sound_buffer);

extern char sound_buffer_vtable_004705d4;
