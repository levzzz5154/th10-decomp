/* Raw Ghidra reference; not compilable reconstruction. Address: 00405B60 */

void __fastcall FUN_00405b60(int param_1)

{
  int in_EAX;
  int iVar1;
  
  iVar1 = *(int *)(in_EAX + 0x58) + param_1;
  *(int *)(in_EAX + 0x58) = iVar1;
  if (0x400 < iVar1) {
    *(undefined4 *)(in_EAX + 0x58) = 0x400;
    return;
  }
  if (iVar1 < -0x400) {
    *(undefined4 *)(in_EAX + 0x58) = 0xfffffc00;
  }
  return;
}

