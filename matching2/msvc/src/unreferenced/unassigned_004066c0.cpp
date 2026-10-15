// 0x004066C0..0x004066D8: process each of the six list heads at owner + 0x14.
// The structure's exact class and the meanings of its fields are not known.

extern "C" {
float __stdcall Angle_NormalizeSum_0044bc10(float value, float addend);
void __fastcall DispatchAnm_004451c0(void* manager, void* object);
extern void* data_00491c10;
}

struct SlotChainNode_004066c0 {
    unsigned char unknown_000[0x34];
    float field_034;
    unsigned char unknown_038[0x033C - 0x038];
    float field_33C;
    float field_340;
    unsigned int field_344;
    unsigned char unknown_348[0x0364 - 0x0348];
    unsigned int flags_364;
    unsigned char unknown_368[0x03B4 - 0x0368];
    float field_3B4;
    float field_3B8;
    unsigned int field_3BC;
    unsigned char unknown_3C0[0x03E4 - 0x03C0];
    float field_3E4;
    unsigned char unknown_3E8[0x044C - 0x03E8];
    SlotChainNode_004066c0* next_44C;
};

struct SlotChainOwner_004066C0 {
    unsigned char unknown_000[0x14];
    SlotChainNode_004066c0* slot_heads[6];

    __declspec(noinline) int UpdateSlotChain(int slot);
    __declspec(noinline) int UpdateAllSlotChains();
};

// The compiler context can choose the private register ABI seen in retail:
// owner in EAX and slot index in ECX. This helper is an ABI anchor in the
// layout, not an independently recovered/exported function.
#pragma code_seg(".text$03anchor")
__declspec(noinline) int SlotChainOwner_004066C0::UpdateSlotChain(int slot) {
    SlotChainNode_004066c0* node = slot_heads[slot];
    while (node != 0) {
        node->field_33C = node->field_3B4 + 224.0f;
        node->field_340 = node->field_3B8 + 16.0f;
        node->field_344 = node->field_3BC;

        if ((node->flags_364 & 0x08000000u) != 0) {
            node->field_034 = Angle_NormalizeSum_0044bc10(
                node->field_3E4, 1.5707964f);
            node->flags_364 |= 4;
        }

        DispatchAnm_004451c0(data_00491c10,
                             reinterpret_cast<unsigned char*>(node) + 8);
        node = node->next_44C;
    }
    return 1;
}
#pragma code_seg()

// The incoming owner is observed in EDI. The ordinary C++ member signature
// documents the operation; the unrooted LTCG cluster/context models that
// private entry convention without inline assembly.
#pragma code_seg(".text$01run")
__declspec(noinline) int SlotChainOwner_004066C0::UpdateAllSlotChains() {
    for (int slot = 0; slot < 6; ++slot)
        UpdateSlotChain(slot);
    return 1;
}
#pragma code_seg()
