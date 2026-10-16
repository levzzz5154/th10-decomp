#include "../../../src/unreferenced/holder_copy.cpp"
#pragma code_seg(".text$09context")
extern "C" int __stdcall HolderCopyCompilerContext(void** dests, void** sources, int count) {
    for (int index = 0; index < count; ++index)
        ((Triple4*)sources[index])->CopyTo((Holder4*)dests[index]);
    return 0;
}
#pragma code_seg()
