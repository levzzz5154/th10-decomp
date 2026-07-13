/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00441AD0
 * Tracking name: FUN_00441ad0
 * Ghidra name: FUN_00441ad0
 * Tracked span: 896 bytes
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00441ad0(void)

{
  float *pfVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float *unaff_ESI;
  float *unaff_EDI;
  float10 fVar10;
  ulonglong uVar11;
  float local_20;
  
  local_20 = unaff_ESI[0xd];
  if (0 < (int)local_20) {
    pfVar1 = (float *)unaff_ESI[0xb];
    unaff_ESI[8] = unaff_ESI[9];
    if ((*pfVar1 <= _DAT_00470b68) || (_DAT_00470b64 <= *pfVar1)) {
      unaff_ESI[10] = *pfVar1 + unaff_ESI[10];
      uVar11 = FUN_00463b2c();
      unaff_ESI[9] = (float)uVar11;
    }
    else {
      fVar2 = unaff_ESI[10] + _DAT_00470afc;
      unaff_ESI[9] = (float)((int)unaff_ESI[9] + 1);
      unaff_ESI[10] = fVar2;
    }
    local_20 = unaff_ESI[0xd];
    if ((int)local_20 <= (int)unaff_ESI[9]) {
      if (((uint)unaff_ESI[0xc] & 1) == 0) {
        unaff_ESI[9] = 0.0;
        unaff_ESI[8] = -NAN;
        unaff_ESI[10] = 0.0;
        unaff_ESI[0xb] = (float)&DAT_00476f78;
        unaff_ESI[0xc] = (float)((uint)unaff_ESI[0xc] | 1);
      }
      unaff_ESI[9] = local_20;
      unaff_ESI[8] = (float)((int)local_20 + -1);
      unaff_ESI[10] = (float)(int)local_20;
      unaff_ESI[0xd] = 0.0;
      if (unaff_ESI[0xe] != 9.80909e-45) {
        *unaff_EDI = unaff_ESI[2];
        unaff_EDI[1] = unaff_ESI[3];
        return;
      }
      *unaff_EDI = *unaff_ESI;
      unaff_EDI[1] = unaff_ESI[1];
      return;
    }
  }
  fVar2 = unaff_ESI[0xe];
  if (fVar2 == 9.80909e-45) {
    fVar3 = *unaff_ESI;
    fVar4 = unaff_ESI[1];
    fVar2 = unaff_ESI[3];
    *unaff_ESI = fVar3 + unaff_ESI[2];
    unaff_ESI[1] = fVar4 + fVar2;
    *unaff_EDI = fVar3 + unaff_ESI[2];
    unaff_EDI[1] = fVar4 + fVar2;
    return;
  }
  if (fVar2 == 2.38221e-44) {
    fVar4 = *unaff_ESI;
    fVar5 = unaff_ESI[1];
    fVar2 = unaff_ESI[6];
    fVar3 = unaff_ESI[7];
    *unaff_ESI = fVar4 + fVar2;
    unaff_ESI[1] = fVar5 + fVar3;
    unaff_ESI[6] = unaff_ESI[6] + unaff_ESI[2];
    unaff_ESI[7] = unaff_ESI[3] + unaff_ESI[7];
    *unaff_EDI = fVar4 + fVar2;
    unaff_EDI[1] = fVar5 + fVar3;
    return;
  }
  if (fVar2 == 1.12104e-44) {
    fVar6 = unaff_ESI[10] / (float)(int)local_20;
    fVar2 = fVar6 - _DAT_00470afc;
    fVar9 = (_DAT_00470afc + fVar6 + fVar6) * fVar2 * fVar2;
    fVar7 = (_DAT_00470bd4 - (fVar6 + fVar6)) * fVar6 * fVar6;
    fVar8 = (_DAT_00470afc - fVar6) * (_DAT_00470afc - fVar6) * fVar6;
    fVar6 = fVar2 * fVar6 * fVar6;
    fVar2 = unaff_ESI[7];
    fVar3 = unaff_ESI[5];
    fVar4 = unaff_ESI[3];
    fVar5 = unaff_ESI[1];
    *unaff_EDI = fVar9 * *unaff_ESI + fVar7 * unaff_ESI[2] + fVar8 * unaff_ESI[4] +
                 fVar6 * unaff_ESI[6];
    unaff_EDI[1] = fVar9 * fVar5 + fVar7 * fVar4 + fVar8 * fVar3 + fVar6 * fVar2;
    return;
  }
  fVar10 = FUN_0044c350(unaff_ESI[10],(float)(int)local_20);
  fVar2 = unaff_ESI[3];
  fVar3 = unaff_ESI[1];
  fVar4 = unaff_ESI[1];
  *unaff_EDI = (float)(((float10)unaff_ESI[2] - (float10)*unaff_ESI) * fVar10 + (float10)*unaff_ESI)
  ;
  unaff_EDI[1] = (float)((float10)(fVar2 - fVar3) * fVar10) + fVar4;
  return;
}

