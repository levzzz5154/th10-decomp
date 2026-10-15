#include <string.h>

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/math/angle.hpp"

// Recovered semantic definitions: the platform prototypes they call and the
// kernel32 entry point reached through a dllimport slot.
#include "th10/platform/sound_buffer.hpp"
#include "th10/platform/windows_types.hpp"

void __cdecl operator delete(void*);
void* __cdecl operator new(unsigned int size);
extern "C" __declspec(dllimport) BOOL __stdcall CloseHandle(HANDLE handle);

// The raw-pair release still lives in inline assembly, so it is called through its
// fixed retail prototype (one stack argument, callee cleans).
typedef void (__stdcall* RawPairReleaseFn)(void* pair);
// CRT heap release reached by the state teardown below.
extern "C" void __cdecl entry_free_004524a1(void* memory);

// 0x0040B940..0x0040B9A2: Recovery_CreateSmallState
// Allocate the small recovery state, register it in the global slot and hand it
// to the pair installer. When the installer rejects it the state is torn down
// through its own release entry and returned to the CRT heap.
struct RecoverySmallState {
    unsigned int flags;             // +0x00, bit 1 marks a registered state
    unsigned int reserved_04[9];    // +0x04..+0x27

    RecoverySmallState();
};

RecoverySmallState::RecoverySmallState() {
    memset(this, 0, sizeof(*this));
    flags |= 2;
    *(void**)&data_00477700 = this;
}

// The installer takes the state as its only stack argument and cleans it, so
// the recovered call keeps the retail push/callee-clean shape.
typedef int (__stdcall* SmallStateInstallFn)(void* state);
typedef void (__stdcall* SmallStateReleaseFn)(void* state);

void* Recovery_CreateSmallState_0040b940() {
    RecoverySmallState* state = new RecoverySmallState;
    if (((SmallStateInstallFn)asm_FUN_0040b560_0040b560)(state)) {
        if (state) {
            ((SmallStateReleaseFn)asm_FUN_0040b7b0_0040b7b0)(state);
            entry_free_004524a1(state);
        }
        return 0;
    }
    return state;
}

// 0x0040CC50 - the enemy's scalar deleting destructor (vtable 0x0046D0C0
// slot 0x14): run the enemy destructor (0x0040DAE0), then free it on request.
// The delete flag is the retail first stack argument, so the second __fastcall
// register argument (EDX) is unused. The destructor is called through its
// fixed retail prototype.
typedef void (__stdcall* EnemyDestroyFn)(void* enemy);

void* __fastcall Enemy_DeletingDestructor(void* enemy, unsigned int unused, unsigned int flags) {
    ((EnemyDestroyFn)asm_FUN_0040dae0_0040dae0)(enemy);
    if (flags & 1)
        operator delete(enemy);
    return enemy;
}

// 0x00413170 - Store an angle after folding it into the retail range.
void Score_SetNormalizedAngle(void* state, float angle) {
    *(float*)((unsigned char*)state + 0x1C) = Angle_Normalize(angle);
}

// 0x004203F0..0x0042046F: Recovery_ReleaseGlobalStates
// Tear down every global state object the engine allocated for the running
// session: manager state, script state, resource state, the small state and the
// pending block. Each object is destroyed through its own release routine and
// then handed back to the CRT heap. The globals keep their stale values, just
// as the retail code leaves them.
typedef void (__stdcall* GlobalStateDestroyFn)(void*);

void Recovery_ReleaseGlobalStates() {
    void* manager_state = *(void**)&data_00477810;
    if (manager_state) {
        ((GlobalStateDestroyFn)asm_FUN_00417c80_00417c80)(manager_state);
        entry_free_004524a1(manager_state);
    }
    void* script_state = *(void**)&data_0047784c;
    if (script_state) {
        ((GlobalStateDestroyFn)asm_FUN_0042cb60_0042cb60)(script_state);
        entry_free_004524a1(script_state);
    }
    void* resource_state = *(void**)&data_00477820;
    if (resource_state) {
        ((GlobalStateDestroyFn)asm_FUN_0041fb50_0041fb50)(resource_state);
        entry_free_004524a1(resource_state);
    }
    void* small_state = *(void**)&data_00477700;
    if (small_state) {
        ((GlobalStateDestroyFn)asm_FUN_0040b7b0_0040b7b0)(small_state);
        entry_free_004524a1(small_state);
    }
    void* pending_block = *(void**)&data_00477838;
    if (pending_block) {
        ((GlobalStateDestroyFn)asm_FUN_004294a0_004294a0)(pending_block);
        entry_free_004524a1(pending_block);
    }
}

// 0x0042ADD0: maintained in src/game/score/score_settings_initialize_defaults_0042add0.cpp.


// 0x00447280..0x004472D1: Recovery_LoadCachedResource
// Return the resource cached for the given index, loading it through 0x004470C0
// when the slot is still empty. The load runs on a worker thread: the entry is
// flagged busy (+0x124) and this side waits a millisecond at a time until the
// worker clears the flag. A progress byte with its sign bit set at 0x00491FF4
// aborts the wait. The index arrives in ECX and the cache table in EDX, with the
// resource name on the stack, matching the retail __fastcall layout.
struct CachedResource {
    unsigned char unknown_000[0x124];
    int busy;                    // +0x124, one while a loader still owns the entry
};

typedef CachedResource* (__stdcall* ResourceLoadFn)(void* owner, int index, const char* name);
// kernel32!Sleep through the import slot the image keeps, loaded once.
typedef void (__stdcall* SleepFn)(unsigned long milliseconds);

CachedResource* __fastcall Recovery_LoadCachedResource(int index, void* owner, const char* name) {
    CachedResource* entry = *(CachedResource**)((char*)owner + 0x3AD06C + index * 4);
    if (entry != 0)
        return entry;
    entry = ((ResourceLoadFn)asm_FUN_004470c0_004470c0)(owner, index, name);
    if (entry == 0)
        return 0;
    SleepFn sleep = *(SleepFn*)&data_004660ac;
    entry->busy = 1;
    do {
        if (data_00491ff4 & 0x80)
            break;
        sleep(1);
    } while (entry->busy != 0);
    return entry;
}

// 0x0044CF00 - scalar deleting destructor for the owned-array object: release
// the owned interfaces first, then free the object when the caller asks for it.
// The delete flag is the retail first stack argument, so the second __fastcall
// register argument (EDX) is unused.
void* __fastcall PlatformOwnedArray_DeletingDestructor(PlatformOwnedArray* owner,
                                                       unsigned int unused, unsigned int flags) {
    Platform_ReleaseOwnedArray(owner);
    if (flags & 1)
        operator delete(owner);
    return owner;
}

// 0x0044D080 - release everything the owned-array object holds: every interface
// in the owned array, the array itself, and the playback device. The object
// returns to the base table at 0x004705D8 first.
//
// th10/platform/sound_buffer.hpp names only the vtable prefix that the
// sound-buffer leaves touch, so the complete layout used here is declared
// locally.
struct OwnedInterface {
    virtual unsigned long __stdcall QueryInterface(void* id, void** object) = 0;
    virtual unsigned long __stdcall AddRef() = 0;
    virtual unsigned long __stdcall Release() = 0;
};

struct OwnedPlaybackDevice {
    unsigned int reserved_00[0x1E];   // +0x00..+0x77
    unsigned int state;               // +0x78, one while the handle is owned
    unsigned int reserved_7C[4];      // +0x7C..+0x8B
    HANDLE handle;                    // +0x8C
};

struct PlatformOwnedArrayFields {
    void* vtable;                     // +0x00
    OwnedInterface** elements;        // +0x04, owned interface pointers
    unsigned int reserved_08;         // +0x08
    OwnedPlaybackDevice* device;      // +0x0C, owned playback device
    unsigned int element_count;       // +0x10
};

void __fastcall Platform_ReleaseOwnedArray(PlatformOwnedArray* owner) {
    PlatformOwnedArrayFields* fields = (PlatformOwnedArrayFields*)owner;
    fields->vtable = (void*)0x004705D8;
    for (unsigned int index = 0; index < fields->element_count; ++index) {
        if (fields->elements[index]) {
            fields->elements[index]->Release();
            fields->elements[index] = 0;
        }
    }
    if (fields->elements) {
        operator delete(fields->elements);
        fields->elements = 0;
    }
    OwnedPlaybackDevice* device = fields->device;
    if (device) {
        if (device->state == 1) {
            CloseHandle(device->handle);
            device->handle = (HANDLE)-1;
        }
        operator delete(device);
        fields->device = 0;
    }
}

// 0x0044D710 - scalar deleting destructor for the sound-buffer object: restore
// the derived table through its base destructor, then free the object on
// request. The delete flag is the retail first stack argument, so the second
// __fastcall register argument (EDX) is unused.
void* __fastcall SoundBuffer_DeletingDestructor(SoundBuffer* sound_buffer, unsigned int unused,
                                                unsigned int flags) {
    SoundBuffer_DestructBaseRetail(sound_buffer);
    if (flags & 1)
        operator delete(sound_buffer);
    return sound_buffer;
}

