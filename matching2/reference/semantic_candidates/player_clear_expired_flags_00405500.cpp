// Candidate only: 81-byte native-LTCG body retains eleven ECX/EDX differences.
// See recovery_notes/player_clear_flags_00405500_cluster.md.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
struct PlayerFlagEntity_00405500 {
    unsigned char reserved_000[0x378];
    unsigned int flags;
    unsigned char reserved_37c[0x30];
};
struct PlayerFlags_00405500 {
    unsigned char reserved_000[0x75c];
    PlayerFlagEntity_00405500 entities[8];
    unsigned char reserved_24bc[0x127c];
    int elapsedFrames;
    unsigned char reserved_373c[0x50];
    unsigned int flags;
    int pendingState;
    __declspec(noinline) void ClearExpiredFlags();
};
#pragma code_seg(".text$01flags")
void PlayerFlags_00405500::ClearExpiredFlags() {
    if (elapsedFrames < 60) return;
    unsigned int oldFlags = flags;
    pendingState = 0;
    _ReadWriteBarrier();
    flags = oldFlags & ~2u;
    entities[0].flags &= ~2u;
    entities[1].flags &= ~2u;
    entities[3].flags &= ~2u;
    entities[4].flags &= ~2u;
    entities[5].flags &= ~2u;
    entities[6].flags &= ~2u;
    entities[7].flags &= ~2u;
}
#pragma code_seg()
