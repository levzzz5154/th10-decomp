/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x004049A0
 * Tracking name: FUN_004049a0
 * Ghidra name: FUN_004049a0
 * Tracked span: 928 bytes
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 FUN_004049a0(float *param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float *pfVar5;
  int iVar6;
  float fVar7;
  undefined4 uVar8;
  float *unaff_EBX;
  float *pfVar9;
  float10 fVar10;
  ulonglong uVar11;
  undefined8 uVar12;
  float local_d4;
  float local_c4 [49];
  
  local_d4 = unaff_EBX[0x21];
  if (0 < (int)local_d4) {
    pfVar5 = (float *)unaff_EBX[0x1f];
    unaff_EBX[0x1c] = unaff_EBX[0x1d];
    if ((*pfVar5 <= _DAT_00470b68) || (_DAT_00470b64 <= *pfVar5)) {
      unaff_EBX[0x1e] = *pfVar5 + unaff_EBX[0x1e];
      uVar11 = FUN_00463b2c();
      fVar7 = (float)(uVar11 >> 0x20);
      unaff_EBX[0x1d] = (float)uVar11;
    }
    else {
      fVar7 = (float)((int)unaff_EBX[0x1d] + 1);
      fVar1 = unaff_EBX[0x1e] + _DAT_00470afc;
      unaff_EBX[0x1d] = fVar7;
      unaff_EBX[0x1e] = fVar1;
    }
    local_d4 = unaff_EBX[0x21];
    if ((int)local_d4 <= (int)unaff_EBX[0x1d]) {
      if (((uint)unaff_EBX[0x20] & 1) == 0) {
        unaff_EBX[0x1d] = 0.0;
        unaff_EBX[0x1c] = -NAN;
        unaff_EBX[0x1e] = 0.0;
        unaff_EBX[0x1f] = (float)&DAT_00476f78;
        unaff_EBX[0x20] = (float)((uint)unaff_EBX[0x20] | 1);
      }
      unaff_EBX[0x1d] = local_d4;
      unaff_EBX[0x1c] = (float)((int)local_d4 + -1);
      unaff_EBX[0x1e] = (float)(int)local_d4;
      iVar6 = 7;
      unaff_EBX[0x21] = 0.0;
      pfVar5 = param_1;
      if (unaff_EBX[0x22] == 9.80909e-45) {
        for (; iVar6 != 0; iVar6 = iVar6 + -1) {
          *pfVar5 = *unaff_EBX;
          unaff_EBX = unaff_EBX + 1;
          pfVar5 = pfVar5 + 1;
        }
        return CONCAT44(fVar7,param_1);
      }
      pfVar5 = unaff_EBX + 7;
      pfVar9 = param_1;
      for (; iVar6 != 0; iVar6 = iVar6 + -1) {
        *pfVar9 = *pfVar5;
        pfVar5 = pfVar5 + 1;
        pfVar9 = pfVar9 + 1;
      }
      return CONCAT44(fVar7,param_1);
    }
  }
  fVar7 = unaff_EBX[0x22];
  if (fVar7 == 9.80909e-45) {
    pfVar5 = unaff_EBX;
    pfVar9 = local_c4;
    for (iVar6 = 7; iVar6 != 0; iVar6 = iVar6 + -1) {
      *pfVar9 = *pfVar5;
      pfVar5 = pfVar5 + 1;
      pfVar9 = pfVar9 + 1;
    }
    uVar12 = FUN_00404e10(local_c4);
    uVar8 = (undefined4)((ulonglong)uVar12 >> 0x20);
    pfVar5 = (float *)uVar12;
    pfVar9 = unaff_EBX;
    for (iVar6 = 7; iVar6 != 0; iVar6 = iVar6 + -1) {
      *pfVar9 = *pfVar5;
      pfVar5 = pfVar5 + 1;
      pfVar9 = pfVar9 + 1;
    }
  }
  else if (fVar7 == 2.38221e-44) {
    pfVar5 = unaff_EBX;
    pfVar9 = local_c4;
    for (iVar6 = 7; iVar6 != 0; iVar6 = iVar6 + -1) {
      *pfVar9 = *pfVar5;
      pfVar5 = pfVar5 + 1;
      pfVar9 = pfVar9 + 1;
    }
    pfVar5 = (float *)FUN_00404e10(local_c4);
    pfVar9 = unaff_EBX;
    for (iVar6 = 7; iVar6 != 0; iVar6 = iVar6 + -1) {
      *pfVar9 = *pfVar5;
      pfVar5 = pfVar5 + 1;
      pfVar9 = pfVar9 + 1;
    }
    uVar12 = FUN_00404e10(unaff_EBX + 0x15);
    uVar8 = (undefined4)((ulonglong)uVar12 >> 0x20);
    pfVar5 = (float *)uVar12;
    pfVar9 = unaff_EBX + 0x15;
    for (iVar6 = 7; iVar6 != 0; iVar6 = iVar6 + -1) {
      *pfVar9 = *pfVar5;
      pfVar5 = pfVar5 + 1;
      pfVar9 = pfVar9 + 1;
    }
  }
  else {
    if (fVar7 == 1.12104e-44) {
      fVar7 = unaff_EBX[0x1e] / (float)(int)local_d4;
      fVar1 = fVar7 - _DAT_00470afc;
      fVar4 = _DAT_00470afc + fVar7 + fVar7;
      fVar3 = _DAT_00470bd4 - (fVar7 + fVar7);
      fVar2 = _DAT_00470afc - fVar7;
      FUN_00404da0(fVar1 * fVar7 * fVar7);
      FUN_00404da0(fVar2 * fVar2 * fVar7);
      FUN_00404da0(fVar3 * fVar7 * fVar7);
      pfVar5 = (float *)FUN_00404da0(fVar4 * fVar1 * fVar1);
      pfVar5 = (float *)FUN_00404e10(pfVar5);
      pfVar5 = (float *)FUN_00404e10(pfVar5);
    }
    else {
      fVar10 = FUN_0044c350(unaff_EBX[0x1e],(float)(int)local_d4);
      fVar7 = (float)fVar10;
      FUN_00404d40(unaff_EBX + 7);
      pfVar5 = (float *)FUN_00404da0(fVar7);
    }
    uVar12 = FUN_00404e10(pfVar5);
    uVar8 = (undefined4)((ulonglong)uVar12 >> 0x20);
    unaff_EBX = (float *)uVar12;
  }
  pfVar5 = param_1;
  for (iVar6 = 7; iVar6 != 0; iVar6 = iVar6 + -1) {
    *pfVar5 = *unaff_EBX;
    unaff_EBX = unaff_EBX + 1;
    pfVar5 = pfVar5 + 1;
  }
  return CONCAT44(uVar8,param_1);
}

