// Compiler context only; never selected as recovered game code. The bodies
// below stand in for callees recovered or still assembly elsewhere, so the
// whole-program pass selects their private registers.
#include "../../../../src/game/card/card_end.cpp"
#include "../animation_lookup_anchors.cpp"

extern "C" short data_004749ce[];

extern "C" __declspec(noinline) void* __stdcall CardStandIn_Allocate(void* manager);
extern "C" __declspec(noinline) void __stdcall CardStandIn_Register(void* manager, int* out, void* object);

// 0x00409E50
#pragma code_seg(".text$01c_stop")
void AnimationHandle::StopAtFrame1() {
    AnimationScriptId id;
    id.value = value;
    AnimationLookupAnchorEntry* node =
        static_cast<AnimationLookupAnchorEntry*>(AnimationManager_Find_004491c0(g_sprt_ctrl, id));
    if (node) {
        node->flags = 1;
        if (!node->children_flagged)
            for (AnimationLookupAnchorEntry* child = node->children; child; child = child->next)
                child->object->flags = 1;
    }
}

// 0x004172E0
#pragma code_seg(".text$01d_caption")
void __stdcall Card_ShowCaption_004172e0(int kind, CardFront_00409c00* front, int number) {
    int created[10];
    switch (kind) {
    case 0:
        created[0] = 0x47;
        CardStandIn_Allocate(created + 0);
        break;
    case 1:
        created[1] = 0x46;
        CardStandIn_Allocate(created + 1);
        break;
    case 2:
        created[2] = 0x45;
        CardStandIn_Allocate(created + 2);
        break;
    case 3:
        created[3] = 0x44;
        CardStandIn_Allocate(created + 3);
        break;
    case 4:
        created[4] = 0x43;
        CardStandIn_Allocate(created + 4);
        break;
    case 5:
        created[5] = 0x42;
        CardStandIn_Allocate(created + 5);
        break;
    case 6:
        created[6] = 0x41;
        CardStandIn_Allocate(created + 6);
        break;
    default:
        return;
    }
    // Taking the arguments' addresses keeps both on the stack; neither is read
    // before the dispatch, which leaves EAX to the kind.
    CardStandIn_Register(&front, created, &number);
}

// 0x00448D00
#pragma code_seg(".text$01f_create")
AnimationScriptId __stdcall Card_CreateAnimation_00448d00(void* file, int script, int layer) {
    int* object = static_cast<int*>(CardStandIn_Allocate(g_sprt_ctrl));
    object[8] = layer;
    object[0xD7] |= 0x40000000;
    CardStandIn_Register(file, object, reinterpret_cast<void*>(script));
    AnimationScriptId created;
    CardStandIn_Register(g_sprt_ctrl, &created.value, object);
    return created;
}

// 0x0043DC90
#pragma code_seg(".text$01e_queue")
int SoundQueue::Queue(int sound_id, int request) {
    int priority = data_004749ce[sound_id * 4];
    int slot;
    for (slot = 0; slot < 12; ++slot) {
        if (sound_ids[slot] < 0)
            break;
        if (sound_ids[slot] == sound_id) {
            int count = counts[slot];
            if (count < 128) {
                requests[slot][count] = request;
                ++counts[slot];
            }
            return slot;
        }
    }
    if (slot < 12) {
        sound_ids[slot] = sound_id;
        priorities[sound_id] = priority;
        requests[slot][0] = request;
        ++counts[slot];
    }
    return slot;
}
#pragma code_seg()

#pragma code_seg(".text$01b_context")
void __stdcall CardEndCompilerContext(Card_00409c00** cards, int count) {
    // The game counters' address escapes, as it does in the whole program.
    CardStandIn_Allocate(&data_00474c44);
    while (count--) (*cards++)->End();
}
#pragma code_seg()
