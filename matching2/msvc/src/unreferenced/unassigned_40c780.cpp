// 0x0040C780..0x0040C7AE: release the node list owned by the object at +0x1034.
//
// The body publishes the released method table over the object's +0x0000 word
// and then walks the list, releasing each node's payload before the node
// itself. It is the non-deleting half of the pair whose deleting form is
// 0x0040C7B0; the receiver arrives in ECX and no result is used.
void __cdecl operator delete(void* memory);

struct ListNode0040c780 {
    void* payload;                 // +0x00
    ListNode0040c780* next_node;   // +0x04
};

struct Object0040c780 {
    void* vtable;                       // +0x0000
    unsigned char pad_004[0x1034 - 4];
    ListNode0040c780* first_node;       // +0x1034

    void Release();
};

void Object0040c780::Release() {
    vtable = (void*)0x0046D0D8;
    ListNode0040c780* node = first_node;
    while (node) {
        ListNode0040c780* next_node = node->next_node;
        operator delete(node->payload);
        operator delete(node);
        node = next_node;
    }
}
