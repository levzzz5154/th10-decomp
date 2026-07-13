/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0040E6A0
 * Tracking name: FUN_0040e6a0
 * Ghidra name: FUN_0040e6a0
 * Tracked span: 208 bytes
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0040e6a0(int param_1)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  float *pfVar4;
  float fVar5;
  ulonglong uVar6;
  
  piVar1 = *(int **)(param_1 + 0x58);
  while (piVar1 != (int *)0x0) {
    iVar2 = *piVar1;
    piVar1 = (int *)piVar1[1];
    uVar3 = *(uint *)(iVar2 + 0x2480);
    if ((((uVar3 & 0x50) == 0) && ((uVar3 & 0xc000) == 0)) || ((char)uVar3 < '\0')) {
      if (-1 < *(int *)(iVar2 + 0x2448)) {
        FUN_00448db0(*(undefined2 **)(DAT_00477704 + 0x30 + *(int *)(iVar2 + 0x244c) * 4));
      }
      *(uint *)(iVar2 + 0x2480) = *(uint *)(iVar2 + 0x2480) | 0x20000;
    }
  }
  pfVar4 = *(float **)(param_1 + 0x4c);
  *(int *)(param_1 + 0x40) = *(int *)(param_1 + 0x44);
  if ((_DAT_00470b68 < *pfVar4) && (*pfVar4 < _DAT_00470b64)) {
    fVar5 = *(float *)(param_1 + 0x48) + _DAT_00470afc;
    *(int *)(param_1 + 0x44) = *(int *)(param_1 + 0x44) + 1;
    *(float *)(param_1 + 0x48) = fVar5;
    return;
  }
  *(float *)(param_1 + 0x48) = *pfVar4 + *(float *)(param_1 + 0x48);
  uVar6 = FUN_00463b2c();
  *(int *)(param_1 + 0x44) = (int)uVar6;
  return;
}

