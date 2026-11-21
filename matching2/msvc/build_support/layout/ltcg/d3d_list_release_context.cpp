// Compiler context only; never selected as recovered game code.
#include "../../../src/core/zunlib/func_ctrl_release_list.cpp"
#pragma code_seg(".text$03context")
void __stdcall ResourceListReleaseContext(FuncCtrlTaskList** lists,int count,FuncCtrlTaskListOwner owner) {
 while(count--) (*lists++)->ReleaseTaskList(owner);
}
#pragma code_seg()
