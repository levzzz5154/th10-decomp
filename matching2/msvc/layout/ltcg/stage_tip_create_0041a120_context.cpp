// Compiler context only; never selected as recovered game code.
// It calls the urgent tip the way the spell timeout at 0x004269D0 does: the
// manager loaded from its global, a literal text and a position inside the
// caller's object.
#include "../../src/game/hint/stage_tip_create_retail_0041a120.cpp"

extern "C" StageTipManager* data_00477814;

struct StageTipContextOwner {
    unsigned char reserved_000[0x3C0];
    StageTipPosition position;
};

#pragma code_seg(".text$05context")
extern "C" __declspec(noinline) int __stdcall StageTipCreateCompilerContext(
        StageTipContextOwner* owner, int* gate) {
    if (gate[4] != 1)
        StageTip_CreateUrgent_00424650(data_00477814, "tip", &owner->position);
    return gate[0];
}
#pragma code_seg()
