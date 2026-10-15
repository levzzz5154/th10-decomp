// Compiler context only; never selected as recovered game code.
#include "../units/stage_anm_reload_93580a.cpp"

extern "C" void* __stdcall find_opaque_004491c0(unsigned int id);

struct AnimationNode_0040c3c0 {
    AnimationNode_0040c3c0* object;
    AnimationNode_0040c3c0* next;
    unsigned char pad_008[0x14 - 0x08];
    AnimationNode_0040c3c0* children;
    int children_flagged;
    unsigned char pad_01c[0x304 - 0x1C];
    unsigned short stop_frame;
};

// Model of 0x00409E50 at its retail address; it earns the EAX handle.
#pragma code_seg(".text$00anchor")
__declspec(noinline) void StopHandle_00409e50(AnimationHandle_0040c3c0* handle) {
    unsigned int id = *(unsigned short*)&handle->id;
    AnimationNode_0040c3c0* node = (AnimationNode_0040c3c0*)find_opaque_004491c0(id);
    if (node != 0) {
        node->stop_frame = 1;
        if (!node->children_flagged) {
            for (AnimationNode_0040c3c0* child = node->children; child != 0; child = child->next)
                child->object->stop_frame = 1;
        }
    }
}
#pragma code_seg()

typedef unsigned int (__cdecl* ThreadEntry_0040c3c0)();

#pragma inline_depth(0)
#pragma code_seg(".text$07context")
int __stdcall StageAnmReloadContext(StageOwner_0040c3c0** owners, int count, ThreadEntry_0040c3c0* entry) {
    int total = 0;
    *entry = Stage_ReloadAnmThread_0040c3a0;
    for (int index = 0; index < count; ++index)
        total += owners[index]->ReloadStageAnm();
    return total;
}
#pragma code_seg()
#pragma inline_depth()
