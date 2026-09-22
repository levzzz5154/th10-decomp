#include <stddef.h>

// 0x0041C850..0x0041C87B: release score records whose type is not one.
//
// Ghidra identifies an internal receiver in EAX, a list head at +0x18, and
// a virtual release slot at vtable +0x14. The schema-2 proposal supplies the
// native compiler context for this private entry convention.
struct ScoreCleanupNode_0041c850 {
    virtual void unused_00() = 0;
    virtual void unused_04() = 0;
    virtual void unused_08() = 0;
    virtual void unused_0c() = 0;
    virtual void unused_10() = 0;
    virtual void Release(int value) = 0;

    unsigned char reserved_004[4];
    ScoreCleanupNode_0041c850* next_008;
    int kind_00c;
};

struct ScoreCleanupOwner_0041c850 {
    unsigned char reserved_000[0x18];
    ScoreCleanupNode_0041c850* records_018;

    __declspec(noinline) int Cleanup(int value);
};

typedef char ScoreCleanupNode_0041c850_offsets[
    (offsetof(ScoreCleanupNode_0041c850, next_008) == 0x08 &&
     offsetof(ScoreCleanupNode_0041c850, kind_00c) == 0x0c) ? 1 : -1];

#pragma code_seg(".text$01cleanup")
int ScoreCleanupOwner_0041c850::Cleanup(int value) {
    ScoreCleanupNode_0041c850* node = records_018;
    while (node != 0) {
        ScoreCleanupNode_0041c850* next = node->next_008;
        if (node->kind_00c != 1)
            node->Release(value);
        node = next;
    }
    return 1;
}
#pragma code_seg()
