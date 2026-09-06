/* Raw Ghidra reference; not compilable reconstruction. Address: 00441600 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int * FUN_00441600(int *param_1)

{
  float *pfVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  float fVar13;
  int *piVar14;
  int *in_EAX;
  int *piVar15;
  int *piVar16;
  ulonglong uVar17;
  ulonglong uVar18;
  ulonglong uVar19;
  
  piVar14 = param_1;
  piVar15 = (int *)in_EAX[0x11];
  if (0 < in_EAX[0x11]) {
    pfVar1 = (float *)in_EAX[0xf];
    in_EAX[0xc] = in_EAX[0xd];
    if ((*pfVar1 <= _DAT_00470b68) || (_DAT_00470b64 <= *pfVar1)) {
      in_EAX[0xe] = (int)(*pfVar1 + (float)in_EAX[0xe]);
      uVar17 = FUN_00463b2c();
      in_EAX[0xd] = (int)uVar17;
    }
    else {
      fVar13 = (float)in_EAX[0xe] + _DAT_00470afc;
      in_EAX[0xd] = in_EAX[0xd] + 1;
      in_EAX[0xe] = (int)fVar13;
    }
    piVar15 = (int *)in_EAX[0x11];
    if ((int)piVar15 <= in_EAX[0xd]) {
      if ((in_EAX[0x10] & 1U) == 0) {
        in_EAX[0xd] = 0;
        in_EAX[0xc] = -999999;
        in_EAX[0xe] = 0;
        in_EAX[0xf] = (int)&DAT_00476f78;
        in_EAX[0x10] = in_EAX[0x10] | 1;
      }
      in_EAX[0xd] = (int)piVar15;
      in_EAX[0xc] = (int)piVar15 + -1;
      in_EAX[0xe] = (int)(float)(int)piVar15;
      in_EAX[0x11] = 0;
      if (in_EAX[0x12] != 7) {
        *param_1 = in_EAX[3];
        param_1[1] = in_EAX[4];
        param_1[2] = in_EAX[5];
        return param_1;
      }
      *param_1 = *in_EAX;
      param_1[1] = in_EAX[1];
      param_1[2] = in_EAX[2];
      return param_1;
    }
  }
  param_1 = piVar15;
  iVar2 = in_EAX[0x12];
  if (iVar2 == 7) {
    iVar2 = *in_EAX;
    iVar3 = in_EAX[1];
    iVar4 = in_EAX[2];
    iVar5 = in_EAX[4];
    iVar6 = in_EAX[5];
    *in_EAX = in_EAX[3] + iVar2;
    in_EAX[1] = iVar5 + iVar3;
    in_EAX[2] = iVar6 + iVar4;
    *piVar14 = in_EAX[3] + iVar2;
    piVar14[1] = iVar5 + iVar3;
    piVar14[2] = iVar6 + iVar4;
    return piVar14;
  }
  if (iVar2 == 0x11) {
    piVar15 = in_EAX + 9;
    iVar2 = *in_EAX;
    iVar3 = in_EAX[1];
    iVar4 = in_EAX[2];
    iVar5 = *piVar15;
    iVar6 = in_EAX[10];
    iVar7 = in_EAX[0xb];
    *in_EAX = iVar5 + iVar2;
    in_EAX[1] = iVar6 + iVar3;
    in_EAX[2] = iVar7 + iVar4;
    *piVar15 = *piVar15 + in_EAX[3];
    in_EAX[10] = in_EAX[4] + in_EAX[10];
    in_EAX[0xb] = in_EAX[5] + in_EAX[0xb];
    *piVar14 = iVar5 + iVar2;
    piVar14[1] = iVar6 + iVar3;
    piVar14[2] = iVar7 + iVar4;
    return piVar14;
  }
  if (iVar2 == 8) {
    piVar15 = (int *)FUN_00441e50();
    piVar16 = (int *)FUN_00441e50();
    iVar2 = *piVar16;
    iVar3 = *piVar15;
    iVar4 = piVar15[1];
    iVar5 = piVar16[1];
    iVar6 = piVar15[2];
    iVar7 = piVar16[2];
    piVar15 = (int *)FUN_00441e50();
    iVar8 = *piVar15;
    iVar9 = piVar15[1];
    iVar10 = piVar15[2];
    piVar15 = (int *)FUN_00441e50();
    iVar11 = piVar15[1];
    iVar12 = piVar15[2];
    *piVar14 = *piVar15 + iVar8 + iVar2 + iVar3;
    piVar14[1] = iVar11 + iVar9 + iVar4 + iVar5;
    piVar14[2] = iVar12 + iVar10 + iVar6 + iVar7;
    return piVar14;
  }
  FUN_0044c350((float)in_EAX[0xe],(float)(int)param_1);
  iVar2 = *in_EAX;
  iVar3 = in_EAX[1];
  iVar4 = in_EAX[2];
  uVar17 = FUN_00463b2c();
  uVar18 = FUN_00463b2c();
  uVar19 = FUN_00463b2c();
  *piVar14 = iVar2 + (int)uVar17;
  piVar14[1] = iVar3 + (int)uVar18;
  piVar14[2] = (int)uVar19 + iVar4;
  return piVar14;
}

