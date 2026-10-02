// Complete player flag expiry at 0x00405500; slot 2 retains its pending bit.
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
    unsigned char reserved_373c[0x3788 - 0x373C];
    int animation_state;                                // +0x3788
    unsigned int flags;                                // +0x378C
    int pending_state;                               // +0x3790

    __declspec(noinline) void ClearExpiredFlags();
};

#pragma code_seg(".text$a03flags")
void PlayerFlags_00405500::ClearExpiredFlags() {
    if (elapsed_frames >= 60) {
        pending_state = 0;
        flags &= ~2u;
        PlayerOwnedEntity_00405500* entity = entities;
        for (int i = 0; i < 8; ++i, ++entity)
            if (i != 2)
                entity->flags &= ~2u;
    }
}
#pragma code_seg()
