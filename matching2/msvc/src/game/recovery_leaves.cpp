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

// 0x0040CC50 - scalar deleting destructor for the bullet object: destroy the
// bullet through its own release entry, then free it on request. The delete
// flag is the retail first stack argument, so the second __fastcall register
// argument (EDX) is unused. The bullet destructor still lives in inline
// assembly, so it is called through its fixed retail prototype.
typedef void (__stdcall* BulletDestroyFn)(void* bullet);

void* __fastcall Bullet_DeletingDestructor(void* bullet, unsigned int unused, unsigned int flags) {
    ((BulletDestroyFn)asm_FUN_0040dae0_0040dae0)(bullet);
    if (flags & 1)
        operator delete(bullet);
    return bullet;
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

// 0x0042ADD0..0x0042AE5D - Recovery_InitializeRandomTable
//
// Fills a 0x448-byte string table: an 8-space blank entry, then 512 generated
// 16-bit words from the game's LCG. The recurrence matches RngState::NextWord
// but reads the seed as a whole 32-bit word and shifts the whole word left, so
// the source used a 32-bit local rather than the 16-bit field rng.hpp wraps.
// The loop head is 16-byte aligned by the compiler, which is where the jump
// over the alignment padding inside the region comes from.
extern "C" void __fastcall Recovery_InitializeRandomTable_0042add0(int unused, char* table) {
    memset(table, 0, 0x448);
    *(unsigned short*)(table + 2) = 0;
    *(unsigned short*)table = 0x5453;
    *(unsigned int*)(table + 8) = 0x448;
    memcpy(table + 12, &data_0046e354, 9);
    unsigned short* out = (unsigned short*)(table + 70);
    int remaining = 512;
    do {
        unsigned short word;
        unsigned int value = *(unsigned int*)&data_004918b0;
        value ^= 0x9630;
        value -= 0x6553;
        unsigned int high = ((unsigned short)value) >> 14;
        word = (unsigned short)(high + (value << 2));
        *(unsigned short*)&data_004918b0 = word;
        ++*(unsigned int*)&data_004918b4;
        *out++ = word;
        --remaining;
    } while (remaining);
}

// 0x0043C870..0x0043C889: Platform_DeletingDestructorNoReturn
// Scalar deleting destructor for the platform-owned raw pair: release the pair,
// return the object to the CRT heap and report success in EAX. The object
// arrives in ECX, matching the retail thunk ABI.
int __fastcall Platform_DeletingDestructorNoReturn(void* pair) {
    if (pair) {
        ((RawPairReleaseFn)asm_Recovery_ReleaseRawPair_0043cb00)(pair);
        entry_free_004524a1(pair);
    }
    return 0;
}


// 0x00441F50..0x00441FC3: ?RecoveryState_Configure41F50@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_RecoveryState_Configure41F50_00441f50() {
    __asm {
    L_00441f50:
        movzx edx,dl
    L_00441f53:
        mov dword ptr [eax+230h],edx
    L_00441f59:
        movzx edx,byte ptr [esp+8]
    L_00441f5e:
        mov dword ptr [eax+22Ch],ecx
    L_00441f64:
        movzx ecx,byte ptr [esp+4]
    L_00441f69:
        mov dword ptr [eax+20Ch],edx
    L_00441f6f:
        mov dword ptr [eax+208h],ecx
    L_00441f75:
        mov ecx,dword ptr [eax+228h]
    L_00441f7b:
        xor edx,edx
    L_00441f7d:
        test cl,1
    L_00441f80:
        jne short L_00441fab
    L_00441f82:
        or ecx,1
    L_00441f85:
        mov dword ptr [eax+21Ch],edx
    L_00441f8b:
        mov dword ptr [eax+218h],0FFF0BDC1h
    L_00441f95:
        mov dword ptr [eax+220h],edx
    L_00441f9b:
        mov dword ptr [eax+224h],476F78h
    L_00441fa5:
        mov dword ptr [eax+228h],ecx
    L_00441fab:
        mov dword ptr [eax+21Ch],edx
    L_00441fb1:
        mov dword ptr [eax+220h],edx
    L_00441fb7:
        mov dword ptr [eax+218h],0FFFFFFFFh
    L_00441fc1:
        ret 8
    }
}

// 0x00442220..0x004422EF: ConfigureColorPlaybackState
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_ConfigureColorPlaybackState_00442220() {
    __asm {
    L_00442220:
        sub esp,0Ch
    L_00442223:
        push ebx
    L_00442224:
        push ebp
    L_00442225:
        push esi
    L_00442226:
        mov esi,dword ptr [esp+1Ch]
    L_0044222a:
        mov dword ptr [eax+100h],esi
    L_00442230:
        xor esi,esi
    L_00442232:
        push edi
    L_00442233:
        xor edi,edi
    L_00442235:
        lea ebp,[eax+0D4h]
    L_0044223b:
        mov dword ptr [ebp],esi
    L_0044223e:
        mov dword ptr [ebp+4],edi
    L_00442241:
        xor ebx,ebx
    L_00442243:
        mov dword ptr [ebp+8],ebx
    L_00442246:
        lea ebp,[eax+0E0h]
    L_0044224c:
        mov dword ptr [ebp],esi
    L_0044224f:
        movzx esi,byte ptr [esp+24h]
    L_00442254:
        mov dword ptr [ebp+4],edi
    L_00442257:
        mov dword ptr [ebp+8],ebx
    L_0044225a:
        mov dword ptr [eax+104h],esi
    L_00442260:
        movzx ebx,byte ptr [ecx+2]
    L_00442264:
        movzx ebp,byte ptr [ecx+1]
    L_00442268:
        movzx ecx,byte ptr [ecx]
    L_0044226b:
        movzx esi,byte ptr [edx+2]
    L_0044226f:
        movzx edi,byte ptr [edx+1]
    L_00442273:
        movzx edx,byte ptr [edx]
    L_00442276:
        mov dword ptr [esp+10h],ecx
    L_0044227a:
        lea ecx,[eax+0BCh]
    L_00442280:
        mov dword ptr [ecx],edx
    L_00442282:
        mov dword ptr [ecx+4],edi
    L_00442285:
        mov dword ptr [ecx+8],esi
    L_00442288:
        mov ecx,dword ptr [esp+10h]
    L_0044228c:
        lea edx,[eax+0C8h]
    L_00442292:
        mov dword ptr [edx],ecx
    L_00442294:
        mov dword ptr [edx+4],ebp
    L_00442297:
        pop edi
    L_00442298:
        mov dword ptr [edx+8],ebx
    L_0044229b:
        mov ecx,dword ptr [eax+0FCh]
    L_004422a1:
        pop esi
    L_004422a2:
        pop ebp
    L_004422a3:
        xor edx,edx
    L_004422a5:
        test cl,1
    L_004422a8:
        pop ebx
    L_004422a9:
        jne short L_004422d4
    L_004422ab:
        or ecx,1
    L_004422ae:
        mov dword ptr [eax+0F0h],edx
    L_004422b4:
        mov dword ptr [eax+0ECh],0FFF0BDC1h
    L_004422be:
        mov dword ptr [eax+0F4h],edx
    L_004422c4:
        mov dword ptr [eax+0F8h],476F78h
    L_004422ce:
        mov dword ptr [eax+0FCh],ecx
    L_004422d4:
        mov dword ptr [eax+0F0h],edx
    L_004422da:
        mov dword ptr [eax+0F4h],edx
    L_004422e0:
        mov dword ptr [eax+0ECh],0FFFFFFFFh
    L_004422ea:
        add esp,0Ch
    L_004422ed:
        ret 8
    }
}

// 0x00442300..0x00442381: RecoveryState_Configure42300
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_RecoveryState_Configure42300_00442300() {
    __asm {
    L_00442300:
        mov dword ptr [eax+12Ch],ecx
    L_00442306:
        movzx ecx,byte ptr [esp+4]
    L_0044230b:
        mov dword ptr [eax+130h],ecx
    L_00442311:
        movzx ecx,byte ptr [esp+8]
    L_00442316:
        mov dword ptr [eax+108h],ecx
    L_0044231c:
        movzx ecx,byte ptr [esp+0Ch]
    L_00442321:
        xor edx,edx
    L_00442323:
        mov dword ptr [eax+110h],edx
    L_00442329:
        mov dword ptr [eax+114h],edx
    L_0044232f:
        mov dword ptr [eax+10Ch],ecx
    L_00442335:
        mov ecx,dword ptr [eax+128h]
    L_0044233b:
        test cl,1
    L_0044233e:
        jne short L_00442369
    L_00442340:
        or ecx,1
    L_00442343:
        mov dword ptr [eax+11Ch],edx
    L_00442349:
        mov dword ptr [eax+118h],0FFF0BDC1h
    L_00442353:
        mov dword ptr [eax+120h],edx
    L_00442359:
        mov dword ptr [eax+124h],476F78h
    L_00442363:
        mov dword ptr [eax+128h],ecx
    L_00442369:
        mov dword ptr [eax+11Ch],edx
    L_0044236f:
        mov dword ptr [eax+120h],edx
    L_00442375:
        mov dword ptr [eax+118h],0FFFFFFFFh
    L_0044237f:
        ret 0Ch
    }
}

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

