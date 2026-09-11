// 0x0041C4E0: drains the intrusive list at +0x18 of `self` unless the global
// frame state is flagged with 4; every entry whose state word is not 1 gets its
// fourth virtual slot invoked. Always reports success. Only touched offsets of
// the host are described.
struct FrameState {
    unsigned char unknown_00[0x58];
    unsigned char flags_58;          // +0x58
};

struct Node {
    virtual void Slot0();            // vtable+0x00
    virtual void Slot1();            // vtable+0x04
    virtual void Slot2();            // vtable+0x08
    virtual void Slot3();            // vtable+0x0C: release/refresh hook

    void* field_04;                  // +0x04
    Node* next;                      // +0x08
    int state;                       // +0x0C
};

struct NodeList {
    unsigned char unknown_00[0x18];
    Node* head;                      // +0x18

    int FUN_0041c4e0_0041c4e0();     // __thiscall: `self` arrives in ECX
};

extern "C" unsigned char data_00477810;

int NodeList::FUN_0041c4e0_0041c4e0() {
    FrameState* state = *(FrameState**)&data_00477810;
    if ((state->flags_58 & 4) == 0) {
        Node* node = head;
        if (node != 0) {
            Node* next;
            do {
                next = node->next;
                if (node->state != 1)
                    node->Slot3();
                node = next;
            } while (next != 0);
        }
    }
    return 1;
}
