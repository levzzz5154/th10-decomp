// 0x0040C7B0 - scalar deleting destructor for the node-list owner: publish the
// base vtable, release every list node (its payload first, then the node), then
// release the object itself when the caller asks for it. The delete flag is the
// first stack argument of this __thiscall body.
void __cdecl operator delete(void* memory);

struct ListNode0040c7b0 {
    void* payload;                 // +0x00
    ListNode0040c7b0* next_node;   // +0x04
};

struct Object0040c7b0 {
    void* vtable;                       // +0x0000
    unsigned char pad_004[0x1034 - 4];
    ListNode0040c7b0* first_node;       // +0x1034

    void* DeletingDestructor(unsigned char delete_flag);
};

void* Object0040c7b0::DeletingDestructor(unsigned char delete_flag) {
    vtable = (void*)0x0046D0D8;
    ListNode0040c7b0* node = first_node;
    while (node) {
        ListNode0040c7b0* next_node = node->next_node;
        operator delete(node->payload);
        operator delete(node);
        node = next_node;
    }
    if (delete_flag & 1)
        operator delete(this);
    return this;
}
