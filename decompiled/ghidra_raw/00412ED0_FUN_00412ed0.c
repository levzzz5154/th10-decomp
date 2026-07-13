/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00412ED0
 * Tracking name: FUN_00412ed0
 * Ghidra name: FUN_00412ed0
 * Tracked span: 288 bytes
 */


void __fastcall FUN_00412ed0(int param_1)

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

