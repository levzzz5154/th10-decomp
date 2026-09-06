/* Raw Ghidra reference; not compilable reconstruction. Address: 0040DC80 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_0040dc80(undefined4 *param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  void *pvVar4;
  undefined4 *puVar5;
  float *pfVar6;
  float *pfVar7;
  uint uVar8;
  int iVar9;
  byte *pbVar10;
  int iVar11;
  int extraout_ECX;
  int extraout_ECX_00;
  int extraout_ECX_01;
  int extraout_ECX_02;
  int extraout_ECX_03;
  int extraout_ECX_04;
  undefined4 *puVar12;
  undefined4 *puVar13;
  int *piVar14;
  float10 fVar15;
  ulonglong uVar16;
  float local_18;
  undefined4 local_14;
  
  puVar5 = param_1;
  if ((param_1[0x511] & 0x400) != 0) {
    return 0;
  }
  param_1[0x511] = param_1[0x511] | 0x400;
  iVar9 = param_1[0x82];
  puVar12 = param_1 + 0xb;
  puVar13 = param_1;
  for (iVar11 = 0xb; iVar11 != 0; iVar11 = iVar11 + -1) {
    *puVar13 = *puVar12;
    puVar12 = puVar12 + 1;
    puVar13 = puVar13 + 1;
  }
  if (iVar9 != 0) {
    FUN_00412ac0();
    fVar15 = (float10)NormalizeAngle(local_18);
    param_1[0x1d] = (float)fVar15;
    param_1[0x1c] = local_14;
  }
  if (param_1[0xa0] != 0) {
    FUN_00412ac0();
    param_1[0x1e] = local_18;
    param_1[0x1f] = local_14;
  }
  if (param_1[0x91] != 0) {
    FUN_00412ac0();
    fVar15 = (float10)NormalizeAngle(local_18);
    param_1[0x28] = (float)fVar15;
    param_1[0x27] = local_14;
  }
  if (param_1[0xaf] != 0) {
    FUN_00412ac0();
    param_1[0x29] = local_18;
    param_1[0x2a] = local_14;
  }
  if (param_1[0x60] == 0) {
    if ((*(byte *)(param_1 + 0x20) & 1) == 0) {
      FUN_0044c5d0(param_1 + 0x19,(float)param_1[0x1d],(float)param_1[0x1c]);
      param_1[0x1b] = 0;
    }
    else {
      param_1[0x1e] = (float)param_1[0x1f] + (float)param_1[0x1e];
      fVar15 = (float10)NormalizeAngle((float)param_1[0x1c] + (float)param_1[0x1d]);
      param_1[0x1d] = (float)fVar15;
    }
  }
  else {
    pfVar6 = (float *)FUN_00404610();
    fVar1 = pfVar6[1];
    fVar2 = pfVar6[2];
    param_1[0x19] = *pfVar6 - (float)param_1[0x16];
    param_1[0x1a] = fVar1 - (float)param_1[0x17];
    param_1[0x1b] = fVar2 - (float)param_1[0x18];
  }
  pfVar6 = (float *)(param_1 + 0x21);
  if (param_1[0x73] == 0) {
    if ((*(byte *)(param_1 + 0x2b) & 1) == 0) {
      FUN_0044c5d0(param_1 + 0x24,(float)param_1[0x28],(float)param_1[0x27]);
      param_1[0x26] = 0;
    }
    else {
      param_1[0x29] = (float)param_1[0x2a] + (float)param_1[0x29];
      fVar15 = (float10)NormalizeAngle((float)param_1[0x27] + (float)param_1[0x28]);
      param_1[0x28] = (float)fVar15;
    }
  }
  else {
    pfVar7 = (float *)FUN_00404610();
    fVar1 = pfVar7[1];
    fVar2 = pfVar7[2];
    param_1[0x24] = *pfVar7 - *pfVar6;
    param_1[0x25] = fVar1 - (float)param_1[0x22];
    param_1[0x26] = fVar2 - (float)param_1[0x23];
  }
  FUN_0044c2a0();
  if ((param_1[0x511] & 0x40000) != 0) {
    *pfVar6 = _DAT_00491e6c + *pfVar6;
    param_1[0x22] = _DAT_00491e70 + (float)param_1[0x22];
    param_1[0x23] = _DAT_00491e74 + (float)param_1[0x23];
  }
  FUN_0044c2a0();
  pfVar7 = (float *)(param_1 + 0xb);
  param_1[0xe] = (*pfVar6 + (float)param_1[0x16]) - *pfVar7;
  param_1[0xf] = ((float)param_1[0x22] + (float)param_1[0x17]) - (float)param_1[0xc];
  param_1[0x10] = ((float)param_1[0x23] + (float)param_1[0x18]) - (float)param_1[0xd];
  FUN_0044c2a0();
  uVar8 = param_1[0x511];
  if ((uVar8 & 0x200) != 0) {
    fVar1 = (float)param_1[0x4eb] - (float)param_1[0x4ed] * _DAT_00470b0c;
    if (fVar1 <= *pfVar7) {
      fVar1 = (float)param_1[0x4ed] * _DAT_00470b0c + (float)param_1[0x4eb];
      if (fVar1 < *pfVar7) {
        *pfVar7 = fVar1;
      }
    }
    else {
      *pfVar7 = fVar1;
    }
    fVar1 = (float)param_1[0x4ec] - (float)param_1[0x4ee] * _DAT_00470b0c;
    if (fVar1 <= (float)param_1[0xc]) {
      fVar1 = (float)param_1[0x4ee] * _DAT_00470b0c + (float)param_1[0x4ec];
      if (fVar1 < (float)param_1[0xc]) {
        param_1[0xc] = fVar1;
      }
    }
    else {
      param_1[0xc] = fVar1;
    }
    param_1[0x16] = *pfVar7 - *pfVar6;
    param_1[0x17] = (float)param_1[0xc] - (float)param_1[0x22];
    param_1[0x18] = (float)param_1[0xd] - (float)param_1[0x23];
  }
  if (((((float)param_1[0x4e9] * _DAT_00470b0c + *pfVar7 < _DAT_00470b40) ||
       (_DAT_00470b3c < *pfVar7 - (float)param_1[0x4e9] * _DAT_00470b0c)) ||
      ((float)param_1[0x4ea] * _DAT_00470b0c + (float)param_1[0xc] < _DAT_00470b04)) ||
     (_DAT_00470b38 < (float)param_1[0xc] - (float)param_1[0x4ea] * _DAT_00470b0c)) {
    if (((uVar8 & 0x100) != 0) && ((uVar8 & 4) == 0)) {
      return 0xffffffff;
    }
  }
  else {
    param_1[0x511] = uVar8 | 0x100;
  }
  uVar8 = param_1[0x511];
  if ((uVar8 & 0x100000) != 0) {
    if (*(int *)(DAT_004776ec + 0x28) == 0) {
LAB_0040e0b8:
      if ((uVar8 & 0x200000) == 0) goto LAB_0040e0e9;
      param_1[0x3d] = param_1[0x513];
      FUN_004496d0(param_1[0x513]);
      uVar8 = param_1[0x511] & 0xffdffffe;
    }
    else {
      if ((uVar8 & 0x200000) != 0) {
        if (*(int *)(DAT_004776ec + 0x28) != 0) goto LAB_0040e0e9;
        goto LAB_0040e0b8;
      }
      param_1[0x3d] = param_1[0x512];
      FUN_004496d0(param_1[0x512]);
      uVar8 = param_1[0x511] | 0x200001;
    }
    param_1[0x511] = uVar8;
  }
LAB_0040e0e9:
  iVar9 = FUN_0044fd10(*(float *)param_1[0x4a]);
  if (iVar9 != 0) {
    return 0xffffffff;
  }
  uVar8 = param_1[0x511];
  param_1[0x511] = uVar8 & 0xffffdfff;
  if ((uVar8 & 0x11) == 0) {
    iVar9 = FUN_00428630((void *)0x0,DAT_00477834,(float *)(param_1 + 0xb),(float *)(param_1 + 0x2c)
                        );
    if ((*(int *)(DAT_00477834 + 0x458) == 2) || (*(int *)(DAT_00477834 + 0x458) == 0)) {
      iVar9 = iVar9 / 5;
    }
    if (iVar9 != 0) {
      if ((((*(byte *)(DAT_004776f4 + 0x378c) & 1) != 0) &&
          ((char)((uint)param_1[0x511] >> 8) < '\0')) && (iVar9 = iVar9 / 5, iVar9 < 1)) {
        iVar9 = 1;
      }
      if (((*(byte *)(param_1 + 0x511) & 8) == 0) && ((int)param_1[0x508] < 1)) {
        param_1[0x4f0] = param_1[0x4f0] - iVar9;
      }
      pbVar10 = (byte *)FUN_004127a0(param_1[0x536]);
      if (pbVar10 != (byte *)0x0) {
        FUN_0040c6e0();
        FUN_0040c730();
        FUN_00450700(pbVar10);
        iVar9 = FUN_0044fd10(*(float *)param_1[0x4a]);
        if (iVar9 != 0) {
          return 0xffffffff;
        }
      }
      if (((int)param_1[0x4f0] < 1 & ~(byte)((uint)param_1[0x511] >> 6)) != 0) {
        FUN_00409d90(&DAT_00474c40,param_1[0x4ef]);
        iVar9 = FUN_0040e5f0(param_1[0x536]);
        if (iVar9 != 0) {
          return 1;
        }
      }
      param_1[0x511] = param_1[0x511] | 0x2000;
    }
    _DAT_00474c50 = 1;
  }
  pbVar10 = (byte *)FUN_004127a0(param_1[0x536]);
  iVar9 = extraout_ECX;
  if (pbVar10 != (byte *)0x0) {
    FUN_0040c6e0();
    FUN_0040c730();
    iVar9 = param_1[0x536];
    iVar11 = FUN_00450470(pbVar10);
    *(int *)(*(int *)(iVar9 + 4) + 4) = iVar11;
    **(undefined4 **)(iVar9 + 4) = 0;
    iVar9 = extraout_ECX_00;
  }
  if (((*(byte *)(param_1 + 0x511) & 0x12) == 0) && ((int)param_1[0x50d] < 1)) {
    FUN_004266b0((float *)(param_1 + 0xb),DAT_00477834);
    iVar9 = extraout_ECX_01;
  }
  if ((param_1[0x511] & 0x1000) != 0) {
    iVar9 = 0;
    if (_DAT_00470d30 <= (float)param_1[0xe]) {
      if ((float)param_1[0xe] <= _DAT_00470c18) {
        iVar11 = 0;
      }
      else {
        iVar11 = 1;
      }
    }
    else {
      iVar11 = -1;
    }
    iVar3 = param_1[0x3e];
    if (iVar3 != iVar11) {
      if (iVar3 == -1) {
        iVar9 = 3 - (uint)(iVar11 != 0);
      }
      else if (iVar3 == 0) {
        iVar9 = (iVar11 != -1) + 1;
      }
      else if (iVar3 == 1) {
        iVar9 = (-(uint)(iVar11 != 0) & 0xfffffffd) + 4;
      }
      param_1[0x3e] = iVar11;
      FUN_004496d0(param_1[0x3d] + iVar9);
      iVar9 = extraout_ECX_02;
    }
  }
  pvVar4 = g_pGameStateManager;
  piVar14 = param_1 + 0x30;
  if ((param_1[0x511] & 0x40000) == 0) {
    param_1 = (undefined4 *)0x8;
    do {
      FUN_00449350(iVar9,(int)pvVar4,*piVar14);
      piVar14 = piVar14 + 1;
      param_1 = (undefined4 *)((int)param_1 + -1);
      iVar9 = extraout_ECX_03;
    } while (param_1 != (undefined4 *)0x0);
  }
  else {
    param_1 = (undefined4 *)0x8;
    do {
      FUN_004492f0(*piVar14,(int)pvVar4,*piVar14);
      piVar14 = piVar14 + 1;
      param_1 = (undefined4 *)((int)param_1 + -1);
      iVar9 = extraout_ECX_04;
    } while (param_1 != (undefined4 *)0x0);
  }
  iVar11 = DAT_00477834;
  if ((((puVar5[0x511] & 0x11) == 0) && ((puVar5[0x511] & 0xc0000) == 0)) &&
     ((iVar9 = iVar11, *(int *)(DAT_00477834 + 0x3504) == 0 ||
      (ABS(*(float *)(*(int *)(DAT_00477834 + 0x3504) + 0x1068) - *(float *)(DAT_00477834 + 0x3c0))
       < ABS((float)puVar5[0xb] - *(float *)(DAT_00477834 + 0x3c0)))))) {
    if (*(char *)(DAT_00477834 + 0x3508) == '\0') {
      *(undefined4 *)(DAT_00477834 + 0x3504) = puVar5[0x536];
    }
    *(undefined1 *)(iVar11 + 0x3508) = 1;
  }
  iVar9 = FUN_004491c0(iVar9,(int)pvVar4,puVar5[0x30]);
  if (iVar9 == 0) {
    puVar5[0x30] = 0;
  }
  if (puVar5[0x505] != 0) {
    *(uint *)(iVar9 + 0x35c) = *(uint *)(iVar9 + 0x35c) & 0xffff7fff;
    if ((char)((uint)puVar5[0x511] >> 8) < '\0') {
      *(uint *)(DAT_0047770c + 0x9da4) = *(uint *)(DAT_0047770c + 0x9da4) & 0xffff7fff;
    }
    puVar5[0x505] = puVar5[0x505] + -1;
    goto LAB_0040e53e;
  }
  if ((puVar5[0x511] & 0x2000) == 0) goto LAB_0040e53e;
  *(undefined4 *)(iVar9 + 0x300) = 0xff0000ff;
  *(uint *)(iVar9 + 0x35c) = *(uint *)(iVar9 + 0x35c) | 0x8000;
  puVar5[0x505] = 4;
  if ((puVar5[0x511] & 0x8000) != 0) {
    uVar8 = *(uint *)(DAT_004776f4 + 0x378c) & 1;
    if ((uVar8 == 0) || ((*(uint *)(DAT_004776f4 + 0x378c) & 8) == 0)) {
      if (uVar8 == 0) {
LAB_0040e4d4:
        if (899 < *(int *)(puVar5[0x536] + 0x2404)) goto LAB_0040e4fb;
      }
      else if (299 < *(int *)(puVar5[0x536] + 0x2404)) {
        if (uVar8 != 0) goto LAB_0040e4fb;
        goto LAB_0040e4d4;
      }
      FUN_0043dd10();
      goto LAB_0040e53e;
    }
  }
LAB_0040e4fb:
  FUN_0043dd10();
LAB_0040e53e:
  if (0 < (int)puVar5[0x508]) {
    FUN_0044bf40(-1.0);
  }
  if (0 < (int)puVar5[0x50d]) {
    FUN_0044bf40(-1.0);
  }
  pfVar6 = (float *)puVar5[0x4a];
  puVar5[0x47] = puVar5[0x48];
  if ((_DAT_00470b68 < *pfVar6) && (*pfVar6 < _DAT_00470b64)) {
    puVar5[0x49] = (float)puVar5[0x49] + _DAT_00470afc;
    puVar5[0x48] = puVar5[0x48] + 1;
    return 0;
  }
  puVar5[0x49] = *pfVar6 + (float)puVar5[0x49];
  uVar16 = FUN_00463b2c();
  puVar5[0x48] = (int)uVar16;
  return 0;
}

