/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00428E10
 * Tracking name: FUN_00428e10
 * Ghidra name: FUN_00428e10
 * Tracked span: 336 bytes
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_00428e10(undefined4 *param_1)

{
  int in_EAX;
  
  *(undefined4 *)(in_EAX + 0x3cc) = *param_1;
  *(undefined4 *)(in_EAX + 0x3d0) = param_1[1];
  *(float *)(in_EAX + 0x3c0) = (float)*(int *)(in_EAX + 0x3cc) * _DAT_00470b00;
  *(float *)(in_EAX + 0x3c4) = (float)*(int *)(in_EAX + 0x3d0) * _DAT_00470b00;
  *(undefined4 *)(in_EAX + 0x332c) = 1;
  *(undefined4 *)(in_EAX + 0x33c4) = 1;
  *(undefined4 *)(in_EAX + 0x345c) = 1;
  *(undefined4 *)(in_EAX + 0x34f4) = 1;
  return;
}

