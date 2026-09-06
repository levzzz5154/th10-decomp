/* Raw Ghidra reference; not compilable reconstruction. Address: 0043C310 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 __fastcall FUN_0043c310(int param_1)

{
  float *pfVar1;
  float fVar2;
  undefined4 in_EDX;
  int iVar3;
  ulonglong uVar4;
  
  if (*(int *)(param_1 + 0x2c) == 0) {
    if ((*(int *)(param_1 + 0x1c) != 0) && (*(int *)(param_1 + 0x34) <= *(int *)(param_1 + 0x1c))) {
      uVar4 = FUN_00463b2c();
      *(int *)(param_1 + 0x18) = (int)uVar4;
    }
  }
  else {
    if (8 < *(int *)(param_1 + 0x34)) {
      return CONCAT44(in_EDX,7);
    }
    uVar4 = FUN_00463b2c();
    *(int *)(param_1 + 0x18) = 0x80 - (int)uVar4;
  }
  pfVar1 = *(float **)(param_1 + 0x3c);
  *(int *)(param_1 + 0x30) = *(int *)(param_1 + 0x34);
  if ((_DAT_00470b68 < *pfVar1) && (*pfVar1 < _DAT_00470b64)) {
    iVar3 = *(int *)(param_1 + 0x34) + 1;
    fVar2 = *(float *)(param_1 + 0x38) + _DAT_00470afc;
    *(int *)(param_1 + 0x34) = iVar3;
    *(float *)(param_1 + 0x38) = fVar2;
    return CONCAT44(iVar3,1);
  }
  *(float *)(param_1 + 0x38) = *pfVar1 + *(float *)(param_1 + 0x38);
  uVar4 = FUN_00463b2c();
  *(int *)(param_1 + 0x34) = (int)uVar4;
  return CONCAT44((int)(uVar4 >> 0x20),1);
}

