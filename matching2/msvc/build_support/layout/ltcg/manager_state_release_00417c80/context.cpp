// Compiler context only; this caller is never selected as recovered game
// code. The shared LTCG unit recovers the observed callee register
// allocation: the whole teardown body, the score-archive flush and the
// game-thread animation fetch walk in one link, and the models below give the
// positioned-primary creation the callees and register pressure retail uses
// (the same modelling the lazy-animation-fetch cluster carries).
#include "../../../../src/game/score/score_manager_save.cpp"
#include "../../../../src/game/ending/animation_resource_lazy_fetch.cpp"

// Bindings for everything the models below call.
extern "C" void* g_sprt_ctrl;
extern "C" void* __cdecl operator_new_00452493(unsigned int size);
extern "C" void* __cdecl Entity_Constructor_00402050(void* entity);
extern "C" void __cdecl Entity_Init_00401de0(void* unused, void* entity);
extern "C" void __cdecl asm_AnimationObject_LoadScriptTail_0043ee30(void* object);

static unsigned int NextPoolIndex_00449950(unsigned int index) {
    unsigned int next = (index + 1) & 0x80000FFFu;
    if ((int)next < 0) {
        next = ((next - 1) | 0xFFFFF000u) + 1;
    }
    return next;
}

// The animation-manager pool allocator modelled only for its argument shape.
// These bytes are never selected as recovered code.
#pragma code_seg(".text$8alloc")
extern "C" __declspec(noinline) void* __cdecl asm_FUN_00449950_00449950(void* manager) {
    unsigned char* bytes = (unsigned char*)manager;
    unsigned int index = *(unsigned int*)(bytes + 0x3AD068);
    if (bytes[0x3AC068 + index] != 0) {
        index = NextPoolIndex_00449950(index);
        *(unsigned int*)(bytes + 0x3AD068) = index;
        if (bytes[0x3AC068 + index] != 0) {
            unsigned char* allocated = (unsigned char*)operator_new_00452493(0x3AC);
            if (allocated == 0) {
                return 0;
            }
            Entity_Constructor_00402050(allocated);
            Entity_Init_00401de0(0, allocated);
            *(unsigned int*)(bytes + 0x3AD068) =
                NextPoolIndex_00449950(*(unsigned int*)(bytes + 0x3AD068));
            return allocated;
        }
    }
    unsigned char* slot = bytes + 0x68 + index * 0x3AC;
    bytes[0x3AC068 + index] = 1;
    *(unsigned int*)(bytes + 0x3AD068) =
        NextPoolIndex_00449950(*(unsigned int*)(bytes + 0x3AD068));
    return slot;
}
#pragma code_seg()

// The script loader modelled only for its argument shape.
#pragma code_seg(".text$8zzload")
extern "C" __declspec(noinline) void __cdecl asm_AnimationObject_LoadScript_0043e710(
        void* resource, void* object, int index) {
    unsigned char* res = (unsigned char*)resource;
    unsigned char* obj = (unsigned char*)object;
    unsigned char* entries = *(unsigned char**)(res + 0x11C);
    if (*(int*)(entries + index * 4) == 0 || *(int*)(res + 0x124) != 0) {
        for (unsigned int byte = 0; byte < 0x3AC; ++byte) { obj[byte] = 0; }
        return;
    }
    Entity_Init_00401de0(0, obj);
    int flags = *(int*)(obj + 0x35C);
    *(short*)(obj + 0x38A) = (short)index;
    *(short*)(obj + 0x386) = *(short*)res;
    *(void**)(obj + 0x308) = res;
    *(int*)(obj + 0x35C) = flags & ~0x600;
    int value = *(int*)(entries + index * 4);
    *(int*)(obj + 0x38C) = value;
    *(int*)(obj + 0x390) = value;
    int state = *(int*)(obj + 0x6C);
    if ((state & 1) == 0) {
        *(int*)(obj + 0x6C) = state | 1;
        *(int*)(obj + 0x60) = 0;
        *(int*)(obj + 0x5C) = (int)0xFFF0BDC1u;
        *(int*)(obj + 0x64) = 0;
        *(int*)(obj + 0x68) = (int)0x00476F78u;
    }
    *(int*)(obj + 0x60) = 0;
    *(int*)(obj + 0x64) = 0;
    *(int*)(obj + 0x5C) = -1;
    *(int*)(obj + 0x35C) = *(int*)(obj + 0x35C) & ~1;
    asm_AnimationObject_LoadScriptTail_0043ee30(obj);
    unsigned char* manager = (unsigned char*)g_sprt_ctrl;
    *(int*)(manager + 0x4C) = *(int*)(manager + 0x4C) + 1;
}
#pragma code_seg()

// The primary-list registration leaf modelled only for its argument shape.
struct AnmListNode_00448d50 {
    void* owner;
    AnmListNode_00448d50* next;
    AnmListNode_00448d50* previous;
};

struct AnmListObject_00448d50 {
    int id;
    AnmListNode_00448d50 primary_back;
};

struct AnmListManager_00448d50 {
    unsigned char reserved_00000000[0x72DAD4];
    AnmListNode_00448d50* primary_back_head;
    AnmListNode_00448d50* primary_back_tail;
    unsigned char reserved_0072DADC[0x732454 - 0x72DADC];
    int next_id;
};

#pragma code_seg(".text$8regprimary")
extern "C" __declspec(noinline) void** __cdecl asm_AnimationManager_RegisterPrimaryBack_004489d0(
        void* manager, void** out, void* entity) {
    unsigned char* m = (unsigned char*)manager;
    unsigned char* e = (unsigned char*)entity;
    void** node = (void**)(e + 0x04);
    node[0] = e; node[1] = 0; node[2] = 0;
    void* head = *(void**)(m + 0x72DAD4);
    if (head == 0) { *(void**)(m + 0x72DAD4) = node; }
    else {
        unsigned char* tail = *(unsigned char**)(m + 0x72DAD8);
        unsigned char* next = *(unsigned char**)(tail + 0x04);
        if (next != 0) { node[1] = next; *(unsigned char**)(next + 0x08) = (unsigned char*)node; }
        *(unsigned char**)(tail + 0x04) = (unsigned char*)node;
        node[2] = tail;
    }
    *(void**)(m + 0x72DAD8) = node;
    int id = ++*(int*)(m + 0x732454);
    if (id == 0) { id = ++*(int*)(m + 0x732454); }
    *(int*)(e + 0x00) = id;
    *(int*)out = id;
    return out;
}
#pragma code_seg()

// 0x00448D50 as a compiled ABI anchor: the animation manager's positioned
// primary creation.  Its body is the recovered one; retail hands this body
// the position record in EDI and receives the resource, out slot and index on
// the stack.  Never exported as recovered code.
struct AnimationObject_00448d50 {
    unsigned char reserved_000[0x20];
    int render_bucket_020;                          // +0x20
    unsigned char reserved_024[0x340 - 0x24];
    AnimationPosition_00448d50 position_340;        // +0x340
    unsigned char reserved_34c[0x35C - 0x34C];
    unsigned int flags_035c;                        // +0x35C
};

#pragma code_seg(".text$8primary")
__declspec(noinline)
void** __stdcall AnimationManager_CreatePositionedPrimary_00448d50(
    void* resource, void** out, int index,
    const AnimationPosition_00448d50* position) {
    AnimationObject_00448d50* object =
        (AnimationObject_00448d50*)asm_FUN_00449950_00449950(g_sprt_ctrl);
    object->flags_035c |= 0x40000000u;
    object->render_bucket_020 = 0;
    object->position_340 = *position;
    asm_AnimationObject_LoadScript_0043e710(resource, object, index);
    asm_AnimationManager_RegisterPrimaryBack_004489d0(g_sprt_ctrl, out, object);
    return out;
}
#pragma code_seg()

#pragma code_seg(".text$8context")
struct Game;
extern "C" void __stdcall Game_Destroy(Game* state);

extern "C" int __stdcall ManagerReleaseContext_00417c80(void** states, int count) {
    for (int index = 0; index < count; ++index)
        Game_Destroy((Game*)states[index]);
    return 0;
}
#pragma code_seg()
