// 0x00427e40..0x00428E7E (14 bytes): address of the gauge slot array field at +0x32DC.
//
// Retail multiplies the index by 0x98 and adds it to this + 0x32DC:
//
//   imul eax,98h
//   lea  eax,[eax+ecx+32DCh]
//   ret
//
// so the index arrives in EAX and the state in ECX, the two-register internal
// convention the whole-program link-time code generator chose for this leaf.
// The siblings 0x00427E40, 0x00428E80, 0x00428E90 and 0x00427E40 walk the same
// 0x98-byte stride over the same state, which is the gauge slot array the
// recovered sibling 0x00428E10 (src/game/player/fun_00428e10_00428e10.cpp) publishes
// into: its per-slot fields sit at +0x00, +0x08, +0x10 and +0x18 of each record.
//
// Plain C++ cannot name EAX, so the body is compiled in the native-LTCG
// cluster layout/ltcg/gauge_slot_00427e40.json, whose synthetic caller keeps the
// state in ECX and the index in EAX.

struct GaugeSlot_00427e40 {
    unsigned char unknown[0x98];
};

struct GaugeState_00427e40 {
    unsigned char unknown_0000[0x32DC];
    GaugeSlot_00427e40 field;                // +0x32DC

    __declspec(noinline) GaugeSlot_00427e40* SlotAt(int index);
};

#pragma code_seg(".text$01slot")
GaugeSlot_00427e40* GaugeState_00427e40::SlotAt(int index) {
    return &field + index;
}
#pragma code_seg()
