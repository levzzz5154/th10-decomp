// Synthetic compiler context; this is not recovered game code.
#include "../../../src/unreferenced/unassigned_427d00.cpp"

#pragma code_seg(".text$03context")
extern "C" __declspec(noinline) int __stdcall PairAddCopyCompilerContext(
        Pair4* outputs,
        Pair4* targets,
        const Pair4* deltas,
        int count) {
    for (int index = 0; index < count; ++index) {
        outputs[index] = targets[index].AddAndCopy(deltas[index]);
    }
    return 0;
}
#pragma code_seg()
