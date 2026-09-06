/* Raw Ghidra reference; not compilable reconstruction. Address: 0043C710 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __fastcall FUN_0043c710(int param_1)

{
  int iVar1;
  int iVar2;
  float fVar3;
  float fVar4;
  uint uVar5;
  int iVar6;
  
  if (DAT_004918a4 != 0) {
    return 7;
  }
  if (((DAT_00477810 == 0) ||
      (uVar5 = *(uint *)(DAT_00477810 + 0x58), ((uVar5 >> 2 | uVar5) & 1) != 0)) ||
     ((uVar5 & 0x72) != 0)) {
    return 1;
  }
  FUN_00404ed0();
  iVar6 = *(int *)(param_1 + 0x20);
  iVar1 = *(int *)(param_1 + 0x34);
  if (iVar1 < iVar6) {
    fVar3 = *(float *)(param_1 + 0x38) / (float)iVar6;
  }
  else {
    iVar2 = *(int *)(param_1 + 0x24);
    fVar3 = _DAT_00470afc;
    if (iVar2 + iVar6 <= iVar1) {
      if (*(int *)(param_1 + 0x28) + iVar2 + iVar6 <= iVar1) {
        return 7;
      }
      iVar1 = *(int *)(param_1 + 0x28);
      iVar6 = iVar2 + iVar1 + iVar6;
      fVar3 = (float)iVar6;
      if (iVar6 < 0) {
        fVar3 = fVar3 + _DAT_00470b98;
      }
      fVar4 = (float)iVar1;
      if (iVar1 < 0) {
        fVar4 = fVar4 + _DAT_00470b98;
      }
      fVar3 = (fVar3 - *(float *)(param_1 + 0x38)) / fVar4;
    }
  }
  fVar3 = (float)*(int *)(param_1 + 0x1c) * fVar3;
  uVar5 = FUN_0043cb80(&DAT_004918b0);
  if (uVar5 == 0) {
    DAT_00491e64 = 0.0;
    fVar4 = DAT_00491e64;
  }
  else {
    fVar4 = fVar3;
    if ((uVar5 != 1) && (fVar4 = DAT_00491e64, uVar5 == 2)) {
      fVar4 = -fVar3;
    }
  }
  DAT_00491e64 = fVar4;
  uVar5 = FUN_0043cb80(&DAT_004918b0);
  if (uVar5 == 0) {
    DAT_00491e68 = 0.0;
  }
  else {
    if (uVar5 == 1) {
      DAT_00491e68 = fVar3;
      return 1;
    }
    if (uVar5 == 2) {
      DAT_00491e68 = -fVar3;
      return 1;
    }
  }
  return 1;
}

