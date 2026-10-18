// Compiler context only; the run-selection words belong to an escaping state object.
#include "../../../src/game/pause/result_rows.cpp"
#pragma code_seg(".text$00context")
extern "C" void __stdcall ResultRowsSelectionEscape(void** addresses) {
    addresses[0] = &data_00474c68_shot;
    addresses[1] = &data_00474c68_char;
}
#pragma code_seg()
