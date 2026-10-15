// 0x0041C4E0: the score display's draw task. Drains the intrusive list at +0x18 of `self` unless the global
// frame state is flagged with 4; every entry whose state word is not 1 gets its
// fourth virtual slot invoked. Always reports success. Only touched offsets of
// the host are described.
struct ScoreFrameState {
    unsigned char unknown_00[0x58];
    unsigned char flags_58;          // +0x58
};

struct ScorePopup {
    virtual void Slot0();            // vtable+0x00
    virtual void Slot1();            // vtable+0x04
    virtual void Slot2();            // vtable+0x08
    virtual void Slot3();            // vtable+0x0C: release/refresh hook

    void* field_04;                  // +0x04
    ScorePopup* next;                      // +0x08
    int state;                       // +0x0C
};

struct ScoreDisplayDrawList {
    unsigned char unknown_00[0x18];
    ScorePopup* head;                      // +0x18

    int OnDraw();     // __thiscall: `self` arrives in ECX
};

extern "C" unsigned char data_00477810;

int ScoreDisplayDrawList::OnDraw() {
    ScoreFrameState* state = *(ScoreFrameState**)&data_00477810;
    if ((state->flags_58 & 4) == 0) {
        ScorePopup* node = head;
        if (node != 0) {
            ScorePopup* next;
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
