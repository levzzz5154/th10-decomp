// Compiler context only; never selected as recovered game code.
#include "../../../src/game/title/anm_vm_pos_interp.cpp"

#pragma code_seg(".text$03context")
int __stdcall StageTextCompilerContext(AnmVmPosInterp** records, int count,
                                       const AnmVmPosInterpVec* local) {
    AnmVmPosInterp** cursor = records;
    while (count--) {
        AnmVmPosInterp* record = *cursor++;
        record->StartPositionInterp(&record->base_position, local, 4, 0);
    }
    return 0;
}
#pragma code_seg()
