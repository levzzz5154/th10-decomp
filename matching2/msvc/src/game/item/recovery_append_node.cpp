#include <stddef.h>

struct RecoveryNode {
    unsigned int reserved_000;
    RecoveryNode* next_004;
    RecoveryNode* prev_008;
    __declspec(noinline) void Append(RecoveryNode* node);
};

#pragma code_seg(".text$01accessor")
void RecoveryNode::Append(RecoveryNode* node) {
    RecoveryNode* tail = this;
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
