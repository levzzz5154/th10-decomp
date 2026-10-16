// Compiler context only; never selected as recovered game code.
#include "../../../src/game/player/cell_pair_scale.cpp"

#pragma code_seg(".text$03context")
int __stdcall CellPairScaleCompilerContext(CellPair* item, int scale) {
    CellPair pair = *item * scale;
    return pair.first + pair.second;
}
#pragma code_seg()
