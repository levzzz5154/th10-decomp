// 0x0040C7B0 - the ECL VM base class's scalar deleting destructor (vtable
// 0x0046D0D8 slot 0x14): publish the base vtable, release every list node (its payload first, then the node), then
// release the object itself when the caller asks for it. The delete flag is the
// first stack argument of this __thiscall body.
void __cdecl operator delete(void* memory);

struct EclVmNode {
    void* payload;                 // +0x00
    EclVmNode* next_node;   // +0x04
};

struct EclVm {
    void* vtable;                       // +0x0000
    unsigned char pad_004[0x1034 - 4];
    EclVmNode* first_node;       // +0x1034

    void* DeletingDestructor(unsigned char delete_flag);
};

void* EclVm::DeletingDestructor(unsigned char delete_flag) {
    vtable = (void*)0x0046D0D8;
    EclVmNode* node = first_node;
    while (node) {
        EclVmNode* next_node = node->next_node;
        operator delete(node->payload);
        operator delete(node);
        node = next_node;
    }
    if (delete_flag & 1)
        operator delete(this);
    return this;
}
