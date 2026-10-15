#include <stddef.h>

struct RecoveryNode_0041ab10 {
    unsigned int reserved_000;
    RecoveryNode_0041ab10* next_004;
    RecoveryNode_0041ab10* prev_008;
    __declspec(noinline) void Append(RecoveryNode_0041ab10* node);
};

#pragma code_seg(".text$01accessor")
void RecoveryNode_0041ab10::Append(RecoveryNode_0041ab10* node) {
    RecoveryNode_0041ab10* tail = this;
    while (tail->next_004 != 0)
        tail = tail->next_004;
    if (tail->next_004 != 0) {
        node->next_004 = tail->next_004;
        tail->next_004->prev_008 = node;
    }
    tail->next_004 = node;
    node->prev_008 = tail;
}
#pragma code_seg()
