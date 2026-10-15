// Compiler context only; never selected as recovered game code.
#include "../../../src/game/mother/vector3_cross.cpp"
#pragma code_seg(".text$03context")
void __stdcall VectorCrossCompilerContext(CrossVector* results, const CrossVector* left, const CrossVector* right, int count) {
 for(int i=0;i<count;++i) VectorCross(&results[i],&left[i],&right[i]);
}
#pragma code_seg()
