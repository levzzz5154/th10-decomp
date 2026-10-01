#ifndef TH10_BULLET_RESET_ANCHOR_HPP
#define TH10_BULLET_RESET_ANCHOR_HPP

// 0x00405BE0..0x00405C7D: clear the mode and reset both scheduler timers.
// Native LTCG supplies the retail EAX receiver. The shared tail pointers keep
// each timer reset together before the next timer flag is read.
extern "C" float data_00476f78;

struct Player_00405be0 {
    unsigned char unknown_0000[0x3F8];
    int link_1_previous;       // +0x3F8
    int link_1_current;        // +0x3FC
    int link_1_elapsed;        // +0x400
    float* link_1_speed;       // +0x404
    unsigned int link_1_flags; // +0x408
    int link_2_previous;       // +0x40C
    int link_2_current;        // +0x410
    int link_2_elapsed;        // +0x414
    float* link_2_speed;       // +0x418
    unsigned int link_2_flags; // +0x41C
    unsigned char unknown_0420[0x26];
    unsigned short marker; // +0x446

    __declspec(noinline) void ResetSchedulerLinks();
};

#pragma code_seg(".text$00breset")
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

#endif
