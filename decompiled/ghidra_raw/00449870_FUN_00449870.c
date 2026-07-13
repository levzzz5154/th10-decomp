/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00449870
 * Tracking name: FUN_00449870
 * Ghidra name: FUN_00449870
 * Tracked span: 224 bytes
 */


void FUN_00449870(undefined4 *param_1,int param_2)

{
  param_1[0xd0] = 0;
  param_1[0xd1] = 0;
  param_1[0xd2] = 0;
  param_1[0xcd] = 0;
  param_1[0xce] = 0;
  param_1[0xcf] = 0;
  param_1[0xd3] = 0;
  param_1[0xd4] = 0;
  param_1[0xd7] = param_1[0xd7] | 0x40000000;
  *(short *)((int)param_1 + 0x38a) = (short)param_2;
  param_1[0xd5] = 0;
  *(undefined1 *)((int)param_1 + 0x3a1) = 0x10;
  *(undefined1 *)(param_1 + 0xe8) = 0x10;
  FUN_0043e7e0(param_2,param_1);
  return;
}

