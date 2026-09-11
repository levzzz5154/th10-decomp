// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/FUN_0040a010_0040a010.cpp"

#pragma code_seg(".text$03context")
int __stdcall f40a010CompilerContext(CallbackPair** pairs, int count) {
    for (int index = 0; index < count; ++index)
        pairs[index]->DetachPairAndFinalize();
    return 0;
}
#pragma code_seg()
