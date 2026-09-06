/* Raw Ghidra reference; not compilable reconstruction. Address: 0041AB10 */

void __fastcall AppendLinkedNode(undefined4 param_1,int param_2)

{
  int *piVar1;
  int iVar2;
  int in_EAX;
  
  piVar1 = (int *)(in_EAX + 4);
  iVar2 = *piVar1;
  while (iVar2 != 0) {
    in_EAX = *piVar1;
    piVar1 = (int *)(in_EAX + 4);
    iVar2 = *(int *)(in_EAX + 4);
  }
  if (*(int *)(in_EAX + 4) != 0) {
    *(int *)(param_2 + 4) = *(int *)(in_EAX + 4);
    *(int *)(*(int *)(in_EAX + 4) + 8) = param_2;
  }
  *(int *)(in_EAX + 4) = param_2;
  *(int *)(param_2 + 8) = in_EAX;
  return;
}

