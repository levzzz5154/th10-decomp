// 0x004493C0..0x004493DA: find a node by key and hand back its +0x340 block.
//
// The key arrives on the stack while the two leading registers are forwarded to
// the manager lookup unchanged, so the model keeps them as the __fastcall
// register pair; the callee uses the argument order the animation-manager
// family uses. The if/else with a single result is what puts the null arm out
// of line ahead of the caller's cleanup, as retail has it.
struct AnimationNode7;

extern "C" AnimationNode7* __fastcall AnimationManager_Find(
    void* value, void* manager, int unused);

extern "C" AnimationNode7* __fastcall AnimationManager_FindBlock(
    void* value, void* manager, int key) {
    AnimationNode7* node =
        AnimationManager_Find(value, manager, key);
    AnimationNode7* block;
    if (node != 0)
        block = (AnimationNode7*)((char*)node + 0x340);
    else
        block = 0;
    return block;
}
