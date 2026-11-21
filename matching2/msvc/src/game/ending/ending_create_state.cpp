#include "th10/source_views/recovery_leaves_f39a06_0.hpp"
#include "th10/source_views/recovery_leaves_f39a06_1.hpp"
void* Recovery_CreateSmallState2() {
    EndingSmallState* state = new EndingSmallState;
    if (((SmallStateInstallFn)Ending_InitializeState)(state)) {
        if (state) {
            ((SmallStateReleaseFn)Ending_ReleaseState)(state);
            crt_free_startup(state);
        }
        return 0;
    }
    return state;
}
