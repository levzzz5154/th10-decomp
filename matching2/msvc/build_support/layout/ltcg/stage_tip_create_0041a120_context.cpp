// Compiler context only; never selected as recovered game code.
// It calls the urgent tip the way the spell timeout at 0x004269D0 does: the
// manager loaded from its global, a literal text and a position inside the
// caller's object.
#include "../../../src/game/hint/hint_data_create.cpp"

extern "C" Hint* g_hint;

struct HintContextOwner {
    unsigned char reserved_000[0x3C0];
    HintDataPosition position;
};

#pragma code_seg(".text$05context")
extern "C" __declspec(noinline) int __stdcall HintDataCreateCompilerContext(
        HintContextOwner* owner, int* gate) {
    if (gate[4] != 1)
        HintData_CreateUrgent_00424650(g_hint, "tip", &owner->position);
    return gate[0];
}
#pragma code_seg()
