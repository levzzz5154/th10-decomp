/* Raw Ghidra reference; not compilable reconstruction. Address: 00413200 */

void __fastcall InsertScoreListNode(int param_1)

{
  int in_EAX;
  
  if (*(int *)(param_1 + 4) != 0) {
    *(int *)(in_EAX + 4) = *(int *)(param_1 + 4);
    *(int *)(*(int *)(param_1 + 4) + 8) = in_EAX;
  }
  *(int *)(param_1 + 4) = in_EAX;
  *(int *)(in_EAX + 8) = param_1;
  return;
}

