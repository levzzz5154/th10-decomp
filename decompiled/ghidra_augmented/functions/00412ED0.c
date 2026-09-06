/* Raw Ghidra reference; not compilable reconstruction. Address: 00412ED0 */

void __fastcall SetScoreMode(int param_1)

{
  int iVar1;
  int in_EAX;
  
  iVar1 = *(int *)(in_EAX + 0x44);
  *(int *)(in_EAX + 0x44) = param_1;
  if (iVar1 != param_1) {
    *(undefined4 *)(in_EAX + 0x4c) = 0;
  }
  return;
}

