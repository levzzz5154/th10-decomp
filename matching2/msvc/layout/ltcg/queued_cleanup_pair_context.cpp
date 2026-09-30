// Compiler context only; never selected as recovered code.
#include "../../src/render/queued_anm_cleanup.cpp"
#include "queued_cleanup_find_anchor.cpp"
#pragma code_seg(".text$70context")
int __stdcall QueuedCleanupCompilerContext_00421070(QueuedAnmState_00421070** states, int count) {
    for (int index = 0; index < count; ++index) {
        QueuedAnimationCleanup_00421070(states[index]);
        ReleaseAnimationHandles_00421300(states[index]);
    }
    return 0;
}
#pragma code_seg()
