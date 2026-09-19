// 0x004493C0..0x004493DA: find a node by key and hand back its +0x340 block.
//
// The key arrives on the stack while the two leading registers are forwarded to
// the manager lookup unchanged, so the model keeps them as the __fastcall
// register pair; the callee uses the argument order the animation-manager
// family uses. The if/else with a single result is what puts the null arm out
// of line ahead of the caller's cleanup, as retail has it.
struct AnimationNode_004493c0;

extern "C" AnimationNode_004493c0* __fastcall AnimationManager_Find_004491c0(
    void* value, void* manager, int unused);

extern "C" AnimationNode_004493c0* __fastcall AnimationManager_FindBlock_004493c0(
    void* value, void* manager, int key) {
    AnimationNode_004493c0* node =
        AnimationManager_Find_004491c0(value, manager, key);
    AnimationNode_004493c0* block;
    if (node != 0)
        block = (AnimationNode_004493c0*)((char*)node + 0x340);
    else
        block = 0;
    return block;
}
