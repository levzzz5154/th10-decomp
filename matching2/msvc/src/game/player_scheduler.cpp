// 0x00405BE0..0x00405C7D: reset both player scheduler links.
//
// Retail enters this member with the player record in EAX, a convention no C++
// declaration names, so the body is compiled in the native-LTCG cluster
// layout/ltcg/player_scheduler_links_00405be0.json, whose synthetic caller
// walks an array of records and leaves the receiver in EAX.
//
// Each link is the same previous/current/elapsed/speed/flags timer block the
// score timer (src/game/score_timer_leaves.cpp) and the recovery state
// (src/game/recovery_initialize_timed_state_00423510.cpp) carry: current and
// elapsed are cleared, previous takes the inactive sentinel -1, and while the
// block is not yet running the countdown is armed with 0xFFF0BDC1 and the
// shared float data_00476f78 as its speed before the running bit is raised.
// The low half of the record's scheduler counter at +0x446 is cleared first.
//
// Every write to the record goes through a pointer to the field rather than
// through the member, and the three clearing stores of each link share one
// pointer (`tail`) the same way the pair write in
// src/game/score_timer_leaves.cpp shares one:
//
//  * a direct member store (`marker = 0;`) sinks into the compare slot of the
//    `test cl,1` that follows and is materialised at its use, 45 differing
//    bytes;
//  * with only the leading store behind a pointer, the prologue is exact but
//    the three trailing stores of the first link sink into the second link's
//    compare slot - the second flag load is hoisted above them - 27 differing
//    bytes;
//  * the shared pointer value keeps all three in front of that load: 0.
extern "C" float data_00476f78;

struct Player_00405be0 {
    unsigned char unknown_0000[0x3F8];
    int link_1_previous;         // +0x3F8
    int link_1_current;          // +0x3FC
    int link_1_elapsed;          // +0x400
    float* link_1_speed;         // +0x404
    unsigned int link_1_flags;   // +0x408
    int link_2_previous;         // +0x40C
    int link_2_current;          // +0x410
    int link_2_elapsed;          // +0x414
    float* link_2_speed;         // +0x418
    unsigned int link_2_flags;   // +0x41C
    unsigned char unknown_0420[0x26];
    unsigned short marker;       // +0x446

    __declspec(noinline) void ResetSchedulerLinks();
};

#pragma code_seg(".text$01accessor")
void Player_00405be0::ResetSchedulerLinks() {
    unsigned short* record = &marker;
    record[0] = 0;
    if ((link_1_flags & 1) == 0) {
        link_1_current = 0;
        link_1_previous = 0xFFF0BDC1;
        link_1_elapsed = 0;
        link_1_speed = &data_00476f78;
        link_1_flags |= 1;
    }
    int* tail_1 = &link_1_current;
    tail_1[0] = 0;
    tail_1[1] = 0;
    tail_1[-1] = -1;
    if ((link_2_flags & 1) == 0) {
        link_2_current = 0;
        link_2_previous = 0xFFF0BDC1;
        link_2_elapsed = 0;
        link_2_speed = &data_00476f78;
        link_2_flags |= 1;
    }
    int* tail_2 = &link_2_current;
    tail_2[0] = 0;
    tail_2[1] = 0;
    tail_2[-1] = -1;
}
#pragma code_seg()
