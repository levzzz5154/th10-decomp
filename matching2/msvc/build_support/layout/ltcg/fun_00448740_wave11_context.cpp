// Compiler context and ABI anchor only; none of these bytes enter the image.
#include "../../../src/core/sprtlib/animation_manager_draw_slot14.cpp"

// One node of a render slot's entity list, the shape 0x00448980 walks: the next
// link at +0x1C, the flag word at +0x35C, the per-entity draw callback at
// +0x39C.
struct RenderSlotNode_00448740 {
    unsigned char reserved_000[0x1C];
    RenderSlotNode_00448740* next;          // +0x1C
    unsigned char reserved_020[0x35C - 0x20];
    unsigned int flags;                     // +0x35C
    unsigned char reserved_360[0x39C - 0x360];
    void (__fastcall* on_render)(void*);    // +0x39C
};

// 0x004451C0: the per-node draw call.
extern "C" void __cdecl asm_FUN_004451c0_004451c0(void* object, void* manager);

// 0x00448980's body.  It is compiled only so the whole-program pass can put the
// manager in EDI and the slot index in EAX: its caller is the modelled task and
// no declaration names either register.  The layout's gaps place this section at
// the retail address, so the task's call bakes retail's displacement and needs no
// relocation.  None of these bytes are selected as recovered code.
#pragma code_seg(".text$03bucket")
extern "C" __declspec(noinline) int __cdecl asm_AnimationManager_RenderBucket_00448980(
        SprtCtrlBatchView* manager, int slot) {
    RenderSlotNode_00448740* node = *(RenderSlotNode_00448740**)
        ((unsigned char*)manager + 0x72DB00 + slot * 0x3AC);
    while (node != 0) {
        if ((node->flags & 0x4000000u) == 0) {
            if (node->on_render != 0) {
                node->on_render(node);
            }
            asm_FUN_004451c0_004451c0(node, manager);
        }
        node = node->next;
    }
    return 1;
}
#pragma code_seg()

// Synthetic scheduler dispatch that establishes the task's register convention;
// not recovered game code.
#pragma code_seg(".text$05context")
int __stdcall AnimationSlotTaskContext(SprtCtrlBatchView** managers,
                                       int count) {
    int result = 0;
    for (int index = 0; index < count; ++index) {
        result = managers[index]->ResetOriginAndRenderSlot14();
    }
    return result;
}
#pragma code_seg()
