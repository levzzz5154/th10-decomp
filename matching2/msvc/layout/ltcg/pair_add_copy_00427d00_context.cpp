// Synthetic compiler context; this is not recovered game code.
#include "../../src/unidentified/unassigned_00427d00.cpp"

#pragma code_seg(".text$03context")
extern "C" __declspec(noinline) int __stdcall PairAddCopyCompilerContext(
        Pair_00427d00* outputs,
        Pair_00427d00* targets,
        const Pair_00427d00* deltas,
        int count) {
    for (int index = 0; index < count; ++index) {
        outputs[index] = targets[index].AddAndCopy(deltas[index]);
    }
    return 0;
}
#pragma code_seg()
