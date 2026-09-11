// 0x0042AC60 - unlink the list node stored at +0x1C from its neighbours and
// clear both list slots. The node's +0x04 link mirrors the list head and its
// +0x08 link mirrors the list tail, so patching the surviving ends keeps the
// doubly linked list consistent before both slots are zeroed.
struct Object0042ac60;

struct ListNode0042ac60 {
    unsigned char pad_000[0x04];
    ListNode0042ac60* head_link;  // +0x04, mirrors the owner's list head
    ListNode0042ac60* tail_link;  // +0x08, mirrors the owner's list tail
};

struct Object0042ac60 {
    unsigned char pad_000[0x1C];
    ListNode0042ac60* head;  // +0x1C
    ListNode0042ac60* tail;  // +0x20

    void UnlinkNode();
};

void Object0042ac60::UnlinkNode() {
    ListNode0042ac60* node = head;
    if (node)
        node->tail_link = tail;
    ListNode0042ac60* end = tail;
    if (end)
        end->head_link = head;
    head = 0;
    tail = 0;
}
