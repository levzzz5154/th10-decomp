// Compiler context and ABI anchors only; none of these bytes enter the image.
#include "../../../src/unreferenced/FUN_00448e80_00448e80.cpp"

extern "C" void* __cdecl operator_new_00452493(unsigned int size);
extern "C" void* __cdecl Entity_Constructor_00402050(void* entity);
extern "C" void __cdecl Entity_Init_00401de0(void* unused, void* entity);
extern "C" void __cdecl asm_AnimationObject_LoadScriptTail_0043ee30(void* object);

__declspec(noinline) void** __stdcall AnimationManager_CreatePrimaryFront(
    void* resource, void** out, int index, int render_bucket);

static unsigned int NextPoolIndex_00449950(unsigned int index) {
    unsigned int next = (index + 1) & 0x80000FFFu;
    if ((int)next < 0) {
        next = ((next - 1) | 0xFFFFF000u) + 1;
    }
    return next;
}

// The animation-manager pool allocator modelled only for its argument shape.
// These bytes are never selected as recovered code.
#pragma code_seg(".text$07alloc")
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


// The script loader modelled only for its argument shape.  These bytes are
// never selected as recovered code.
#pragma code_seg(".text$01loadscript")
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


// The primary-list front registration leaf modelled for its argument shape.
// These bytes are never selected as recovered code.
//
// 0x00448A50's head insert unthreads the node's *existing* successor before it
// relinks the node at the front (retail reads node->next at 0x00448A77, after
// it has already cleared it, and only then stores head->next = node->next), so
// the successor is captured first here.
//
// The body's *shape* is the whole point: it is what makes the /LTCG pass hand
// this callee (manager in EDX, entity in EBX, handle record in EAX), and that
// assignment is what lets 0x00448E80 keep the position in EDI.  Measured in the
// throwaway copy: the same body with the successor read folded away (the node
// provably fresh) emits `lea 0x4(%edi),%ecx` - entity in EDI - and the caller
// then grows to 97 bytes with the position moved into EAX and the object into
// EDI.  Keeping the read earns EBX and the caller's retail shape.
struct AnmListNode_00448e80 {
    void* owner;
    AnmListNode_00448e80* next;
    AnmListNode_00448e80* previous;
};

struct AnmListManager_00448e80 {
    unsigned char reserved_00000000[0x72DAD4];
    AnmListNode_00448e80* primary_head;
    AnmListNode_00448e80* primary_tail;
    unsigned char reserved_0072DADC[0x732454 - 0x72DADC];
    int next_id;
};

#pragma code_seg(".text$03regfront")
extern "C" __declspec(noinline) void** __cdecl asm_AnimationManager_RegisterPrimaryFront_00448a50(
        void* manager, void** out, void* entity) {
    unsigned char* m = (unsigned char*)manager;
    unsigned char* e = (unsigned char*)entity;
    unsigned char* base = (unsigned char*)e + 0x04;
    unsigned char* next = *(unsigned char**)(base + 0x04);
    *(void**)base = e;
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
    *(int*)(e + 0x00) = id;
    *(int*)out = id;
    return out;
}
#pragma code_seg()


// 0x00448E80's own caller, shaped like the game's animation-object factories.
// Not recovered game code.
struct AnimationPosition_00448ee0;
__declspec(noinline) void** __stdcall AnimationManager_CreateScreenPositionedPrimaryFront(void*, void**, int, const AnimationPosition_00448ee0*);

#pragma code_seg(".text$09context")
int __stdcall PositionedPrimaryFrontContext(void** resources, void*** outs, int* indexes,
                                            const AnimationPosition_00448e80** positions,
                                            int count) {
    for (int i = 0; i < count; ++i) {
        AnimationManager_CreatePrimaryFront(resources[i], outs[i], indexes[i], 15);
        AnimationManager_CreatePositionedPrimaryFront(resources[i], outs[i], indexes[i],
                                                               positions[i]);
        AnimationManager_CreateScreenPositionedPrimaryFront(resources[i], outs[i], indexes[i], (const AnimationPosition_00448ee0*)positions[i]);
    }
    return count;
}
