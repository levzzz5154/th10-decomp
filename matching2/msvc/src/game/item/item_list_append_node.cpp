// 0x0041AB10: ItemListNode::Append
#include <stddef.h>

struct ItemListNode {
    unsigned int reserved_000;
    ItemListNode* next_004;
    ItemListNode* prev_008;
    __declspec(noinline) void Append(ItemListNode* node);
};

#pragma code_seg(".text$01accessor")
void ItemListNode::Append(ItemListNode* node) {
    ItemListNode* tail = this;
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
