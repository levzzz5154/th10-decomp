#include "th10/source_views/recovery_leaves_f39a06_0.hpp"
#include "th10/source_views/recovery_leaves_f39a06_1.hpp"
void* Recovery_CreateSmallState_0040b940() {
    RecoverySmallState* state = new RecoverySmallState;
    if (((SmallStateInstallFn)asm_FUN_0040b560_0040b560)(state)) {
        if (state) {
            ((SmallStateReleaseFn)asm_FUN_0040b7b0_0040b7b0)(state);
            entry_free_004524a1(state);
        }
        return 0;
    }
    return state;
}
