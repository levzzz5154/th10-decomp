// 0x0042A8A0..0x0042A8F4: Recovery_AppendPacket
//
// The retail routine is a native-LTCG member call: the receiver arrives in
// EAX, the first short in DX, and the remaining two shorts are stack-owned.
// The cursor is volatile because the original compiler reloads +0x5460 for
// each packet field before advancing it.
#include <stddef.h>

struct RecoveryPacketState_0042a8a0 {
    unsigned char reserved_0000[0x5460];
    unsigned char* volatile cursor_5460;

    __declspec(noinline) int AppendPacket(short first, short second, short third);
};

typedef char RecoveryPacketState_cursor_offset_must_be_5460[
    (offsetof(RecoveryPacketState_0042a8a0, cursor_5460) == 0x5460) ? 1 : -1];

#pragma code_seg(".text$01packet")
int RecoveryPacketState_0042a8a0::AppendPacket(short first, short second, short third) {
    unsigned char* cursor = cursor_5460;
    *(volatile unsigned short*)cursor = (unsigned short)first;
    cursor = cursor_5460;
    *(volatile unsigned short*)(cursor + 2) = (unsigned short)second;
    cursor = cursor_5460;
    *(volatile unsigned short*)(cursor + 4) = (unsigned short)third;
    cursor = cursor_5460;
    cursor += 6;
    cursor_5460 = cursor;
    return ((int)(cursor - (unsigned char*)this) / 6) >= 0xe10;
}
#pragma code_seg()
