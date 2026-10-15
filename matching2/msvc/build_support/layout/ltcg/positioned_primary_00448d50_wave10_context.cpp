// Compiler context and ABI anchors only; none of these bytes enter the image.
#include "../../../src/core/sprtlib/animation_manager_create_positioned_primary_00448d50.cpp"

extern "C" void* __cdecl operator_new_00452493(unsigned int size);
extern "C" void* __cdecl Entity_Constructor_00402050(void* entity);
extern "C" void __cdecl Entity_Init_00401de0(void* unused, void* entity);
extern "C" void __cdecl asm_AnimationObject_LoadScriptTail_0043ee30(void* object);
__declspec(noinline) void** __stdcall AnimationManager_CreatePrimaryBack(
    void* resource, void** out, int index, int render_bucket);

struct AnimationPosition_00448db0;
__declspec(noinline) void** __stdcall AnimationManager_CreateScreenPositionedPrimary(void*, void**, int, const AnimationPosition_00448db0*);

static unsigned int NextPoolIndex_00449950(unsigned int index) {
    unsigned int next = (index + 1) & 0x80000FFFu;
    if ((int)next < 0) {
        next = ((next - 1) | 0xFFFFF000u) + 1;
    }
    return next;
}

#pragma code_seg(".text$07alloc")
extern "C" __declspec(noinline) void* __cdecl asm_FUN_00449950_00449950(void* manager) {
    unsigned char* bytes = (unsigned char*)manager;
    unsigned int index = *(unsigned int*)(bytes + 0x3AD068);
    if (bytes[0x3AC068 + index] != 0) {
        index = NextPoolIndex_00449950(index);
        *(unsigned int*)(bytes + 0x3AD068) = index;
        if (bytes[0x3AC068 + index] != 0) {
            unsigned char* allocated = (unsigned char*)operator_new_00452493(0x3AC);
            if (allocated == 0) return 0;
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

struct AnmListNode_00448d50 {
    void* owner;
    AnmListNode_00448d50* next;
    AnmListNode_00448d50* previous;
};

#pragma code_seg(".text$03regprimary")
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

#pragma code_seg(".text$09context")
int __stdcall PositionedPrimaryContext(void** resources, void*** outs, int* indexes,
                                       const AnimationPosition_00448d50** positions,
                                       int count) {
    for (int i = 0; i < count; ++i) {
        AnimationManager_CreatePrimaryBack(resources[i], outs[i], indexes[i], 15);
        AnimationManager_CreatePositionedPrimary(resources[i], outs[i], indexes[i],
                                                          positions[i]);
        AnimationManager_CreateScreenPositionedPrimary(resources[i], outs[i], indexes[i], (const AnimationPosition_00448db0*)positions[i]);
    }
    return count;
}
