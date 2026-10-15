// 0x00405500 (81 bytes): once sixty frames have elapsed, drop the "pending"
// bit (bit 1) from the player's flags and from seven of its eight owned
// entities (slot 2 keeps it), and reset the pending state.
//
// Native LTCG passes the player in EAX.
struct PlayerOwnedEntity_00405500 {
    unsigned char reserved_000[0x378];
    unsigned int flags;                                // +0x378
    unsigned char reserved_37c[0x3AC - 0x37C];
};

struct PlayerFlags_00405500 {
    unsigned char reserved_0000[0x75C];
    PlayerOwnedEntity_00405500 entities[8];            // +0x75C
    unsigned char reserved_24bc[0x3738 - 0x24BC];
    int elapsed_frames;                                // +0x3738
    unsigned char reserved_373c[0x378C - 0x373C];
    unsigned int flags;                                // +0x378C
    int pending_state;                               // +0x3790

    __declspec(noinline) void ClearExpiredFlags();
};

#pragma code_seg(".text$01flags")
void PlayerFlags_00405500::ClearExpiredFlags() {
    if (elapsed_frames >= 60) {
        pending_state = 0;
        flags &= ~2u;
        for (int i = 0; i < 8; ++i)
            if (i != 2)
                entities[i].flags &= ~2u;
    }
}
#pragma code_seg()
