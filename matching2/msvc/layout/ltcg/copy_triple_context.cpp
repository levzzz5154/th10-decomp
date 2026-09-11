// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/FUN_00405130_00405130.cpp"

#pragma code_seg(".text$03context")
int __stdcall CopyTripleCompilerContext(TripleWordBlock** blocks, int count, TripleWordBlock* destination) {
    TripleWordBlock** cursor = blocks;
    while (count--) {
        TripleWordBlock* block = *cursor++;
        destination->Assign(*block);
        destination->Assign(*block);
    }
    return 0;
}
#pragma code_seg()
