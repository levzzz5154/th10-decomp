/* Raw Ghidra reference; not compilable reconstruction. Address: 004067D0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

ulonglong __fastcall
FUN_004067d0(undefined4 param_1,undefined4 param_2,uint param_3,uint param_4,int param_5,
            float param_6)

{
  short *psVar1;
  float *pfVar2;
  uint uVar3;
  float fVar4;
  float fVar5;
  undefined4 extraout_ECX;
  uint extraout_EDX;
  short *unaff_EBX;
  uint *puVar6;
  uint *puVar7;
  uint *puVar8;
  int iVar9;
  float10 fVar10;
  float10 extraout_ST1;
  float10 extraout_ST1_00;
  float10 extraout_ST1_01;
  float10 extraout_ST1_02;
  ulonglong uVar11;
  float local_14;
  float local_10;
  
  puVar7 = *(uint **)(param_3 + 0x10);
  iVar9 = 0;
  while (puVar8 = puVar7, *(short *)((int)puVar7 + 0x446) != 0) {
    puVar8 = puVar7 + 0x1fc;
    param_2 = 5;
    if (*(short *)((int)puVar7 + 0xc36) == 5) {
      puVar8 = (uint *)(param_3 + 0x60);
    }
    if (*(short *)((int)puVar8 + 0x446) == 0) {
      iVar9 = iVar9 + 1;
      break;
    }
    psVar1 = (short *)((int)puVar8 + 0xc36);
    puVar8 = puVar8 + 0x1fc;
    if (*psVar1 == 5) {
      puVar8 = (uint *)(param_3 + 0x60);
    }
    if (*(short *)((int)puVar8 + 0x446) == 0) {
      iVar9 = iVar9 + 2;
      break;
    }
    psVar1 = (short *)((int)puVar8 + 0xc36);
    puVar8 = puVar8 + 0x1fc;
    if (*psVar1 == 5) {
      puVar8 = (uint *)(param_3 + 0x60);
    }
    if (*(short *)((int)puVar8 + 0x446) == 0) {
      iVar9 = iVar9 + 3;
      break;
    }
    puVar6 = puVar8 + 0x1fc;
    if (*(short *)((int)puVar8 + 0xc36) == 5) {
      puVar6 = (uint *)(param_3 + 0x60);
    }
    if (*(short *)((int)puVar6 + 0x446) == 0) {
      iVar9 = iVar9 + 4;
      puVar8 = puVar6;
      break;
    }
    puVar7 = puVar6 + 0x1fc;
    if (*(short *)((int)puVar6 + 0xc36) == 5) {
      puVar7 = (uint *)(param_3 + 0x60);
    }
    iVar9 = iVar9 + 5;
    if (1999 < iVar9) {
      return 0x500000001;
    }
  }
  if (1999 < iVar9) {
    return CONCAT44(param_2,1);
  }
  local_14 = 0.0;
  if (unaff_EBX[0xfb] < 2) {
    local_10 = *(float *)(unaff_EBX + 0xc);
  }
  else {
    local_10 = *(float *)(unaff_EBX + 0xc) -
               ((*(float *)(unaff_EBX + 0xc) - *(float *)(unaff_EBX + 0xe)) * (float)param_5) /
               (float)(int)unaff_EBX[0xfb];
  }
  switch(unaff_EBX[0xfc]) {
  case 0:
  case 1:
    if ((*(byte *)(unaff_EBX + 0xfa) & 1) == 0) {
      local_14 = (float)((int)param_4 / 2) + _DAT_00470b0c;
    }
    else {
      local_14 = (float)((int)(param_4 + 1) / 2);
    }
    local_14 = local_14 * *(float *)(unaff_EBX + 10);
    if ((param_4 & 1) != 0) {
      local_14 = local_14 * _DAT_00470b60;
    }
    if (unaff_EBX[0xfc] == 0) {
      local_14 = local_14 + param_6;
    }
    local_14 = local_14 + *(float *)(unaff_EBX + 8);
    break;
  case 2:
    local_14 = param_6;
  case 3:
    local_14 = (float)param_5 * *(float *)(unaff_EBX + 10) +
               ((float)(int)param_4 * _DAT_00470b14) / (float)(int)unaff_EBX[0xfa] + local_14 +
               *(float *)(unaff_EBX + 8);
    break;
  case 4:
    local_14 = param_6;
  case 5:
    local_14 = (float)param_5 * *(float *)(unaff_EBX + 10) +
               ((float)(int)param_4 * _DAT_00470b14) / (float)(int)unaff_EBX[0xfa] +
               _DAT_00470b18 / (float)(int)unaff_EBX[0xfa] + local_14 + *(float *)(unaff_EBX + 8);
    break;
  case 6:
    fVar10 = NextRandomFloat(&DAT_004918b0);
    local_14 = (float)(fVar10 * extraout_ST1 + (float10)*(float *)(unaff_EBX + 10));
    break;
  case 7:
    fVar10 = NextRandomFloat(&DAT_004918b0);
    local_10 = (float)(fVar10 * extraout_ST1_00 + (float10)*(float *)(unaff_EBX + 0xe));
    local_14 = (float)param_5 * *(float *)(unaff_EBX + 10) +
               ((float)(int)param_4 * _DAT_00470b14) / (float)(int)unaff_EBX[0xfa] +
               *(float *)(unaff_EBX + 8);
    break;
  case 8:
    fVar10 = NextRandomFloat(&DAT_004918b0);
    local_14 = (float)(fVar10 * extraout_ST1_01 + (float10)*(float *)(unaff_EBX + 10));
    fVar10 = NextRandomFloat(&DAT_004918b0);
    local_10 = (float)(fVar10 * extraout_ST1_02 + (float10)*(float *)(unaff_EBX + 0xe));
  }
  *puVar8 = *puVar8 | 1;
  *(undefined2 *)((int)puVar8 + 0x446) = 1;
  if ((puVar8[0x102] & 1) == 0) {
    puVar8[0xff] = 0;
    puVar8[0xfe] = 0xfff0bdc1;
    puVar8[0x100] = 0;
    puVar8[0x101] = (uint)&DAT_00476f78;
    puVar8[0x102] = puVar8[0x102] | 1;
  }
  puVar8[0xff] = 0;
  puVar8[0x100] = 0;
  puVar8[0xfe] = 0xffffffff;
  if ((puVar8[0x107] & 1) == 0) {
    puVar8[0x104] = 0;
    puVar8[0x103] = 0xfff0bdc1;
    puVar8[0x105] = 0;
    puVar8[0x106] = (uint)&DAT_00476f78;
    puVar8[0x107] = puVar8[0x107] | 1;
  }
  puVar8[0x103] = 0xffffffff;
  puVar8[0x104] = 0;
  puVar8[0x105] = 0;
  puVar8[0xf6] = (uint)local_10;
  fVar10 = (float10)FUN_0044bc10(local_14,0.0);
  puVar8[0xf9] = (uint)(float)fVar10;
  pfVar2 = (float *)(puVar8 + 0xed);
  *pfVar2 = *(float *)(unaff_EBX + 2);
  puVar8[0xee] = *(uint *)(unaff_EBX + 4);
  puVar8[0xef] = *(uint *)(unaff_EBX + 6);
  puVar8[0xef] = 0x3dcccccd;
  FUN_00408750(puVar8 + 0xf0,local_14,local_10);
  puVar8[0x10f] = *(uint *)(unaff_EBX + 0xfe);
  *(short *)(puVar8 + 0x1fb) = unaff_EBX[1];
  *(short *)((int)puVar8 + 0x7ea) = *unaff_EBX;
  *puVar8 = *puVar8 & 0xfffffff3 | 2;
  puVar8[0x115] = 0;
  FUN_00404f30(*(void **)(param_3 + 0x3e0b50),*(void **)(param_3 + 0x3e0b50));
  switch(*(undefined4 *)(&DAT_004742c0 + *unaff_EBX * 4)) {
  case 0:
    puVar8[0x10e] = unaff_EBX[1] * 2 + 0x11;
    break;
  case 1:
    puVar8[0x10e] = *(uint *)(&DAT_0047432c + unaff_EBX[1] * 4);
    break;
  case 2:
    puVar8[0x10e] = 0xffffffff;
    break;
  case 3:
    puVar8[0x10e] = 0x1d;
    break;
  case 4:
    puVar8[0x10e] = 0x13;
  }
  puVar8[0x118] = *(uint *)(&DAT_00474250 + *unaff_EBX * 4);
  puVar8[0x116] = *(uint *)(unaff_EBX + 0x102);
  puVar8[0x10d] = 10;
  uVar3 = *(uint *)(&DAT_004741e0 + *unaff_EBX * 4);
  puVar8[0xfd] = uVar3;
  puVar8[0xfc] = uVar3;
  uVar3 = *(uint *)(unaff_EBX + 0xfe);
  if ((uVar3 & 2) == 0) {
    if ((uVar3 & 4) == 0) {
      if ((uVar3 & 8) == 0) {
        *(undefined2 *)(puVar8 + 0xc3) = 2;
        goto LAB_00406cdc;
      }
      *(undefined2 *)(puVar8 + 0xc3) = 9;
    }
    else {
      *(undefined2 *)(puVar8 + 0xc3) = 8;
    }
  }
  else {
    *(undefined2 *)(puVar8 + 0xc3) = 7;
  }
  *(undefined2 *)((int)puVar8 + 0x446) = 2;
  fVar4 = (float)puVar8[0xf1] * _DAT_00470c40;
  fVar5 = (float)puVar8[0xf2] * _DAT_00470c40;
  *pfVar2 = *pfVar2 - (float)puVar8[0xf0] * _DAT_00470c40;
  puVar8[0xee] = (uint)((float)puVar8[0xee] - fVar4);
  puVar8[0xef] = (uint)((float)puVar8[0xef] - fVar5);
LAB_00406cdc:
  puVar7 = (uint *)(unaff_EBX + 0x10);
  puVar6 = puVar8 + 0x119;
  for (iVar9 = 0x6c; iVar9 != 0; iVar9 = iVar9 + -1) {
    *puVar6 = *puVar7;
    puVar7 = puVar7 + 1;
    puVar6 = puVar6 + 1;
  }
  puVar8[0x110] = *(uint *)(unaff_EBX + 0xfe);
  puVar8[0x10f] = 0;
  puVar8[0x117] = *(uint *)(unaff_EBX + 0x104);
  FUN_00406d90((int)puVar8);
  uVar11 = FUN_0043ee30(extraout_ECX,extraout_EDX,(int)(puVar8 + 2));
  if (*(short *)((int)puVar8 + 0xc36) != 5) {
    *(uint **)(param_3 + 0x10) = puVar8 + 0x1fc;
    return (ulonglong)param_3 << 0x20;
  }
  *(uint *)(param_3 + 0x10) = param_3 + 0x60;
  return uVar11 & 0xffffffff00000000;
}

