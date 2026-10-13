// 0x00448E30..0x00448E78: create an animation object and prepend it to the
#include "th10/game/player_hud_animations.hpp"
// manager's primary-front list.
struct AnimationObject_00448e30 {
    unsigned char reserved_000[0x20];
    int render_bucket_020;
    unsigned char reserved_024[0x35C - 0x24];
    unsigned int flags_035c;
};

extern "C" void* data_00491c10;

// Same-TU forward for the allocator thunk: /O2 inlines it into the create
// body so the whole-program pass sees the real allocator edge without an
// extra symbol.
extern "C" void* __cdecl asm_FUN_00449950_00449950(void* manager) {
    return ((AnimationPool*)manager)->Allocate();
}

// The registrar thunk the create wrapper calls; anchored at 0x00448A50 and
// never selected as recovered code.  Its explicit out parameter is what lets
// the whole-program pass wire the wrapper's out slot to the registrar's sret.
#pragma code_seg(".text$00448a50_front")
extern "C" __declspec(noinline) void** __cdecl asm_AnimationManager_RegisterPrimaryFront_00448a50(
        void* manager, void** out, void* entity) {
    unsigned char* m = (unsigned char*)manager;
    unsigned char* base = (unsigned char*)entity + 0x04;
    unsigned char* next = *(unsigned char**)(base + 0x04);
    *(void**)base = entity;
    *(void**)(base + 0x04) = 0;
    *(void**)(base + 0x08) = 0;
    unsigned char* head = *(unsigned char**)(m + 0x72DAD4);
    if (head == 0) {
        *(void**)(m + 0x72DAD8) = base;
    } else {
        if (next != 0) {
            *(unsigned char**)(head + 0x04) = next;
            *(unsigned char**)(next + 0x08) = head;
        }
        *(unsigned char**)(base + 0x04) = head;
        *(unsigned char**)(head + 0x08) = base;
    }
    *(void**)(m + 0x72DAD4) = base;
    int id = ++*(int*)(m + 0x732454);
    if (id == 0) { id = ++*(int*)(m + 0x732454); }
    *(int*)((unsigned char*)entity + 0x00) = id;
    *(int*)out = id;
    return out;
}
#pragma code_seg()

#pragma code_seg(".text$00448e30_create")
__declspec(noinline)
void** __stdcall AnimationManager_CreatePrimaryFront_00448e30(
        void* resource, void** out, int index, int render_bucket) {
    AnimationObject_00448e30* object =
        (AnimationObject_00448e30*)asm_FUN_00449950_00449950(data_00491c10);
    unsigned int flags = object->flags_035c;
    object->render_bucket_020 = render_bucket;
    object->flags_035c = flags | 0x40000000u;
    ((AnimationResource_00449870*)resource)->InitializeObject((Entity*)object, index);
    asm_AnimationManager_RegisterPrimaryFront_00448a50(data_00491c10, out, object);
    return out;
}
#pragma code_seg()
