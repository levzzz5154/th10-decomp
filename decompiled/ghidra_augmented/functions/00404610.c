/* Raw Ghidra reference; not compilable reconstruction. Address: 00404610 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00404610(void)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float *pfVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float *in_EAX;
  float *unaff_EDI;
  float10 fVar14;
  ulonglong uVar15;
  float local_40;
  
  local_40 = in_EAX[0x11];
  if (0 < (int)local_40) {
    pfVar4 = (float *)in_EAX[0xf];
    in_EAX[0xc] = in_EAX[0xd];
    if ((*pfVar4 <= _DAT_00470b68) || (_DAT_00470b64 <= *pfVar4)) {
      in_EAX[0xe] = *pfVar4 + in_EAX[0xe];
      uVar15 = FUN_00463b2c();
      in_EAX[0xd] = (float)uVar15;
    }
    else {
      fVar5 = in_EAX[0xe] + _DAT_00470afc;
      in_EAX[0xd] = (float)((int)in_EAX[0xd] + 1);
      in_EAX[0xe] = fVar5;
    }
    local_40 = in_EAX[0x11];
    if ((int)local_40 <= (int)in_EAX[0xd]) {
      if (((uint)in_EAX[0x10] & 1) == 0) {
        in_EAX[0xd] = 0.0;
        in_EAX[0xc] = -NAN;
        in_EAX[0xe] = 0.0;
        in_EAX[0xf] = (float)&DAT_00476f78;
        in_EAX[0x10] = (float)((uint)in_EAX[0x10] | 1);
      }
      in_EAX[0xd] = local_40;
      in_EAX[0xc] = (float)((int)local_40 + -1);
      in_EAX[0xe] = (float)(int)local_40;
      in_EAX[0x11] = 0.0;
      if (in_EAX[0x12] != 9.80909e-45) {
        *unaff_EDI = in_EAX[3];
        unaff_EDI[1] = in_EAX[4];
        unaff_EDI[2] = in_EAX[5];
        return;
      }
      *unaff_EDI = *in_EAX;
      unaff_EDI[1] = in_EAX[1];
      unaff_EDI[2] = in_EAX[2];
      return;
    }
  }
  fVar5 = in_EAX[0x12];
  if (fVar5 == 9.80909e-45) {
    fVar6 = *in_EAX;
    fVar7 = in_EAX[1];
    fVar8 = in_EAX[2];
    fVar5 = in_EAX[4];
    fVar1 = in_EAX[5];
    *in_EAX = fVar6 + in_EAX[3];
    in_EAX[1] = fVar7 + fVar5;
    in_EAX[2] = fVar8 + fVar1;
    *unaff_EDI = fVar6 + in_EAX[3];
    unaff_EDI[1] = fVar7 + fVar5;
    unaff_EDI[2] = fVar8 + fVar1;
    return;
  }
  if (fVar5 == 2.38221e-44) {
    fVar7 = *in_EAX;
    fVar8 = in_EAX[1];
    fVar9 = in_EAX[2];
    fVar5 = in_EAX[9];
    fVar1 = in_EAX[10];
    fVar6 = in_EAX[0xb];
    *in_EAX = fVar7 + fVar5;
    in_EAX[1] = fVar8 + fVar1;
    in_EAX[2] = fVar9 + fVar6;
    in_EAX[9] = in_EAX[9] + in_EAX[3];
    in_EAX[10] = in_EAX[4] + in_EAX[10];
    in_EAX[0xb] = in_EAX[5] + in_EAX[0xb];
    *unaff_EDI = fVar7 + fVar5;
    unaff_EDI[1] = fVar8 + fVar1;
    unaff_EDI[2] = fVar9 + fVar6;
    return;
  }
  if (fVar5 == 1.12104e-44) {
    fVar10 = in_EAX[0xe] / (float)(int)local_40;
    fVar5 = fVar10 - _DAT_00470afc;
    fVar13 = (_DAT_00470afc + fVar10 + fVar10) * fVar5 * fVar5;
    fVar11 = (_DAT_00470bd4 - (fVar10 + fVar10)) * fVar10 * fVar10;
    fVar12 = (_DAT_00470afc - fVar10) * (_DAT_00470afc - fVar10) * fVar10;
    fVar10 = fVar5 * fVar10 * fVar10;
    fVar5 = in_EAX[10];
    fVar1 = in_EAX[0xb];
    fVar6 = in_EAX[7];
    fVar7 = in_EAX[8];
    fVar8 = in_EAX[4];
    fVar9 = in_EAX[5];
    fVar2 = in_EAX[1];
    fVar3 = in_EAX[2];
    *unaff_EDI = fVar13 * *in_EAX + fVar11 * in_EAX[3] + fVar12 * in_EAX[6] + fVar10 * in_EAX[9];
    unaff_EDI[1] = fVar13 * fVar2 + fVar11 * fVar8 + fVar12 * fVar6 + fVar10 * fVar5;
    unaff_EDI[2] = fVar13 * fVar3 + fVar11 * fVar9 + fVar12 * fVar7 + fVar10 * fVar1;
    return;
  }
  fVar14 = FUN_0044c350(in_EAX[0xe],(float)(int)local_40);
  fVar5 = in_EAX[4];
  fVar1 = in_EAX[1];
  fVar6 = in_EAX[5];
  fVar7 = in_EAX[2];
  fVar8 = in_EAX[1];
  fVar9 = in_EAX[2];
  *unaff_EDI = (float)(((float10)in_EAX[3] - (float10)*in_EAX) * fVar14) + *in_EAX;
  unaff_EDI[1] = (float)(((float10)fVar5 - (float10)fVar1) * fVar14 + (float10)fVar8);
  unaff_EDI[2] = (float)((float10)(fVar6 - fVar7) * fVar14) + fVar9;
  return;
}

