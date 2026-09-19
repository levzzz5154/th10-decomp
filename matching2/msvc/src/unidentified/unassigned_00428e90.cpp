// 0x00428e90..0x00428E9E (14 bytes): address of the gauge slot array field at +0x32EC.
//
// Retail multiplies the index by 0x98 and adds it to this + 0x32EC:
//
//   imul eax,98h
//   lea  eax,[eax+ecx+32ECh]
//   ret
//
// so the index arrives in EAX and the state in ECX, the two-register internal
// convention the whole-program link-time code generator chose for this leaf.
// The siblings 0x00428E70, 0x00428E80, 0x00428E90 and 0x00427E40 walk the same
// 0x98-byte stride over the same state, which is the gauge slot array the
// recovered sibling 0x00428E10 (src/game/fun_00428e10_00428e10.cpp) publishes
// into: its per-slot fields sit at +0x00, +0x08, +0x10 and +0x18 of each record.
//
// Plain C++ cannot name EAX, so the body is compiled in the native-LTCG
// cluster layout/ltcg/gauge_slot_00428e90.json, whose synthetic caller keeps the
// state in ECX and the index in EAX.

struct GaugeSlot_00428e90 {
    unsigned char unknown[0x98];
};

struct GaugeState_00428e90 {
    unsigned char unknown_0000[0x32EC];
    GaugeSlot_00428e90 field;                // +0x32EC

    __declspec(noinline) GaugeSlot_00428e90* SlotAt(int index);
};

#pragma code_seg(".text$01slot")
GaugeSlot_00428e90* GaugeState_00428e90::SlotAt(int index) {
    return &field + index;
}
#pragma code_seg()
