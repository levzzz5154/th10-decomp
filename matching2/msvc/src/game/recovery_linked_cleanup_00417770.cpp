// Variant A: member with the container walk, head cached in a local.
extern "C" void __cdecl entry_free_004524a1(void* memory);

struct LinkedNode_00417770 {
    virtual void Slot0();
    virtual void Slot1();
    virtual void Slot2();
    virtual void Slot3();
    virtual void Release();
    virtual void Slot5(void* arg);

    LinkedNode_00417770* prev;
    LinkedNode_00417770* next;
    int state;
};

struct ScoreChain_00417770 {
    unsigned char reserved_000[0x18];
    LinkedNode_00417770* head;

    __declspec(noinline) void ReleaseChain();
};

#pragma code_seg(".text$01release")
void ScoreChain_00417770::ReleaseChain() {
    LinkedNode_00417770* node = head;
    while (node != 0) {
        LinkedNode_00417770* next = node->next;
        node->Release();
        node->prev->next = node->next;
        if (node->next != 0)
            node->next->prev = node->prev;
        entry_free_004524a1(node);
        node = next;
    }
}
#pragma code_seg()
