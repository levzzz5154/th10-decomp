// Compiler context only; never selected as recovered game code.
#include "../../src/core/zunlib/d3_d_resource_list_release_resources_00449e50.cpp"
#pragma code_seg(".text$03context")
void __stdcall ResourceListReleaseContext(ResourceList_00449e50** lists,int count,ResourceListOwner_00449e50 owner) {
 while(count--) (*lists++)->Release(owner);
}
#pragma code_seg()
