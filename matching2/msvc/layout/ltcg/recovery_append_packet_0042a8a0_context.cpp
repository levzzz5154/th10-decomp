// Compiler context only; never selected as recovered game code.
#include "../../src/game/recovery_append_packet_0042a8a0.cpp"

#pragma code_seg(".text$03context")
extern "C" __declspec(noinline) int __stdcall RecoveryAppendPacketContext(
        RecoveryPacketState_0042a8a0** states, int count,
        short first, short second, short third) {
    int total = 0;
    while (count--)
        total += (*states++)->AppendPacket(first, second, third);
    return total;
}
#pragma code_seg()
