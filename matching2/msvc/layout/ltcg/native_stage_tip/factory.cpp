#include "stage_tip.hpp"
#pragma code_seg(".text$a04factory")
__declspec(noinline) Hint* __cdecl Hint_Create() {
    Hint* block = new Hint;
    Hint* manager;
    if (block)
        manager = block->InitializeLayout();
    else
        manager = 0;
    if (Hint_Initialize(manager)) {
        if (manager) {
            asm_FUN_00418ee0_00418ee0(manager);
            entry_free_004524a1(manager);
        }
        return 0;
    }
    return manager;
}
#pragma code_seg()
