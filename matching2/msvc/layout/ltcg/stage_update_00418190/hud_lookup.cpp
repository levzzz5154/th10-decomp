#define data_00491c10 stage_hud_data_00491c10
#define data_0047770c stage_hud_data_0047770c
#define data_00474c40 stage_hud_data_00474c40
#define data_004776e0 stage_hud_data_004776e0
#define data_00477704 stage_hud_data_00477704
#define data_00477834 stage_hud_data_00477834
#define data_00477838 stage_hud_data_00477838
#define data_0047783c stage_hud_data_0047783c
#define data_00476f78 stage_hud_data_00476f78
#define data_00491fc4 stage_hud_data_00491fc4
#define data_00491fb8 stage_hud_data_00491fb8
#define data_00492590 stage_hud_data_00492590
#include "hud_view.hpp"
// Compiler-only ABI anchors for the animation lookup (0x004491C0) and the
// flag setter (0x004492A0), placed by clusters whose recovered code precedes
// 0x004491C0. The setter forwards no receiver, so the pass drops ECX from
// every call. Never selected as recovered game code.
//
// The including source declares ResultAnimationId and the setter.
struct ResultAnimationEntry {
    ResultAnimationEntry* object;
    ResultAnimationEntry* next;
    unsigned char reserved_08[0x0C];
    ResultAnimationEntry* children;
    int children_flagged;
    unsigned char reserved_1c[0x340];
    unsigned int flags;
};

struct ResultAnimationLookup {
    unsigned char reserved[0x72DAD4];
    ResultAnimationEntry* primary_bucket;
    int reserved_2;
    ResultAnimationEntry* secondary_bucket;
};

#pragma code_seg(".text$004491c0_fn")
__declspec(noinline) void* __fastcall ResultAnimation_Find(
        ResultAnimationLookup* context, ResultAnimationId id) {
    if (!id.value)
        return 0;
    for (ResultAnimationEntry* node = context->primary_bucket; node != 0; node = node->next)
        if (*(int*)node->object == id.value)
            return node->object;
    for (ResultAnimationEntry* node = context->secondary_bucket; node != 0; node = node->next)
        if (*(int*)node->object == id.value)
            return node->object;
    return 0;
}
#pragma code_seg()

#pragma code_seg(".text$004492a0_fn")
__declspec(noinline) void* __fastcall ResultAnimation_Retire(
        ResultAnimationLookup* context, ResultAnimationId id) {
    ResultAnimationEntry* entry =
        (ResultAnimationEntry*)ResultAnimation_Find(context, id);
    if (entry) {
        entry->flags |= 0x4000000;
        if (!entry->children_flagged)
            for (entry = entry->children; entry != 0; entry = entry->next)
                entry->object->flags |= 0x4000000;
    }
    return entry;
}
#pragma code_seg()

#undef data_00491c10
#undef data_0047770c
#undef data_00474c40
#undef data_004776e0
#undef data_00477704
#undef data_00477834
#undef data_00477838
#undef data_0047783c
#undef data_00476f78
#undef data_00491fc4
#undef data_00491fb8
#undef data_00492590
