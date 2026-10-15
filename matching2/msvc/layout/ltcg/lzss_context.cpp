// Compiler context only; never selected as recovered game code. The direct
// call keeps the stand-alone Lzss_InitTree, which retail also kept although
// every real use of it is inlined.
#include "../../src/pack/resfile/lzss.cpp"

#pragma inline_depth(0)
#pragma code_seg(".text$lzss18_context")
extern "C" int __stdcall LzssCompilerContext(const unsigned char* in, int inSize, int* outSize, int node) {
    Lzss_InitTree(node);
    return (int)Lzss_Compress(in, inSize, outSize);
}
#pragma code_seg()
#pragma inline_depth()
