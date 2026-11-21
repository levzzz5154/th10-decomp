// 0x00405500 (81 bytes): CardCaptureFlags::ClearExpiredFlags — called on g_card
// when a bomb starts: once 60 frames have elapsed in the active spellcard,
// drop bit 1 (capture-bonus flag) from the card's flags and seven of its eight
// owned entities (slot 2 keeps it), and clear pending_state.
//
// Native LTCG passes the card pointer in EAX.
struct CardOwnedEntity {
    unsigned char reserved_000[0x378];
    unsigned int flags;                                // +0x378
    unsigned char reserved_37c[0x3AC - 0x37C];
};

struct CardCaptureFlags {
    unsigned char reserved_0000[0x75C];
    CardOwnedEntity entities[8];            // +0x75C
    unsigned char reserved_24bc[0x3738 - 0x24BC];
    int elapsed_frames;                                // +0x3738
    unsigned char reserved_373c[0x378C - 0x373C];
    unsigned int flags;                                // +0x378C
    int pending_state;                               // +0x3790

    __declspec(noinline) void ClearExpiredFlags();
};

#pragma code_seg(".text$01flags")
void CardCaptureFlags::ClearExpiredFlags() {
    if (elapsed_frames >= 60) {
        pending_state = 0;
        flags &= ~2u;
        for (int i = 0; i < 8; ++i)
            if (i != 2)
                entities[i].flags &= ~2u;
    }
}
#pragma code_seg()
