// Compiler context only; never selected as recovered game code.
// The array-walking caller is what makes the whole-program pass pick the
// observed retail convention for the 0x0041A050 body: line in EAX, value in
// EBX, key in EDI, with the trim helper at 0x0041A0A0 reached in EAX.
#include "../../src/game/hint/recovery_split_resource_path_0041a050.cpp"

#pragma code_seg(".text$04context")
extern "C" __declspec(noinline) int __stdcall SplitResourcePathCompilerContext(
        char** lines, char** values, char** keys, int count) {
    int total = 0;
    while (count--) {
        total += (int)SplitResourcePath_0041a050(*lines++, *values++, *keys++);
    }
    return total;
}
#pragma code_seg()
