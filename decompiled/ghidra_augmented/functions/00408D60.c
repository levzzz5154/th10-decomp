/* Raw Ghidra reference; not compilable reconstruction. Address: 00408D60 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __fastcall FUN_00408d60(int param_1)

{
  float fVar1;
  float fVar2;
  void *pvVar3;
  uint uVar4;
  undefined2 *puVar5;
  int iVar6;
  int iVar7;
  undefined4 extraout_ECX;
  float *extraout_ECX_00;
  int extraout_ECX_01;
  float *pfVar8;
  float *extraout_ECX_02;
  undefined4 extraout_ECX_03;
  undefined4 extraout_ECX_04;
  undefined4 extraout_ECX_05;
  undefined4 uVar9;
  undefined4 extraout_ECX_06;
  uint extraout_EDX;
  uint extraout_EDX_00;
  uint extraout_EDX_01;
  int iVar10;
  int iVar11;
  int unaff_EDI;
  ulonglong uVar12;
  int local_1c;
  
  if ((*(byte *)(unaff_EDI + 0x378c) & 1) == 0) {
    return 1;
  }
  if (0x3b < *(int *)(unaff_EDI + 0x3738)) {
    *(uint *)(DAT_004776e8 + 0x2a18) = *(uint *)(DAT_004776e8 + 0x2a18) & 0xfffffffe;
  }
  if ((299 < *(int *)(unaff_EDI + 0x3738)) && ((*(byte *)(unaff_EDI + 0x378c) & 8) == 0)) {
    iVar7 = *(int *)(unaff_EDI + 0x3790) -
            (*(int *)(unaff_EDI + 0x3794) - *(int *)(unaff_EDI + 0x3794) / 10) /
            (*(int *)(unaff_EDI + 0x3798) + -300);
    param_1 = iVar7 - iVar7 % 10;
    *(int *)(unaff_EDI + 0x3790) = param_1;
  }
  uVar12 = FUN_0043ee30(param_1,unaff_EDI + 0x10U,unaff_EDI + 0x10U);
  FUN_0043ee30(extraout_ECX,(uint)(uVar12 >> 0x20),unaff_EDI + 0x3bc);
  pfVar8 = *(float **)(unaff_EDI + 0x3740);
  *(int *)(unaff_EDI + 0x3734) = *(int *)(unaff_EDI + 0x3738);
  if ((*pfVar8 <= _DAT_00470b68) || (_DAT_00470b64 <= *pfVar8)) {
    *(float *)(unaff_EDI + 0x373c) = *pfVar8 + *(float *)(unaff_EDI + 0x373c);
    uVar12 = FUN_00463b2c();
    *(int *)(unaff_EDI + 0x3738) = (int)uVar12;
    pfVar8 = extraout_ECX_00;
  }
  else {
    fVar1 = *(float *)(unaff_EDI + 0x373c) + _DAT_00470afc;
    *(int *)(unaff_EDI + 0x3738) = *(int *)(unaff_EDI + 0x3738) + 1;
    *(float *)(unaff_EDI + 0x373c) = fVar1;
  }
  if (0x77 < *(int *)(unaff_EDI + 0x3738)) {
    if ((*(byte *)(unaff_EDI + 0x378c) & 4) == 0) {
      if (_DAT_00470c80 <= *(float *)(DAT_00477834 + 0x3c4)) goto LAB_00408f7c;
      iVar10 = 3;
      iVar7 = DAT_00477834;
      do {
        FUN_00449470(iVar7);
        iVar10 = iVar10 + -1;
        iVar7 = extraout_ECX_01;
      } while (iVar10 != 0);
      puVar5 = (undefined2 *)(unaff_EDI + 0xa7c);
      iVar7 = 8;
      do {
        *puVar5 = 3;
        puVar5 = puVar5 + 0x1d6;
        iVar7 = iVar7 + -1;
      } while (iVar7 != 0);
      puVar5 = (undefined2 *)(unaff_EDI + 0x27dc);
      iVar7 = 5;
      do {
        *puVar5 = 3;
        puVar5 = puVar5 + 0x1d6;
        iVar7 = iVar7 + -1;
      } while (iVar7 != 0);
      uVar4 = *(uint *)(unaff_EDI + 0x378c) | 4;
    }
    else {
      if (*(float *)(DAT_00477834 + 0x3c4) <= _DAT_00470bf4) goto LAB_00408f7c;
      iVar7 = 3;
      do {
        FUN_00449470(pfVar8);
        iVar7 = iVar7 + -1;
        pfVar8 = extraout_ECX_02;
      } while (iVar7 != 0);
      puVar5 = (undefined2 *)(unaff_EDI + 0xa7c);
      iVar7 = 8;
      do {
        *puVar5 = 2;
        puVar5 = puVar5 + 0x1d6;
        iVar7 = iVar7 + -1;
      } while (iVar7 != 0);
      puVar5 = (undefined2 *)(unaff_EDI + 0x27dc);
      iVar7 = 5;
      do {
        *puVar5 = 2;
        puVar5 = puVar5 + 0x1d6;
        iVar7 = iVar7 + -1;
      } while (iVar7 != 0);
      uVar4 = *(uint *)(unaff_EDI + 0x378c) & 0xfffffffb;
    }
    *(uint *)(unaff_EDI + 0x378c) = uVar4;
  }
LAB_00408f7c:
  if ((*(byte *)(unaff_EDI + 0x378c) & 2) == 0) {
    FUN_0043e5a0(*(int *)(DAT_0047770c + 0x9ec8),0x29);
    FUN_0043ee30(extraout_ECX_04,extraout_EDX_00,unaff_EDI + 0xed0);
  }
  else {
    iVar10 = *(int *)(unaff_EDI + 0x3790);
    iVar11 = 10000000;
    iVar7 = unaff_EDI + 0x778;
    local_1c = 8;
    do {
      iVar6 = iVar10 / iVar11;
      iVar10 = iVar10 % iVar11;
      FUN_0043e5a0(*(int *)(DAT_0047770c + 0x9ec8),iVar6 + 0x1e);
      FUN_0043ee30(extraout_ECX_03,extraout_EDX,iVar7);
      iVar11 = iVar11 / 10;
      iVar7 = iVar7 + 0x3ac;
      local_1c = local_1c + -1;
    } while (local_1c != 0);
  }
  iVar10 = DAT_0047770c;
  iVar7 = *(int *)(*(int *)(unaff_EDI + 0x3788) * 0x90 + 0x624 +
                  (DAT_00474c6c + DAT_00474c68 * 3) * 0x437c + DAT_0047783c);
  if (99 < iVar7) {
    iVar7 = 99;
  }
  iVar11 = unaff_EDI + 0x24d8;
  FUN_0043e5a0(*(int *)(DAT_0047770c + 0x9ec8),iVar7 / 10 + 0x1e);
  FUN_0043e5a0(*(int *)(iVar10 + 0x9ec8),iVar7 % 10 + 0x1e);
  iVar7 = *(int *)(*(int *)(unaff_EDI + 0x3788) * 0x90 + 0x628 +
                  (DAT_00474c6c + DAT_00474c68 * 3) * 0x437c + DAT_0047783c);
  if (99 < iVar7) {
    iVar7 = 99;
  }
  FUN_0043e5a0(*(int *)(iVar10 + 0x9ec8),iVar7 / 10 + 0x1e);
  FUN_0043e5a0(*(int *)(iVar10 + 0x9ec8),iVar7 % 10 + 0x1e);
  iVar7 = 5;
  uVar9 = extraout_ECX_05;
  uVar4 = extraout_EDX_01;
  do {
    uVar12 = FUN_0043ee30(uVar9,uVar4,iVar11);
    pvVar3 = g_pGameStateManager;
    uVar4 = (uint)(uVar12 >> 0x20);
    iVar11 = iVar11 + 0x3ac;
    iVar7 = iVar7 + -1;
    uVar9 = extraout_ECX_06;
  } while (iVar7 != 0);
  iVar7 = *(int *)(DAT_00477704 + 0x10);
  pfVar8 = (float *)(unaff_EDI + 0x379c);
  fVar1 = (*(float *)(iVar7 + 0x106c) - *(float *)(unaff_EDI + 0x37a0)) * _DAT_00470c84;
  fVar2 = (*(float *)(iVar7 + 0x1070) - *(float *)(unaff_EDI + 0x37a4)) * _DAT_00470c84;
  *pfVar8 = (*(float *)(iVar7 + 0x1068) - *pfVar8) * _DAT_00470c84 + *pfVar8;
  *(float *)(unaff_EDI + 0x37a0) = fVar1 + *(float *)(unaff_EDI + 0x37a0);
  *(float *)(unaff_EDI + 0x37a4) = fVar2 + *(float *)(unaff_EDI + 0x37a4);
  FUN_00449350(extraout_ECX_06,(int)pvVar3,*(int *)(unaff_EDI + 0x774));
  return 1;
}

