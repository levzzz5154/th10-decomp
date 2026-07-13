/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00405860
 * Tracking name: FUN_00405860
 * Ghidra name: FUN_00405860
 * Tracked span: 400 bytes
 */


undefined4 FUN_00405860(int param_1)

{
  undefined4 *puVar1;
  int iVar2;
  
  if (*(int *)(param_1 + 0x28) != 0) {
    return 0xffffffff;
  }
  *(undefined4 *)(param_1 + 0x28) = 1;
  if ((*(uint *)(param_1 + 0x24) & 1) == 0) {
    *(undefined4 *)(param_1 + 0x18) = 0;
    *(undefined4 *)(param_1 + 0x14) = 0xfff0bdc1;
    *(undefined4 *)(param_1 + 0x1c) = 0;
    *(undefined4 **)(param_1 + 0x20) = &DAT_00476f78;
    *(uint *)(param_1 + 0x24) = *(uint *)(param_1 + 0x24) | 1;
  }
  iVar2 = DAT_00477834;
  *(undefined4 *)(param_1 + 0x18) = 0;
  *(undefined4 *)(param_1 + 0x1c) = 0;
  *(undefined4 *)(param_1 + 0x14) = 0xffffffff;
  *(undefined4 *)(param_1 + 0x3c) = 0x42000000;
  *(undefined4 *)(param_1 + 0x40) = 0x40800000;
  *(undefined4 *)(param_1 + 0x30) = *(undefined4 *)(iVar2 + 0x3c0);
  *(undefined4 *)(param_1 + 0x34) = *(undefined4 *)(iVar2 + 0x3c4);
  *(undefined4 *)(param_1 + 0x38) = *(undefined4 *)(iVar2 + 0x3c8);
  puVar1 = (undefined4 *)FUN_00448db0(*(undefined2 **)(DAT_004776f0 + 0x3e0b50));
  *(undefined4 *)(param_1 + 0x2c) = *puVar1;
  FUN_0043dd10();
  iVar2 = (int)DAT_00474c48 / 0x14;
  FUN_004054b0(iVar2,iVar2,(((int)DAT_00474c48 % 0x14) * 100) / 0x14);
  iVar2 = DAT_004776f4;
  FUN_00405500();
  DAT_00474c98 = DAT_00474c98 + -0x80;
  if (DAT_00474c98 < 0x401) {
    if (DAT_00474c98 < -0x400) {
      DAT_00474c98 = -0x400;
    }
  }
  else {
    DAT_00474c98 = 0x400;
  }
  if (((*(byte *)(iVar2 + 0x378c) & 1) != 0) && (0x3b < *(int *)(iVar2 + 0x3738))) {
    *(undefined4 *)(param_1 + 0x44) = 1;
    return 0;
  }
  *(undefined4 *)(param_1 + 0x44) = 0;
  return 0;
}

