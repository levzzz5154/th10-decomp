// Variant A: member with the container walk, head cached in a local.
extern "C" void __cdecl crt_free_startup(void* memory);

struct LinkedNode {
    virtual void Slot0();
    virtual void Slot1();
    virtual void Slot2();
    virtual void Slot3();
    virtual void Release();
    virtual void Slot5(void* arg);

    LinkedNode* prev;
    LinkedNode* next;
    int state;
};

struct ScoreChain {
    unsigned char reserved_000[0x18];
    LinkedNode* head;

    __declspec(noinline) void ReleaseChain();
};

#pragma code_seg(".text$01release")
void ScoreChain::ReleaseChain() {
    LinkedNode* node = head;
    while (node != 0) {
        LinkedNode* next = node->next;
        node->Release();
        node->prev->next = node->next;
        if (node->next != 0)
            node->next->prev = node->prev;
        crt_free_startup(node);
        node = next;
    }
}
#pragma code_seg()
