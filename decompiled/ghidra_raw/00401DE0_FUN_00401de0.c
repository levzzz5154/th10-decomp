/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00401DE0
 * Tracking name: FUN_00401de0
 * Ghidra name: FUN_00401de0
 * Tracked span: 528 bytes
 */


void __fastcall FUN_00401de0(undefined4 param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  undefined4 *puVar6;
  
  uVar1 = param_2[0xd0];
  uVar2 = param_2[0xd1];
  uVar3 = param_2[0xd2];
  uVar4 = param_2[8];
  puVar6 = param_2;
  for (iVar5 = 0xeb; iVar5 != 0; iVar5 = iVar5 + -1) {
    *puVar6 = 0;
    puVar6 = puVar6 + 1;
  }
  param_2[0xd0] = uVar1;
  param_2[0xd1] = uVar2;
  param_2[8] = uVar4;
  param_2[0xd2] = uVar3;
  param_2[0xbf] = 0xffffffff;
  param_2[0xf] = 0x3f800000;
  param_2[0x10] = 0x3f800000;
  param_2[0x9d] = 0;
  param_2[0x9c] = 0;
  param_2[0x9b] = 0;
  param_2[0x9a] = 0;
  param_2[0x98] = 0;
  param_2[0x97] = 0;
  param_2[0x96] = 0;
  param_2[0x95] = 0;
  param_2[0x93] = 0;
  param_2[0x92] = 0;
  param_2[0x91] = 0;
  param_2[0x90] = 0;
  param_2[0x9e] = 0x3f800000;
  param_2[0x99] = 0x3f800000;
  param_2[0x94] = 0x3f800000;
  param_2[0x8f] = 0x3f800000;
  *(undefined2 *)(param_2 + 0xd7) = 7;
  param_2[0x18] = 0;
  param_2[0x17] = 0xfff0bdc1;
  param_2[0x19] = 0;
  param_2[0x2d] = 0;
  param_2[0x40] = 0;
  param_2[0x4b] = 0;
  param_2[0x5e] = 0;
  param_2[0x6d] = 0;
  param_2[0x80] = 0;
  param_2[0x8b] = 0;
  param_2[1] = param_2;
  param_2[2] = 0;
  param_2[3] = 0;
  param_2[4] = param_2;
  param_2[5] = 0;
  param_2[6] = 0;
  return;
}

