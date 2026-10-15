// Compiler context only; never selected as recovered game code.
#include "../../src/unreferenced/unassigned_00421c70.cpp"
// The existing SprtCtrl::Find dependency is emitted here as a
// non-recovered ABI anchor; its maintained source belongs to another cluster.

struct AnimationEntry {
    AnimationEntry* object;
    AnimationEntry* next;
    unsigned char reserved_08[0x0C];
    AnimationEntry* children;
    int children_flagged;
    unsigned char reserved_1c[0x340];
    unsigned int flags;
};

struct AnimationLookupContext {
    unsigned char reserved[0x72DAD4];
    AnimationEntry* primary_bucket;
    int reserved_2;
    AnimationEntry* secondary_bucket;
};

struct AnimationScriptId {
    int value;
};

class SprtCtrl {
public:
    void* __fastcall Find(AnimationLookupContext* context,
                           AnimationScriptId id);
};

#pragma code_seg(".text$50find")
__declspec(noinline) void* __fastcall SprtCtrl::Find(
        AnimationLookupContext* context, AnimationScriptId id) {
    if (!id.value)
        return 0;
    for (AnimationEntry* node = context->primary_bucket;
         node != 0; node = node->next)
        if (*(int*)node->object == id.value)
            return node->object;
    for (AnimationEntry* node = context->secondary_bucket;
         node != 0; node = node->next)
        if (*(int*)node->object == id.value)
            return node->object;
    return 0;
}
#pragma code_seg()

struct AnimationTable_0042c7e0;
extern "C" int AnimationTable_HasSlot_0042c7e0(
        AnimationTable_0042c7e0* table, int index);

#pragma code_seg(".text$20context")
extern "C" __declspec(noinline) int MiscPrivateAbiWave22Context(
        SlotLockTable_00421c70** locks, int* slots,
        AnimationTable_0042c7e0** tables, int count) {
    int result = 0;
    for (int index = 0; index < count; ++index) {
        SlotLockTable_EnterRetail_00421c70(slots[index], locks[index]);
        result += AnimationTable_HasSlot_0042c7e0(tables[index], slots[index]);
    }
    return result;
}
#pragma code_seg()
