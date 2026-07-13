/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00405B60
 * Tracking name: FUN_00405b60
 * Ghidra name: FUN_00405b60
 * Tracked span: 128 bytes
 */


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

