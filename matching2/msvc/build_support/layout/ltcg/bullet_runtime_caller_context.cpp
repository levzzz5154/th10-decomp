// Compiler context only; never recovered game code.
#include "../../../src/game/bullet/bullet_runtime_update.cpp"
#include "th10/game/player_wrap.hpp"
#pragma code_seg(".text$10context")
int __stdcall SoundQueueMotionContext(BulletRuntimeDeceleration** bullets, int count) {
    for (int i = 0; i < count; ++i) {
        bullets[i]->TurnStep();
        bullets[i]->AimStep();
        bullets[i]->Bounce();
        BulletRuntimeTick(reinterpret_cast<BulletRuntimeState*>(bullets[i]));
        data_00492590.QueuePan(i, reinterpret_cast<BulletRuntimeState*>(bullets[i])->position.x);
    }
    return count;
}
#pragma code_seg()

extern "C" const float data_00470b0c;
extern float g_playfield_min_x, g_playfield_max_x, g_playfield_min_y, g_playfield_max_y;
#pragma code_seg(".text$00ebounds")
int PlayfieldPoint::OutsidePlayfieldInclusive(float width, float height) const {
    float half_width = width * 0.5f;
    if (half_width + x <= g_playfield_min_x || x - half_width >= g_playfield_max_x)
        return 1;
    float half_height = height * 0.5f;
    if (half_height + y <= g_playfield_min_y || y - half_height >= g_playfield_max_y)
        return 1;
    return 0;
}

#pragma code_seg()

extern float g_frame_timer_normal_lower, g_frame_timer_normal_upper;
// 0x0044BF40. Converting after the branch reloads the binary32 elapsed field.
#pragma code_seg(".text$13advance")
void FrameTimer::Advance(float delta) {
    previous = current;
    if (*speed > g_frame_timer_normal_lower && *speed < g_frame_timer_normal_upper) {
        elapsed += delta;
    } else {
        elapsed += delta * *speed;
    }
    current = int(elapsed);
}

#pragma code_seg()

extern "C" float data_00470b5c;
#pragma code_seg(".text$00dbounds")
int PlayfieldPoint::OutsidePlayfield(float width, float height) const {
    float half_width = width * 0.5f;
    if (half_width + x <= g_playfield_min_x || x - half_width >= g_playfield_max_x)
        return 1;
    float half_height = height * 0.5f;
    if (half_height + y <= data_00470b5c || y - half_height >= g_playfield_max_y)
        return 1;
    return 0;
}

#pragma code_seg()

// Compiler context and ABI anchors only; none of these bytes enter the image.
extern "C" void* g_sprt_ctrl;

extern "C" void* __cdecl operator_new_00452493(unsigned int size);
extern "C" void* __cdecl Entity_Constructor_00402050(void* entity);
extern "C" void __cdecl Entity_Init_00401de0(void* unused, void* entity);
extern "C" void __cdecl asm_AnimationObject_LoadScriptTail_0043ee30(void* object);
__declspec(noinline) void** __stdcall
AnimationManager_CreatePrimaryBack_00448d00(void* resource, void** out, int index,
                                            int render_bucket);

struct AnimationPosition_00448db0;
__declspec(noinline) void** __stdcall
AnimationManager_CreateScreenPositionedPrimary_00448db0(void*, void**, int,
                                                        const AnimationPosition_00448db0*);

static unsigned int NextPoolIndex_00449950(unsigned int index) {
    unsigned int next = (index + 1) & 0x80000FFFu;
    if ((int)next < 0) {
        next = ((next - 1) | 0xFFFFF000u) + 1;
    }
    return next;
}

#pragma code_seg(".text$09zallocate")
extern "C" __declspec(noinline) void* __cdecl asm_FUN_00449950_00449950(void* manager) {
    unsigned char* bytes = (unsigned char*)manager;
    unsigned int index = *(unsigned int*)(bytes + 0x3AD068);
    if (bytes[0x3AC068 + index] != 0) {
        index = NextPoolIndex_00449950(index);
        *(unsigned int*)(bytes + 0x3AD068) = index;
        if (bytes[0x3AC068 + index] != 0) {
            unsigned char* allocated = (unsigned char*)operator_new_00452493(0x3AC);
            if (allocated == 0)
                return 0;
            Entity_Constructor_00402050(allocated);
            Entity_Init_00401de0(0, allocated);
            *(unsigned int*)(bytes + 0x3AD068) =
                NextPoolIndex_00449950(*(unsigned int*)(bytes + 0x3AD068));
            return allocated;
        }
    }
    unsigned char* slot = bytes + 0x68 + index * 0x3AC;
    bytes[0x3AC068 + index] = 1;
    *(unsigned int*)(bytes + 0x3AD068) = NextPoolIndex_00449950(*(unsigned int*)(bytes + 0x3AD068));
    return slot;
}
#pragma code_seg()

#pragma code_seg(".text$06load")
extern "C" __declspec(noinline) void __cdecl
asm_AnimationObject_LoadScript_0043e710(void* resource, void* object, int index) {
    unsigned char* res = (unsigned char*)resource;
    unsigned char* obj = (unsigned char*)object;
    unsigned char* entries = *(unsigned char**)(res + 0x11C);
    if (*(int*)(entries + index * 4) == 0 || *(int*)(res + 0x124) != 0) {
        for (unsigned int byte = 0; byte < 0x3AC; ++byte) {
            obj[byte] = 0;
        }
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

#pragma code_seg(".text$08register")
extern "C" __declspec(noinline) void** __cdecl
asm_AnimationManager_RegisterPrimaryBack_004489d0(void* manager, void** out, void* entity) {
    unsigned char* m = (unsigned char*)manager;
    unsigned char* e = (unsigned char*)entity;
    void** node = (void**)(e + 0x04);
    node[0] = e;
    node[1] = 0;
    node[2] = 0;
    void* head = *(void**)(m + 0x72DAD4);
    if (head == 0) {
        *(void**)(m + 0x72DAD4) = node;
    } else {
        unsigned char* tail = *(unsigned char**)(m + 0x72DAD8);
        unsigned char* next = *(unsigned char**)(tail + 0x04);
        if (next != 0) {
            node[1] = next;
            *(unsigned char**)(next + 0x08) = (unsigned char*)node;
        }
        *(unsigned char**)(tail + 0x04) = (unsigned char*)node;
        node[2] = tail;
    }
    *(void**)(m + 0x72DAD8) = node;
    int id = ++*(int*)(m + 0x732454);
    if (id == 0) {
        id = ++*(int*)(m + 0x732454);
    }
    *(int*)(e + 0x00) = id;
    *(int*)out = id;
    return out;
}
#pragma code_seg()
