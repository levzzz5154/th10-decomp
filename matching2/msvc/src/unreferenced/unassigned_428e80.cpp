// 0x00428e80..0x00428E8E (14 bytes): address of the gauge slot array field at +0x32E4.
//
// Retail multiplies the index by 0x98 and adds it to this + 0x32E4:
//
//   imul eax,98h
//   lea  eax,[eax+ecx+32E4h]
//   ret
//
// so the index arrives in EAX and the state in ECX, the two-register internal
// convention the whole-program link-time code generator chose for this leaf.
// The siblings 0x00428E70, 0x00428E80, 0x00428E90 and 0x00427E40 walk the same
// 0x98-byte stride over the same state, which is the gauge slot array the
// recovered sibling 0x00428E10 (src/game/player/fun.cpp) publishes
// into: its per-slot fields sit at +0x00, +0x08, +0x10 and +0x18 of each record.
//
// Plain C++ cannot name EAX, so the body is compiled in the native-LTCG
// cluster build_support/layout/ltcg/gauge_slot_428e80.json, whose synthetic caller keeps the
// state in ECX and the index in EAX.

struct GaugeSlot3 {
    unsigned char unknown[0x98];
};

struct GaugeState4 {
    unsigned char unknown_0000[0x32E4];
    GaugeSlot3 field;                // +0x32E4

    __declspec(noinline) GaugeSlot3* SlotAt(int index);
};

#pragma code_seg(".text$01slot")
GaugeSlot3* GaugeState4::SlotAt(int index) {
    return &field + index;
}
#pragma code_seg()
