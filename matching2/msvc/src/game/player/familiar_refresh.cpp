// Equivalent recovery of the familiar refresh (0x00426F70); the readable
// model is the LTCG cluster source included below. One commutative add in
// the third shot-type column loads its operands in the other order (recorded
// in build_support/layout/equivalent/familiar_refresh_00426f70.json).
#include "../../../build_support/contexts/legacy/game/familiar_refresh_00426f70.cpp"

// Compiler context only; never selected as recovered game code. The game
// counters are one object whose address is handed around elsewhere, which is
// what makes the refresh reload the character and shot type after stores.
#pragma code_seg(".text$02entry")
extern "C" void* __stdcall FamiliarRefreshEscape() {
    return &data_00474c44;
}
#pragma code_seg()
