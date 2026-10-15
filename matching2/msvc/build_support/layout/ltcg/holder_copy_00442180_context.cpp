#include "../../../src/unreferenced/holder_copy_00442180.cpp"
#pragma code_seg(".text$09context")
extern "C" int __stdcall HolderCopyCompilerContext(void** dests, void** sources, int count) {
    for (int index = 0; index < count; ++index)
        ((Triple_00442180*)sources[index])->CopyTo((Holder_00442180*)dests[index]);
    return 0;
}
#pragma code_seg()
