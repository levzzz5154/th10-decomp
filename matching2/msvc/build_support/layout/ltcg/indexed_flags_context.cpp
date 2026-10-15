#include "../../../src/core/zunlib/indexed_flags.cpp"
#pragma code_seg(".text$05context")
extern "C" __declspec(noinline) int __stdcall IndexedFlagsContext(const signed char* table, unsigned short* output, short* indices, unsigned short bit, unsigned int mask, int count) {
 int result=0;
 while(count--) {
  result += ReadSignedByteFlag(*indices,table,output,bit);
  result += ReadSignedMaskFlag(*indices,mask,output,bit);
  ++indices;
 }
 return result;
}
#pragma code_seg()
