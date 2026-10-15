// Compiler context only; never selected as recovered game code.
#include "../../src/game/mother/vector3_cross.cpp"
#pragma code_seg(".text$03context")
void __stdcall VectorCrossCompilerContext(CrossVector_00421b90* results, const CrossVector_00421b90* left, const CrossVector_00421b90* right, int count) {
 for(int i=0;i<count;++i) VectorCross_00421b90(&results[i],&left[i],&right[i]);
}
#pragma code_seg()
