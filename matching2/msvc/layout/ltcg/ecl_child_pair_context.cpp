#include "../../src/script/ecl_child_pair.cpp"
#pragma code_seg(".text$11context")
extern "C" __declspec(noinline) int __stdcall EclChildPairContext(EclCompleteChild** sources, int id, int index, int count) {
 int result=0;
 while(count--) {
  EclCompleteChild* source=*sources++;
  EclChildOwner* owner=(EclChildOwner*)source->stack.context;
  result += EclSpawnChild(owner,id,index);
  result += EclStartChild(source,source,index);
 }
 return result;
}
#pragma code_seg()
