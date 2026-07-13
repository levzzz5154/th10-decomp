/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0040E770
 * Tracking name: FUN_0040e770
 * Ghidra name: FUN_0040e770
 * Tracked span: 16304 bytes
 */


/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __fastcall FUN_0040e770(float param_1)

{
  short sVar1;
  float fVar2;
  byte bVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  undefined4 uVar6;
  int *piVar7;
  uint uVar8;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  undefined4 extraout_ECX_02;
  undefined4 extraout_ECX_03;
  undefined4 extraout_ECX_04;
  undefined4 extraout_ECX_05;
  undefined4 extraout_ECX_06;
  undefined4 extraout_ECX_07;
  undefined4 extraout_ECX_08;
  undefined4 extraout_ECX_09;
  undefined4 extraout_ECX_10;
  undefined4 extraout_ECX_11;
  undefined4 extraout_ECX_12;
  undefined4 extraout_ECX_13;
  undefined4 extraout_ECX_14;
  undefined4 extraout_ECX_15;
  undefined4 extraout_ECX_16;
  undefined4 extraout_ECX_17;
  undefined4 extraout_ECX_18;
  undefined4 extraout_ECX_19;
  undefined4 extraout_ECX_20;
  undefined4 extraout_ECX_21;
  undefined4 extraout_ECX_22;
  undefined4 extraout_ECX_23;
  undefined4 extraout_ECX_24;
  undefined4 extraout_ECX_25;
  undefined4 extraout_ECX_26;
  undefined4 extraout_ECX_27;
  undefined4 extraout_ECX_28;
  undefined4 extraout_ECX_29;
  undefined4 extraout_ECX_30;
  float fVar9;
  undefined4 extraout_ECX_31;
  undefined4 extraout_ECX_32;
  undefined4 extraout_ECX_33;
  undefined4 extraout_ECX_34;
  undefined4 extraout_ECX_35;
  undefined4 extraout_ECX_36;
  undefined4 extraout_ECX_37;
  undefined4 extraout_ECX_38;
  undefined4 extraout_ECX_39;
  undefined4 extraout_ECX_40;
  undefined4 extraout_ECX_41;
  undefined4 extraout_ECX_42;
  undefined4 extraout_ECX_43;
  undefined4 extraout_ECX_44;
  undefined4 extraout_ECX_45;
  undefined4 extraout_ECX_46;
  undefined4 extraout_ECX_47;
  undefined4 extraout_ECX_48;
  undefined4 extraout_ECX_49;
  undefined4 extraout_ECX_50;
  undefined4 extraout_ECX_51;
  int extraout_ECX_52;
  undefined4 extraout_ECX_53;
  undefined4 extraout_ECX_54;
  undefined4 extraout_ECX_55;
  undefined4 extraout_ECX_56;
  undefined4 extraout_ECX_57;
  undefined4 extraout_ECX_58;
  undefined4 extraout_ECX_59;
  undefined4 extraout_ECX_60;
  float fVar10;
  int iVar11;
  float *pfVar12;
  undefined4 *puVar13;
  undefined4 *puVar14;
  float *pfVar15;
  byte *pbVar16;
  int iVar17;
  bool bVar18;
  float10 fVar19;
  float10 fVar20;
  float10 fVar21;
  ulonglong uVar22;
  ulonglong uVar23;
  ulonglong uVar24;
  ulonglong uVar25;
  int iVar26;
  int iVar27;
  undefined4 uVar28;
  float local_2c8;
  float local_2c4;
  float local_2bc;
  float local_2b4;
  float local_2b0;
  float local_2ac;
  float local_2a8;
  float local_2a4;
  char local_29d;
  float local_29c;
  float local_298;
  float local_288 [4];
  float local_278;
  float local_274;
  float local_270;
  float local_26c;
  float local_268;
  undefined4 local_264;
  float local_260;
  undefined4 local_25c [4];
  undefined4 local_24c;
  undefined2 local_248;
  undefined2 local_246;
  uint local_244;
  undefined4 local_240 [108];
  float local_90 [4];
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  uint local_74;
  byte local_70 [100];
  uint local_c;
  
  iVar26 = *(int *)((int)param_1 + 0x14d8);
  local_c = DAT_00473660 ^ (uint)&stack0xfffffffc;
  iVar27 = *(int *)(*(int *)(iVar26 + 4) + 4);
  sVar1 = *(short *)(iVar27 + 4);
  if (0xb4 < (int)sVar1 - 0x100U) {
    return 0;
  }
  uVar8 = (uint)*(byte *)((int)&PTR_caseD_14f_00411de0 + (int)sVar1);
  local_2a8 = param_1;
  switch(sVar1) {
  case 0x101:
    goto switchD_0040e7c9_caseD_101;
  case 0x102:
    uVar22 = FUN_0044fdb0(uVar8,*(int *)(iVar26 + 4),0);
    *(int *)((int)param_1 + 0xe8) = (int)uVar22;
    return 0;
  case 0x103:
    uVar22 = FUN_0044fdb0(uVar8,*(int *)(iVar26 + 4),0);
    iVar26 = (int)uVar22;
    uVar22 = FUN_0044fdb0(extraout_ECX_03,*(int *)(*(int *)((int)param_1 + 0x14d8) + 4),1);
    FUN_00449630(extraout_ECX_04);
    if ((int)uVar22 < 0) {
      return 0;
    }
    uVar22 = FUN_0044fdb0(extraout_ECX_05,*(int *)(*(int *)((int)param_1 + 0x14d8) + 4),1);
    puVar5 = (undefined4 *)
             FUN_00448e30(*(undefined4 *)(DAT_00477704 + 0x30 + *(int *)((int)param_1 + 0xe8) * 4),
                          (int)uVar22,5);
    *(undefined4 *)((int)param_1 + 0xc0 + iVar26 * 4) = *puVar5;
    uVar6 = extraout_ECX_06;
    if (iVar26 == 0) {
      uVar22 = FUN_0044fdb0(extraout_ECX_06,*(int *)(*(int *)((int)param_1 + 0x14d8) + 4),1);
      *(int *)((int)param_1 + 0xf0) = (int)uVar22;
      *(undefined4 *)((int)param_1 + 0xec) = *(undefined4 *)((int)param_1 + 0xe8);
      uVar6 = extraout_ECX_07;
    }
    iVar27 = FUN_00449450(uVar6);
    goto LAB_0040f103;
  case 0x104:
switchD_0040e7c9_caseD_104:
    iVar26 = *(int *)(iVar27 + 0x10) + 4;
    fVar9 = *(float *)((int)param_1 + 0x2c);
    pfVar15 = local_90;
    for (iVar11 = 0x10; iVar11 != 0; iVar11 = iVar11 + -1) {
      *pfVar15 = 0.0;
      pfVar15 = pfVar15 + 1;
    }
    iVar26 = (int)(iVar26 + (iVar26 >> 0x1f & 3U)) >> 2;
    fVar19 = (float10)FUN_00412aa0(1,*(float *)(iVar27 + 0x10 + iVar26 * 4));
    fVar10 = *(float *)((int)param_1 + 0x30);
    local_90[0] = (float)(fVar19 + (float10)fVar9);
    fVar19 = (float10)FUN_00412aa0(2,*(float *)(iVar27 + 0x14 + iVar26 * 4));
    local_90[1] = (float)(fVar19 + (float10)fVar10);
    uVar22 = FUN_0044ff00(*(int *)((int)param_1 + 0x14d8),
                          *(int *)(*(int *)((int)param_1 + 0x14d8) + 4),3,
                          *(int *)(iVar27 + 0x18 + iVar26 * 4));
    local_7c = (undefined4)uVar22;
    uVar22 = FUN_0044ff00(*(int *)((int)param_1 + 0x14d8),
                          *(int *)(*(int *)((int)param_1 + 0x14d8) + 4),4,
                          *(int *)(iVar27 + 0x1c + iVar26 * 4));
    local_90[3] = (float)uVar22;
    uVar22 = FUN_0044ff00(extraout_ECX_01,*(int *)(*(int *)((int)param_1 + 0x14d8) + 4),5,
                          *(int *)(iVar27 + 0x20 + iVar26 * 4));
    local_80 = (undefined4)uVar22;
    puVar5 = (undefined4 *)((int)param_1 + 0xfc);
    pbVar16 = local_70;
    for (iVar26 = 8; iVar26 != 0; iVar26 = iVar26 + -1) {
      *(undefined4 *)pbVar16 = *puVar5;
      puVar5 = puVar5 + 1;
      pbVar16 = pbVar16 + 4;
    }
    local_78 = 1;
    FUN_0040cfb0(DAT_00477704,(void *)(iVar27 + 0x14));
    return 0;
  case 0x105:
    goto switchD_0040e7c9_caseD_105;
  case 0x106:
    uVar22 = FUN_0044fdb0(uVar8,*(int *)(iVar26 + 4),0);
    iVar26 = (int)uVar22;
    uVar22 = FUN_0044fdb0(extraout_ECX_15,*(int *)(*(int *)((int)param_1 + 0x14d8) + 4),1);
    iVar27 = (int)uVar22;
    FUN_00449630(extraout_ECX_16);
    puVar5 = (undefined4 *)
             FUN_00448e30(*(undefined4 *)(DAT_00477704 + 0x30 + *(int *)((int)param_1 + 0xe8) * 4),
                          iVar27,5);
    uVar6 = *puVar5;
    *(undefined4 *)((int)param_1 + 0xc0 + iVar26 * 4) = uVar6;
    iVar11 = FUN_00449450(uVar6);
    if (iVar26 == 0) {
      *(float *)((int)param_1 + 0x13a4) = *(float *)(iVar11 + 0x50) * *(float *)(iVar11 + 0x40);
      *(float *)((int)param_1 + 0x13a8) = *(float *)(iVar11 + 0x4c) * *(float *)(iVar11 + 0x3c);
    }
    if ((*(byte *)((int)param_1 + 0x1444) & 0x10) != 0) {
      FUN_004495e0();
    }
    if (iVar26 == 0) {
      *(uint *)((int)param_1 + 0x1444) = *(uint *)((int)param_1 + 0x1444) | 0x1000;
      *(int *)((int)param_1 + 0xf4) = iVar27;
      *(int *)((int)param_1 + 0xf0) = iVar27;
      *(undefined4 *)((int)param_1 + 0xf8) = 0;
      *(undefined4 *)((int)param_1 + 0xec) = *(undefined4 *)((int)param_1 + 0xe8);
      return 0;
    }
    break;
  case 0x107:
    uVar22 = FUN_0044fdb0(uVar8,*(int *)(iVar26 + 4),0);
    uVar23 = FUN_0044fdb0(extraout_ECX_08,*(int *)(*(int *)((int)param_1 + 0x14d8) + 4),1);
    FUN_00448e30(*(undefined4 *)(DAT_00477704 + 0x30 + (int)uVar22 * 4),(int)uVar23,6);
    uVar6 = extraout_ECX_09;
    goto LAB_0040ee5b;
  case 0x108:
    uVar22 = FUN_0044fdb0(uVar8,*(int *)(iVar26 + 4),0);
    uVar23 = FUN_0044fdb0(extraout_ECX_12,*(int *)(*(int *)((int)param_1 + 0x14d8) + 4),1);
    FUN_00448e30(*(undefined4 *)(DAT_00477704 + 0x30 + (int)uVar22 * 4),(int)uVar23,6);
    return 0;
  case 0x109:
    if (*(int *)(DAT_00477704 + 0x10) != 0) {
      return 0;
    }
  case 0x100:
    iVar26 = *(int *)(iVar27 + 0x10) + 4;
    pfVar15 = local_90;
    for (iVar11 = 0x10; iVar11 != 0; iVar11 = iVar11 + -1) {
      *pfVar15 = 0.0;
      pfVar15 = pfVar15 + 1;
    }
    iVar26 = (int)(iVar26 + (iVar26 >> 0x1f & 3U)) >> 2;
    if ((*(uint *)((int)param_1 + 0x1444) & 0x40000) == 0) {
      fVar9 = *(float *)((int)param_1 + 0x2c);
      fVar19 = (float10)FUN_00412aa0(1,*(float *)(iVar27 + 0x10 + iVar26 * 4));
      fVar10 = *(float *)((int)param_1 + 0x30);
      local_90[0] = (float)(fVar19 + (float10)fVar9);
      fVar19 = (float10)FUN_00412aa0(2,*(float *)(iVar27 + 0x14 + iVar26 * 4));
      fVar19 = fVar19 + (float10)fVar10;
    }
    else {
      fVar9 = *(float *)((int)param_1 + 0x2c);
      fVar19 = (float10)FUN_00412aa0(1,*(float *)(iVar27 + 0x10 + iVar26 * 4));
      fVar10 = *(float *)((int)param_1 + 0x30);
      local_2b4 = (float)(fVar19 + (float10)fVar9);
      fVar19 = (float10)FUN_00412aa0(2,*(float *)(iVar27 + 0x14 + iVar26 * 4));
      local_2ac = *(float *)((int)param_1 + 0x34);
      local_2b0 = (float)(fVar19 + (float10)fVar10);
      FUN_00401d20();
      D3DXVec3Project(local_90,&local_2b4,&DAT_00491e48,&DAT_00491e08,&DAT_00491dc8,&DAT_00474df0);
      local_90[0] = local_90[0] - _DAT_00470b4c;
      local_90[2] = 0.0;
      fVar19 = (float10)local_90[1] - (float10)_DAT_00470b48;
      param_1 = local_2a8;
    }
LAB_0040e900:
    local_90[1] = (float)fVar19;
    uVar22 = FUN_0044ff00(*(int *)((int)param_1 + 0x14d8),
                          *(int *)(*(int *)((int)param_1 + 0x14d8) + 4),3,
                          *(int *)(iVar27 + 0x18 + iVar26 * 4));
    local_7c = (undefined4)uVar22;
    uVar22 = FUN_0044ff00(*(int *)((int)param_1 + 0x14d8),
                          *(int *)(*(int *)((int)param_1 + 0x14d8) + 4),4,
                          *(int *)(iVar27 + 0x1c + iVar26 * 4));
    local_90[3] = (float)uVar22;
    uVar22 = FUN_0044ff00(extraout_ECX,*(int *)(*(int *)((int)param_1 + 0x14d8) + 4),5,
                          *(int *)(iVar27 + 0x20 + iVar26 * 4));
    local_80 = (undefined4)uVar22;
    puVar5 = (undefined4 *)((int)param_1 + 0xfc);
    pbVar16 = local_70;
    for (iVar26 = 8; iVar26 != 0; iVar26 = iVar26 + -1) {
      *(undefined4 *)pbVar16 = *puVar5;
      puVar5 = puVar5 + 1;
      pbVar16 = pbVar16 + 4;
    }
LAB_0040ecfb:
    FUN_0040cfb0(DAT_00477704,(void *)(iVar27 + 0x14));
    return 0;
  case 0x10a:
    if (*(int *)(DAT_00477704 + 0x10) != 0) {
      return 0;
    }
    goto switchD_0040e7c9_caseD_101;
  case 0x10b:
    if (*(int *)(DAT_00477704 + 0x10) == 0) goto switchD_0040e7c9_caseD_104;
    break;
  case 0x10c:
    if (*(int *)(DAT_00477704 + 0x10) != 0) {
      return 0;
    }
    goto switchD_0040e7c9_caseD_105;
  case 0x10d:
    uVar22 = FUN_0044fdb0(uVar8,*(int *)(iVar26 + 4),0);
    iVar26 = (int)uVar22;
    FUN_00449630(extraout_ECX_17);
    puVar5 = (undefined4 *)
             FUN_00448e30(*(undefined4 *)(DAT_00477704 + 0x30 + *(int *)((int)param_1 + 0xe8) * 4),
                          *(int *)((int)param_1 + 0xf4) + 5,5);
    *(undefined4 *)((int)param_1 + 0xc0 + iVar26 * 4) = *puVar5;
    iVar27 = FUN_00449450(extraout_ECX_18);
LAB_0040f103:
    if (iVar26 == 0) {
      *(float *)((int)param_1 + 0x13a4) = *(float *)(iVar27 + 0x50) * *(float *)(iVar27 + 0x40);
      *(float *)((int)param_1 + 0x13a8) = *(float *)(iVar27 + 0x4c) * *(float *)(iVar27 + 0x3c);
    }
    if ((*(byte *)((int)param_1 + 0x1444) & 0x10) != 0) {
      FUN_004495e0();
      return 0;
    }
    break;
  case 0x10e:
switchD_0040e7c9_caseD_10e:
    iVar26 = *(int *)(iVar27 + 0x10) + 4;
    pfVar15 = local_90;
    for (iVar11 = 0x10; iVar11 != 0; iVar11 = iVar11 + -1) {
      *pfVar15 = 0.0;
      pfVar15 = pfVar15 + 1;
    }
    iVar26 = (int)(iVar26 + (iVar26 >> 0x1f & 3U)) >> 2;
    fVar19 = (float10)FUN_00412aa0(1,*(float *)(iVar27 + 0x10 + iVar26 * 4));
    local_90[0] = (float)(fVar19 + (float10)DAT_00491d7c);
    fVar19 = (float10)FUN_00412aa0(2,*(float *)(iVar27 + 0x14 + iVar26 * 4));
    local_90[1] = (float)(fVar19 + (float10)DAT_00491d80);
    fVar19 = (float10)FUN_00412aa0(3,*(float *)(iVar27 + 0x18 + iVar26 * 4));
    local_90[2] = (float)fVar19;
    uVar22 = FUN_0044ff00(*(int *)((int)param_1 + 0x14d8),
                          *(int *)(*(int *)((int)param_1 + 0x14d8) + 4),4,
                          *(int *)(iVar27 + 0x1c + iVar26 * 4));
    local_7c = (undefined4)uVar22;
    uVar22 = FUN_0044ff00(*(int *)((int)param_1 + 0x14d8),
                          *(int *)(*(int *)((int)param_1 + 0x14d8) + 4),5,
                          *(int *)(iVar27 + 0x20 + iVar26 * 4));
    local_90[3] = (float)uVar22;
    uVar22 = FUN_0044ff00(extraout_ECX_00,*(int *)(*(int *)((int)param_1 + 0x14d8) + 4),6,
                          *(int *)(iVar27 + 0x24 + iVar26 * 4));
    local_80 = (undefined4)uVar22;
    puVar5 = (undefined4 *)((int)param_1 + 0xfc);
    pbVar16 = local_70;
    for (iVar26 = 8; iVar26 != 0; iVar26 = iVar26 + -1) {
      *(undefined4 *)pbVar16 = *puVar5;
      puVar5 = puVar5 + 1;
      pbVar16 = pbVar16 + 4;
    }
    local_74 = local_74 | 1;
    FUN_0040cfb0(DAT_00477704,(void *)(iVar27 + 0x14));
    return 0;
  case 0x10f:
    if (*(int *)(DAT_00477704 + 0x10) == 0) goto switchD_0040e7c9_caseD_10e;
    break;
  case 0x110:
    uVar22 = FUN_0044fdb0(uVar8,*(int *)(iVar26 + 4),0);
    uVar23 = FUN_0044fdb0(extraout_ECX_10,*(int *)(*(int *)((int)param_1 + 0x14d8) + 4),1);
    FUN_00448d00(*(undefined4 *)(DAT_00477704 + 0x30 + (int)uVar22 * 4),(int)uVar23,6);
    uVar6 = extraout_ECX_11;
LAB_0040ee5b:
    iVar26 = FUN_00449450(uVar6);
    if ((*(uint *)((int)param_1 + 0x1444) & 0x40000) == 0) {
      puVar5 = (undefined4 *)FUN_00418810();
      *(undefined4 *)(iVar26 + 0x340) = *puVar5;
      *(undefined4 *)(iVar26 + 0x344) = puVar5[1];
      *(undefined4 *)(iVar26 + 0x348) = puVar5[2];
      return 0;
    }
    *(undefined4 *)(iVar26 + 0x340) = *(undefined4 *)((int)param_1 + 0x2c);
    *(undefined4 *)(iVar26 + 0x344) = *(undefined4 *)((int)param_1 + 0x30);
    *(undefined4 *)(iVar26 + 0x348) = *(undefined4 *)((int)param_1 + 0x34);
    return 0;
  case 0x111:
    uVar22 = FUN_0044fdb0(uVar8,*(int *)(iVar26 + 4),0);
    uVar23 = FUN_0044fdb0(extraout_ECX_13,*(int *)(*(int *)((int)param_1 + 0x14d8) + 4),1);
    FUN_00448e30(*(undefined4 *)(DAT_00477704 + 0x30 + (int)uVar22 * 4),(int)uVar23,6);
    iVar26 = FUN_00449450(extraout_ECX_14);
    if ((*(uint *)((int)param_1 + 0x1444) & 0x40000) == 0) {
      puVar5 = (undefined4 *)FUN_00418810();
      *(undefined4 *)(iVar26 + 0x340) = *puVar5;
      *(undefined4 *)(iVar26 + 0x344) = puVar5[1];
      *(undefined4 *)(iVar26 + 0x348) = puVar5[2];
    }
    else {
      *(undefined4 *)(iVar26 + 0x340) = *(undefined4 *)((int)param_1 + 0x2c);
      *(undefined4 *)(iVar26 + 0x344) = *(undefined4 *)((int)param_1 + 0x30);
      *(undefined4 *)(iVar26 + 0x348) = *(undefined4 *)((int)param_1 + 0x34);
    }
    fVar19 = FUN_0044fe40(2.8026e-45);
    *(float *)(iVar26 + 0x2c) = (float)fVar19;
    *(uint *)(iVar26 + 0x35c) = *(uint *)(iVar26 + 0x35c) | 4;
    return 0;
  case 0x118:
  case 0x11a:
    pfVar15 = (float *)((int)param_1 + 0x58);
    if (sVar1 != 0x118) {
      pfVar15 = (float *)((int)param_1 + 0x84);
    }
    fVar19 = FUN_0044fe40(0.0);
    fVar21 = FUN_0044fe40(1.4013e-45);
    if ((float)_DAT_00470d58 < (float)fVar19) {
      *pfVar15 = (float)fVar19;
    }
    if ((float10)_DAT_00470d58 < fVar21) {
      pfVar15[1] = (float)fVar21;
    }
    pfVar15[10] = (float)((uint)pfVar15[10] & 0xfffffffe);
    *(float *)((int)param_1 + 0x2c) =
         *(float *)((int)param_1 + 0x84) + *(float *)((int)param_1 + 0x58);
    *(float *)((int)param_1 + 0x30) =
         *(float *)((int)param_1 + 0x88) + *(float *)((int)param_1 + 0x5c);
    *(float *)((int)param_1 + 0x34) =
         *(float *)((int)param_1 + 0x8c) + *(float *)((int)param_1 + 0x60);
    return 0;
  case 0x119:
  case 0x11b:
    pfVar15 = (float *)((int)param_1 + 0x58);
    if (sVar1 == 0x119) {
      pfVar12 = (float *)((int)param_1 + 0x13c);
    }
    else {
      pfVar15 = (float *)((int)param_1 + 0x84);
      pfVar12 = (float *)((int)param_1 + 0x188);
    }
    fVar19 = FUN_0044fe40(2.8026e-45);
    fVar10 = (float)fVar19;
    fVar19 = FUN_0044fe40(4.2039e-45);
    fVar9 = (float)fVar19;
    uVar22 = FUN_0044fdb0(extraout_ECX_19,*(int *)(*(int *)((int)param_1 + 0x14d8) + 4),0);
    pfVar12[0x11] = (float)uVar22;
    pfVar12[6] = DAT_00491c14;
    pfVar12[7] = DAT_00491c18;
    pfVar12[8] = DAT_00491c1c;
    pfVar12[9] = DAT_00491c14;
    pfVar12[10] = DAT_00491c18;
    pfVar12[0xb] = DAT_00491c1c;
    uVar22 = FUN_0044fdb0(pfVar12 + 9,*(int *)(*(int *)((int)param_1 + 0x14d8) + 4),1);
    fVar2 = (float)_DAT_00470d58;
    pfVar12[0x12] = (float)uVar22;
    *pfVar12 = *pfVar15;
    pfVar12[1] = pfVar15[1];
    pfVar12[2] = pfVar15[2];
    if (fVar9 <= fVar2) {
      fVar9 = pfVar15[1];
    }
    if (fVar10 <= (float)_DAT_00470d58) {
      fVar10 = *pfVar15;
    }
    pfVar12[3] = fVar10;
    pfVar12[4] = fVar9;
    local_2ac = 0.0;
    pfVar12[5] = 0.0;
    local_2b4 = fVar10;
    local_2b0 = fVar9;
    FUN_004050d0();
    pfVar15[10] = (float)((uint)pfVar15[10] & 0xfffffffe);
    return 0;
  case 0x11c:
  case 0x11e:
    iVar26 = (int)param_1 + 0x58;
    if (sVar1 != 0x11c) {
      iVar26 = (int)param_1 + 0x84;
    }
    fVar19 = FUN_0044fe40(0.0);
    local_2bc = (float)fVar19;
    fVar19 = FUN_0044fe40(1.4013e-45);
    if ((float)_DAT_00470d58 < local_2bc) {
      if ((*(uint *)((int)param_1 + 0x1444) & 0x800) != 0) {
        fVar21 = (float10)FUN_0044bc70(local_2bc - _DAT_00470b94);
        fVar21 = (float10)FUN_0044bc70((float)((float10)_DAT_00470b94 - fVar21));
        local_2bc = (float)fVar21;
      }
      FUN_00413170(iVar26,local_2bc);
    }
    if ((float)_DAT_00470d58 < (float)fVar19) {
      *(float *)(iVar26 + 0x18) = (float)fVar19;
    }
    *(uint *)(iVar26 + 0x28) = *(uint *)(iVar26 + 0x28) & 0xfffffffe;
    return 0;
  case 0x11d:
  case 0x11f:
    iVar26 = (int)param_1 + 0x58;
    if (sVar1 == 0x11d) {
      pfVar15 = (float *)((int)param_1 + 0x1d4);
    }
    else {
      iVar26 = (int)param_1 + 0x84;
      pfVar15 = (float *)((int)param_1 + 0x210);
    }
    fVar19 = FUN_0044fe40(2.8026e-45);
    local_2c8 = (float)fVar19;
    fVar19 = FUN_0044fe40(4.2039e-45);
    local_2c4 = (float)fVar19;
    uVar22 = FUN_0044fdb0(extraout_ECX_20,*(int *)(*(int *)((int)param_1 + 0x14d8) + 4),1);
    fVar9 = (float)_DAT_00470d58;
    pfVar15[0xe] = (float)uVar22;
    if ((float)uVar22 == 9.80909e-45) {
      if (local_2c8 <= fVar9) {
        local_2c8 = 0.0;
      }
      if (local_2c4 <= (float)_DAT_00470d58) {
        local_2c4 = 0.0;
      }
    }
    else {
      if (local_2c8 <= fVar9) {
        fVar19 = (float10)*(float *)(iVar26 + 0x1c);
      }
      else {
        fVar19 = (float10)local_2c8;
        if ((*(uint *)((int)param_1 + 0x1444) & 0x800) != 0) {
          fVar19 = (float10)FUN_0044bc70((float)(fVar19 - (float10)_DAT_00470b94));
          fVar19 = (float10)FUN_0044bc70((float)((float10)_DAT_00470b94 - fVar19));
        }
      }
      local_2c8 = (float)fVar19;
      if (local_2c4 <= (float)_DAT_00470d58) {
        local_2c4 = *(float *)(iVar26 + 0x18);
      }
    }
    fVar9 = *(float *)(iVar26 + 0x1c);
    local_2a4 = *(float *)(iVar26 + 0x18);
    local_2a8 = fVar9;
    if (_DAT_00470b18 <= ABS(fVar9 - local_2c8)) {
      if (local_2c8 <= fVar9) {
        local_2c8 = local_2c8 + _DAT_00470b14;
      }
      else {
        local_2a8 = fVar9 + _DAT_00470b14;
      }
    }
    uVar22 = FUN_0044fdb0(fVar9,*(int *)(*(int *)((int)param_1 + 0x14d8) + 4),0);
    pfVar15[0xd] = (float)uVar22;
    pfVar15[4] = DAT_00491c20;
    pfVar15[5] = DAT_00491c24;
    pfVar15[6] = DAT_00491c20;
    fVar9 = local_2a8;
    fVar10 = local_2a4;
    goto LAB_0040fc07;
  case 0x120:
  case 0x122:
    puVar5 = (undefined4 *)((int)param_1 + 0x58);
    if (sVar1 != 0x120) {
      puVar5 = (undefined4 *)((int)param_1 + 0x84);
    }
    fVar19 = FUN_0044fe40(0.0);
    fVar21 = FUN_0044fe40(1.4013e-45);
    fVar20 = FUN_0044fe40(2.8026e-45);
    local_2a8 = (float)fVar20;
    fVar20 = FUN_0044fe40(4.2039e-45);
    if ((*(byte *)(puVar5 + 10) & 1) == 0) {
      puVar5[3] = *puVar5;
      puVar5[4] = puVar5[1];
      puVar5[5] = puVar5[2];
    }
    if ((float)_DAT_00470d58 < (float)fVar19) {
      FUN_00413170((int)puVar5,(float)fVar19);
    }
    if ((float)_DAT_00470d58 < (float)fVar21) {
      puVar5[6] = (float)fVar21;
    }
    if ((float)_DAT_00470d58 < local_2a8) {
      puVar5[8] = local_2a8;
    }
    if ((float)_DAT_00470d58 < (float)fVar20) {
      puVar5[9] = (float)fVar20;
    }
    puVar5[10] = puVar5[10] | 1;
    return 0;
  case 0x121:
  case 0x123:
    puVar5 = (undefined4 *)((int)param_1 + 0x58);
    puVar14 = (undefined4 *)((int)param_1 + 0x1d4);
    if (sVar1 == 0x121) {
      puVar13 = (undefined4 *)((int)param_1 + 0x24c);
    }
    else {
      puVar5 = (undefined4 *)((int)param_1 + 0x84);
      puVar14 = (undefined4 *)((int)param_1 + 0x210);
      puVar13 = (undefined4 *)((int)param_1 + 0x288);
    }
    fVar19 = FUN_0044fe40(2.8026e-45);
    local_2a8 = (float)fVar19;
    fVar19 = FUN_0044fe40(4.2039e-45);
    fVar9 = (float)fVar19;
    fVar19 = FUN_0044fe40(5.60519e-45);
    fVar10 = (float)fVar19;
    fVar19 = FUN_0044fe40(7.00649e-45);
    if (fVar9 <= (float)_DAT_00470d58) {
      fVar9 = (float)puVar5[6];
    }
    if (local_2a8 <= (float)_DAT_00470d58) {
      local_2a8 = (float)puVar5[7];
    }
    local_2a4 = (float)puVar5[6];
    if (fVar19 <= (float10)_DAT_00470d58) {
      fVar19 = (float10)(float)puVar5[9];
    }
    if (fVar10 <= (float)_DAT_00470d58) {
      fVar10 = (float)puVar5[8];
    }
    uVar6 = puVar5[9];
    uVar4 = puVar5[8];
    local_2b0 = (float)fVar19;
    local_2b4 = fVar10;
    local_29c = local_2a8;
    local_2a8 = (float)puVar5[7];
    local_298 = fVar9;
    uVar22 = FUN_0044fdb0(puVar5,*(int *)(*(int *)((int)param_1 + 0x14d8) + 4),0);
    uVar23 = FUN_0044fdb0(extraout_ECX_21,*(int *)(*(int *)((int)param_1 + 0x14d8) + 4),1);
    puVar14[0xd] = (int)uVar22;
    puVar14[4] = DAT_00491c20;
    puVar14[5] = DAT_00491c24;
    puVar14[6] = DAT_00491c20;
    fVar9 = DAT_00491c24;
    *puVar14 = local_2a8;
    puVar14[7] = fVar9;
    puVar14[3] = local_298;
    puVar14[0xe] = (int)uVar23;
    puVar14[1] = local_2a4;
    puVar14[2] = local_29c;
    FUN_00412db0();
    puVar13[0xd] = (int)uVar22;
    puVar13[4] = DAT_00491c20;
    puVar13[5] = DAT_00491c24;
    puVar13[6] = DAT_00491c20;
    fVar9 = DAT_00491c24;
    *puVar13 = uVar4;
    puVar13[7] = fVar9;
    puVar13[3] = local_2b0;
    puVar13[0xe] = (int)uVar23;
    puVar13[1] = uVar6;
    puVar13[2] = local_2b4;
    FUN_00412db0();
    puVar5[3] = *puVar5;
    puVar5[4] = puVar5[1];
    puVar5[5] = puVar5[2];
    puVar5[10] = puVar5[10] | 1;
    return 0;
  case 0x124:
  case 0x125:
    iVar26 = (int)param_1 + 0x58;
    if (sVar1 == 0x124) {
      pfVar15 = (float *)((int)param_1 + 0x1d4);
    }
    else {
      iVar26 = (int)param_1 + 0x84;
      pfVar15 = (float *)((int)param_1 + 0x210);
    }
    fVar9 = *(float *)((int)param_1 + 0x13b4) * _DAT_00470d40;
    if (*(float *)((int)param_1 + 0x13ac) - fVar9 <= *(float *)((int)param_1 + 0x2c)) {
      if (*(float *)((int)param_1 + 0x2c) <= fVar9 + *(float *)((int)param_1 + 0x13ac)) {
        if (*(float *)((int)param_1 + 0x2c) < *(float *)(DAT_00477834 + 0x3c0)) {
          fVar19 = FUN_0044bb90(&DAT_004918b0);
          fVar19 = fVar19 * (float10)_DAT_00470b94;
          uVar6 = extraout_ECX_23;
          goto LAB_0040fb39;
        }
        fVar19 = FUN_0044bb90(&DAT_004918b0);
        fVar19 = fVar19 * (float10)_DAT_00470b18 * (float10)_DAT_00470b0c;
      }
      else {
        fVar19 = FUN_0044bb90(&DAT_004918b0);
        fVar19 = fVar19 * (float10)_DAT_00470b18 * (float10)_DAT_00470cc4;
      }
      fVar19 = (float10)FUN_0044bc70((float)(fVar19 + (float10)_DAT_00470b18));
      uVar6 = extraout_ECX_24;
    }
    else {
      fVar19 = FUN_0044bb90(&DAT_004918b0);
      fVar19 = fVar19 * (float10)_DAT_00470d50;
      uVar6 = extraout_ECX_22;
    }
LAB_0040fb39:
    local_2bc = (float)fVar19;
    fVar9 = *(float *)((int)param_1 + 0x13b8) * _DAT_00470d40;
    if (*(float *)((int)param_1 + 0x13b0) - fVar9 <= *(float *)((int)param_1 + 0x30)) {
      if (fVar9 + *(float *)((int)param_1 + 0x13b0) < *(float *)((int)param_1 + 0x30)) {
        local_2bc = -ABS(local_2bc);
      }
    }
    else {
      local_2bc = ABS(local_2bc);
    }
    uVar22 = FUN_0044fdb0(uVar6,*(int *)(*(int *)((int)param_1 + 0x14d8) + 4),1);
    pfVar15[0xe] = (float)uVar22;
    local_2c4 = 0.0;
    local_2c8 = local_2bc;
    local_2b4 = local_2bc;
    fVar19 = FUN_0044fe40(2.8026e-45);
    local_2b0 = (float)fVar19;
    uVar22 = FUN_0044fdb0(extraout_ECX_25,*(int *)(*(int *)((int)param_1 + 0x14d8) + 4),0);
    pfVar15[0xd] = (float)uVar22;
    pfVar15[4] = DAT_00491c20;
    pfVar15[5] = DAT_00491c24;
    pfVar15[6] = DAT_00491c20;
    fVar9 = local_2b4;
    fVar10 = local_2b0;
LAB_0040fc07:
    pfVar15[7] = DAT_00491c24;
    *pfVar15 = fVar9;
    pfVar15[1] = fVar10;
    pfVar15[2] = local_2c8;
    pfVar15[3] = local_2c4;
    FUN_00412db0();
    *(uint *)(iVar26 + 0x28) = *(uint *)(iVar26 + 0x28) & 0xfffffffe;
    return 0;
  case 0x126:
    goto switchD_0040e7c9_caseD_126;
  case 0x127:
    iVar26 = *(int *)(DAT_00477704 + 0x10);
    *(undefined4 *)((int)param_1 + 0x84) = *(undefined4 *)(iVar26 + 0x1068);
    *(undefined4 *)((int)param_1 + 0x88) = *(undefined4 *)(iVar26 + 0x106c);
    *(undefined4 *)((int)param_1 + 0x8c) = *(undefined4 *)(iVar26 + 0x1070);
    return 0;
  case 0x128:
  case 0x129:
    pfVar15 = (float *)((int)param_1 + 0x58);
    if (sVar1 != 0x128) {
      pfVar15 = (float *)((int)param_1 + 0x84);
    }
    fVar19 = FUN_0044fe40(0.0);
    fVar21 = FUN_0044fe40(1.4013e-45);
    local_2a8 = (float)fVar21;
    fVar21 = FUN_0044fe40(2.8026e-45);
    *pfVar15 = (float)fVar19 + *pfVar15;
    pfVar15[1] = local_2a8 + pfVar15[1];
    pfVar15[2] = (float)(fVar21 + (float10)pfVar15[2]);
    return 0;
  case 0x12a:
  case 299:
    iVar26 = (int)param_1 + 0x58;
    if (sVar1 != 0x12a) {
      iVar26 = (int)param_1 + 0x84;
    }
    fVar19 = FUN_0044fe40(0.0);
    fVar21 = FUN_0044fe40(1.4013e-45);
    if ((float)_DAT_00470d58 < (float)fVar19) {
      *(float *)(iVar26 + 0xc) = (float)fVar19;
    }
    if ((float10)_DAT_00470d58 < fVar21) {
      *(float *)(iVar26 + 0x10) = (float)fVar21;
    }
    goto switchD_0040e7c9_caseD_126;
  case 0x140:
    fVar19 = FUN_0044fe40(0.0);
    *(float *)((int)param_1 + 0xb0) = (float)fVar19;
    fVar19 = FUN_0044fe40(1.4013e-45);
    *(float *)((int)param_1 + 0xb4) = (float)fVar19;
    return 0;
  case 0x141:
    fVar19 = FUN_0044fe40(0.0);
    *(float *)((int)param_1 + 0xb8) = (float)fVar19;
    fVar19 = FUN_0044fe40(1.4013e-45);
    *(float *)((int)param_1 + 0xbc) = (float)fVar19;
    return 0;
  case 0x142:
    uVar22 = FUN_0044fdb0(uVar8,*(int *)(iVar26 + 4),0);
    uVar8 = *(uint *)((int)param_1 + 0x1444) | (uint)uVar22;
    *(uint *)((int)param_1 + 0x1444) = uVar8;
    if ((uVar8 & 0x10) != 0) {
      iVar26 = 10;
      do {
        FUN_004495e0();
        iVar26 = iVar26 + -1;
      } while (iVar26 != 0);
      return 0;
    }
    break;
  case 0x143:
    uVar22 = FUN_0044fdb0(uVar8,*(int *)(iVar26 + 4),0);
    uVar8 = *(uint *)((int)param_1 + 0x1444) & ~(uint)uVar22;
    *(uint *)((int)param_1 + 0x1444) = uVar8;
    if ((uVar8 & 0x10) == 0) {
      iVar26 = 10;
      do {
        FUN_00449590();
        iVar26 = iVar26 + -1;
      } while (iVar26 != 0);
      return 0;
    }
    break;
  case 0x144:
    *(uint *)((int)param_1 + 0x1444) = *(uint *)((int)param_1 + 0x1444) | 0x200;
    fVar19 = FUN_0044fe40(0.0);
    *(float *)((int)param_1 + 0x13ac) = (float)fVar19;
    fVar19 = FUN_0044fe40(1.4013e-45);
    *(float *)((int)param_1 + 0x13b0) = (float)fVar19;
    fVar19 = FUN_0044fe40(2.8026e-45);
    *(float *)((int)param_1 + 0x13b4) = (float)fVar19;
    fVar19 = FUN_0044fe40(4.2039e-45);
    *(float *)((int)param_1 + 0x13b8) = (float)fVar19;
    return 0;
  case 0x145:
    *(uint *)((int)param_1 + 0x1444) = *(uint *)((int)param_1 + 0x1444) & 0xfffffdff;
    return 0;
  case 0x146:
    puVar5 = (undefined4 *)((int)param_1 + 0x13d0);
    for (iVar26 = 0xc; iVar26 != 0; iVar26 = iVar26 + -1) {
      *puVar5 = 0;
      puVar5 = puVar5 + 1;
    }
    return 0;
  case 0x147:
    uVar22 = FUN_0044fdb0(uVar8,*(int *)(iVar26 + 4),0);
    iVar26 = (int)uVar22;
    if ((char)((uint)*(undefined4 *)((int)param_1 + 0x1444) >> 8) < '\0') {
      if (iVar26 == 1) {
        iVar26 = 10;
      }
      else if (iVar26 == 4) {
        iVar26 = 0xb;
      }
    }
    uVar22 = FUN_0044fdb0(extraout_ECX_27,*(int *)(*(int *)((int)param_1 + 0x14d8) + 4),1);
    *(int *)((int)param_1 + 0x13cc + iVar26 * 4) = (int)uVar22;
    return 0;
  case 0x148:
    fVar19 = FUN_0044fe40(1.4013e-45);
    fVar21 = FUN_0044fe40(0.0);
    *(float *)((int)param_1 + 0x1400) = (float)fVar21;
    *(float *)((int)param_1 + 0x1404) = (float)fVar19;
    return 0;
  case 0x149:
    FUN_0040c9a0();
    return 0;
  case 0x14a:
    uVar22 = FUN_0044fdb0(uVar8,*(int *)(iVar26 + 4),0);
    iVar26 = (int)uVar22;
    if ((char)((uint)*(undefined4 *)((int)param_1 + 0x1444) >> 8) < '\0') {
      if (iVar26 == 1) {
        *(undefined4 *)((int)param_1 + 0x13cc) = 10;
        return 0;
      }
      if (iVar26 == 4) {
        iVar26 = 0xb;
      }
    }
    *(int *)((int)param_1 + 0x13cc) = iVar26;
    return 0;
  case 0x14b:
    uVar22 = FUN_0044fdb0(uVar8,*(int *)(iVar26 + 4),0);
    *(int *)((int)param_1 + 0x13c0) = (int)uVar22;
    *(int *)((int)param_1 + 0x13c4) = (int)uVar22;
    iVar26 = DAT_0047770c;
    *(undefined4 *)(DAT_0047770c + 0x9e94) = 0;
    *(undefined4 *)(iVar26 + 0x9e98) = 0;
    *(undefined4 *)(iVar26 + 0x9e9c) = 0;
    *(undefined4 *)(iVar26 + 0x9ea0) = 0;
    *(undefined4 *)(iVar26 + 0x9ea4) = 0;
    *(undefined4 *)(iVar26 + 0x9ea8) = 0;
    *(undefined4 *)(iVar26 + 0x9eac) = 0;
    *(undefined4 *)(iVar26 + 0x9eb0) = 0;
    *(undefined4 *)((int)param_1 + 0x13c8) = *(undefined4 *)((int)param_1 + 0x13c0);
    return 0;
  case 0x14c:
    uVar22 = FUN_0044fdb0(uVar8,*(int *)(iVar26 + 4),0);
    iVar26 = DAT_00477704;
    iVar27 = (int)uVar22;
    if (iVar27 < 0) {
      if ((char)((uint)*(undefined4 *)((int)param_1 + 0x1444) >> 8) < '\0') {
        *(undefined4 *)(DAT_00477704 + 0x10 + *(int *)((int)param_1 + 0x1450) * 4) = 0;
      }
      *(uint *)((int)param_1 + 0x1444) = *(uint *)((int)param_1 + 0x1444) & 0xffff7fff;
      return 0;
    }
    *(uint *)((int)param_1 + 0x1444) = *(uint *)((int)param_1 + 0x1444) | 0x8000;
    *(undefined4 *)(iVar26 + 0x10 + iVar27 * 4) = *(undefined4 *)((int)param_1 + 0x14d8);
    *(int *)((int)param_1 + 0x1450) = iVar27;
    return 0;
  case 0x14d:
    FUN_00405410(0);
    return 0;
  case 0x14e:
    uVar22 = FUN_0044fdb0(uVar8,*(int *)(iVar26 + 4),2);
    uVar23 = FUN_0044fdb0(extraout_ECX_48,*(int *)(*(int *)((int)param_1 + 0x14d8) + 4),1);
    uVar24 = FUN_0044fdb0(extraout_ECX_49,*(int *)(*(int *)((int)param_1 + 0x14d8) + 4),0);
    FUN_00412720((int)uVar23,(int)uVar24,(int)uVar22);
    return 0;
  case 0x14f:
    uVar22 = FUN_0044fdb0(uVar8,*(int *)(iVar26 + 4),0);
    FUN_00405410((int)uVar22);
    return 0;
  case 0x150:
    FUN_0044fdb0(uVar8,*(int *)(iVar26 + 4),0);
    FUN_0043dd10();
    return 0;
  case 0x151:
    uVar22 = FUN_0044fdb0(uVar8,*(int *)(iVar26 + 4),2);
    uVar6 = (undefined4)uVar22;
    uVar22 = FUN_0044fdb0(extraout_ECX_50,*(int *)(*(int *)((int)param_1 + 0x14d8) + 4),1);
    uVar4 = (undefined4)uVar22;
    uVar28 = 0;
    uVar22 = FUN_0044fdb0(extraout_ECX_51,*(int *)(*(int *)((int)param_1 + 0x14d8) + 4),0);
    FUN_0043c8b0(1,(int)uVar22,uVar4,uVar6,uVar28);
    return 0;
  case 0x152:
    FUN_0044fdb0(uVar8,*(int *)(iVar26 + 4),0);
    FUN_00415db0();
    FUN_00408210(0);
    FUN_0041c850();
    FUN_0040e6a0(DAT_00477704);
    return 0;
  case 0x153:
    if ((*(int *)(DAT_0047770c + 0x9eb8) != 0) &&
       (*(int *)(*(int *)(DAT_0047770c + 0x9eb8) + 0x78) == 0)) {
      return 0xffffffff;
    }
    break;
  case 0x154:
    if (*(int *)(DAT_00477704 + 0x10) != 0) {
      return 0xffffffff;
    }
    break;
  case 0x155:
    uVar22 = FUN_0044fdb0(uVar8,*(int *)(iVar26 + 4),0);
    *(int *)(((int)uVar22 + 0x24a) * 0x10 + *(int *)((int)param_1 + 0x14d8)) = iVar27 + 0x18;
    return 0;
  case 0x156:
  case 0x15c:
  case 0x165:
  case 0x166:
  case 0x167:
    local_2a8 = *(float *)(iVar27 + 0x1c);
    iVar17 = 0;
    bVar3 = 0x77;
    local_29d = '\a';
    iVar11 = iVar27 + 0x20;
    if (0 < (int)local_2a8) {
      do {
        *(byte *)((int)local_90 + iVar17) =
             ((byte *)((int)local_90 + iVar17))[(iVar27 + 0x20) - (int)local_90] ^ bVar3;
        bVar3 = bVar3 + local_29d;
        local_29d = local_29d + '\x10';
        iVar17 = iVar17 + 1;
        iVar11 = (int)local_2a8;
      } while (iVar17 < (int)local_2a8);
    }
    uVar22 = FUN_0044fdb0(iVar11,*(int *)(iVar26 + 4),0);
    iVar26 = (int)uVar22;
    sVar1 = *(short *)(iVar27 + 4);
    if (sVar1 == 0x165) {
      iVar26 = iVar26 + DAT_00474c74;
      iVar27 = extraout_ECX_52;
    }
    else if (sVar1 == 0x166) {
      iVar26 = iVar26 + -1 + DAT_00474c74;
      iVar27 = DAT_00474c74;
    }
    else {
      iVar27 = extraout_ECX_52;
      if (sVar1 == 0x167) {
        iVar26 = iVar26 + -2 + DAT_00474c74;
        iVar27 = extraout_ECX_52;
      }
    }
    FUN_0044fdb0(iVar27,*(int *)(*(int *)((int)param_1 + 0x14d8) + 4),2);
    uVar22 = FUN_0044fdb0(extraout_ECX_53,*(int *)(*(int *)((int)param_1 + 0x14d8) + 4),1);
    FUN_00409280(DAT_004776f4,iVar26,(char *)local_90,(int)uVar22);
    return 0;
  case 0x157:
    FUN_00409c00(uVar8);
    return 0;
  case 0x158:
    uVar22 = FUN_00412a00(0);
    FUN_00412ed0((int)uVar22);
    return 0;
  case 0x159:
    FUN_0040e6a0(DAT_00477704);
    return 0;
  case 0x15a:
    fVar19 = FUN_0044fe40(0.0);
    *(float *)((int)param_1 + 0x1454) = (float)(fVar19 * fVar19);
    break;
  case 0x15b:
    uVar22 = FUN_0044fdb0(uVar8,*(int *)(iVar26 + 4),2);
    fVar19 = FUN_0044fe40(1.4013e-45);
    local_2a8 = (float)fVar19;
    iVar26 = *(int *)((int)param_1 + 0x13c4);
    uVar23 = FUN_0044fdb0(extraout_ECX_26,*(int *)(*(int *)((int)param_1 + 0x14d8) + 4),0);
    iVar27 = DAT_0047770c;
    *(int *)(DAT_0047770c + 0x9e98 + (int)uVar23 * 8) = (int)uVar22;
    *(float *)(iVar27 + 0x9e94 + (int)uVar23 * 8) = local_2a8 / (float)iVar26;
    return 0;
  case 0x15d:
    if (DAT_00474c98 < 0x200) {
      fVar9 = 0.0;
      if (DAT_00474c98 < -0x1ff) goto LAB_0041190c;
    }
    else {
      fVar9 = 2.8026e-45;
    }
    goto LAB_00411951;
  case 0x15e:
    if (599 < DAT_00474c98) {
switchD_004100f8_caseD_3:
      fVar9 = 5.60519e-45;
      goto LAB_0041190c;
    }
    if (199 < DAT_00474c98) goto switchD_004100f8_caseD_2;
    if (DAT_00474c98 < -200) {
      if (DAT_00474c98 < -400) {
        fVar9 = 0.0;
        goto LAB_0041190c;
      }
      goto LAB_0041194c;
    }
switchD_004100f8_caseD_1:
    fVar9 = 2.8026e-45;
LAB_0041190c:
    fVar19 = FUN_0044fe40(fVar9);
    pfVar15 = (float *)FUN_00450070(0);
    *pfVar15 = (float)fVar19;
    return 0;
  case 0x15f:
    fVar19 = FUN_0044fe40(1.4013e-45);
    fVar21 = FUN_0044fe40(2.8026e-45);
    local_2a8 = (float)fVar21;
    pfVar15 = (float *)FUN_00450070(0);
    *pfVar15 = (local_2a8 - (float)fVar19) * ((float)DAT_00474c98 + _DAT_00470d4c) * _DAT_00470d48 +
               (float)fVar19;
    return 0;
  case 0x160:
    if (0x1ff < DAT_00474c98) {
LAB_00411ab8:
      puVar5 = (undefined4 *)FUN_00412a10(0);
      uVar22 = FUN_00412a00(2);
      *puVar5 = (int)uVar22;
      return 0;
    }
    goto LAB_00411a15;
  case 0x161:
    if (599 < DAT_00474c98) {
      puVar5 = (undefined4 *)FUN_00412a10(0);
      uVar22 = FUN_00412a00(4);
      *puVar5 = (int)uVar22;
      return 0;
    }
    if (199 < DAT_00474c98) {
      puVar5 = (undefined4 *)FUN_00412a10(0);
      uVar22 = FUN_00412a00(3);
      *puVar5 = (int)uVar22;
      return 0;
    }
    if (-0xc9 < DAT_00474c98) goto LAB_00411ab8;
    if (-0x191 < DAT_00474c98) {
      puVar5 = (undefined4 *)FUN_00412a10(0);
      uVar22 = FUN_00412a00(1);
      *puVar5 = (int)uVar22;
      return 0;
    }
LAB_00411a15:
    puVar5 = (undefined4 *)FUN_00412a10(0);
    uVar22 = FUN_00412a00(0);
    *puVar5 = (int)uVar22;
    return 0;
  case 0x162:
    uVar22 = FUN_00412a00(1);
    uVar23 = FUN_00412a00(2);
    piVar7 = (int *)FUN_00412a10(0);
    iVar26 = ((int)uVar23 - (int)uVar22) * (DAT_00474c98 + 0x400);
    *piVar7 = ((int)(iVar26 + (iVar26 >> 0x1f & 0x7ffU)) >> 0xb) + (int)uVar22;
    return 0;
  case 0x163:
    switch(DAT_00474c74) {
    case 0:
      iVar27 = 1;
      break;
    case 1:
      iVar27 = 2;
      break;
    case 2:
      iVar27 = 3;
      break;
    case 3:
    case 4:
      iVar27 = 4;
      break;
    default:
      goto switchD_0040e7c9_caseD_112;
    }
    uVar22 = FUN_0044fdb0(uVar8,*(int *)(iVar26 + 4),iVar27);
    puVar5 = (undefined4 *)FUN_00412a10(0);
    *puVar5 = (int)uVar22;
    return 0;
  case 0x164:
    switch(DAT_00474c74) {
    case 0:
LAB_0041194c:
      fVar9 = 1.4013e-45;
      break;
    case 1:
      goto switchD_004100f8_caseD_1;
    case 2:
switchD_004100f8_caseD_2:
      fVar9 = 4.2039e-45;
      break;
    case 3:
      goto switchD_004100f8_caseD_3;
    case 4:
      fVar9 = 5.60519e-45;
      break;
    default:
      goto switchD_0040e7c9_caseD_112;
    }
LAB_00411951:
    fVar19 = FUN_0044fe40(fVar9);
LAB_00411956:
    pfVar15 = (float *)FUN_00450070(0);
    *pfVar15 = (float)fVar19;
    return 0;
  case 0x168:
    uVar22 = FUN_00412a00(0);
    *(int *)(DAT_0047770c + 0x9e90) = (int)uVar22;
    return 0;
  case 0x169:
    uVar22 = FUN_0044fdb0(uVar8,*(int *)(iVar26 + 4),0);
    FUN_00405410((int)uVar22);
    return 0;
  case 0x16a:
    *(uint *)(DAT_004776f4 + 0x378c) = *(uint *)(DAT_004776f4 + 0x378c) | 8;
    return 0;
  case 0x16b:
    FUN_0040cea0(uVar8);
    return 0;
  case 0x16c:
    uVar22 = FUN_0044fdb0(uVar8,*(int *)(iVar26 + 4),0);
    *(uint *)((int)param_1 + 0x1444) =
         *(uint *)((int)param_1 + 0x1444) ^
         ((int)uVar22 << 0x13 ^ *(uint *)((int)param_1 + 0x1444)) & 0x80000;
    return 0;
  case 0x16d:
    FUN_0041c7d0();
    return 0;
  case 0x16e:
    uVar22 = FUN_00412a00(0);
    *(uint *)((int)param_1 + 0x1444) =
         *(uint *)((int)param_1 + 0x1444) ^
         ((int)uVar22 << 0x14 ^ *(uint *)((int)param_1 + 0x1444)) & 0x100000;
    uVar22 = FUN_00412a00(1);
    *(int *)((int)param_1 + 0x1448) = (int)uVar22;
    *(uint *)((int)param_1 + 0x1444) = *(uint *)((int)param_1 + 0x1444) & 0xffdfffff;
    *(undefined4 *)((int)param_1 + 0x144c) = *(undefined4 *)((int)param_1 + 0xf4);
    return 0;
  case 0x16f:
    fVar19 = FUN_0044fe40(0.0);
    DAT_00476f78 = (float)fVar19;
    return 0;
  case 0x170:
    if (DAT_00474c74 == 0) {
      uVar22 = FUN_00412a00(0);
      fVar9 = (float)(int)uVar22;
    }
    else if (DAT_00474c74 == 1) {
      uVar22 = FUN_00412a00(1);
      fVar9 = (float)(int)uVar22;
    }
    else if (DAT_00474c74 == 2) {
      uVar22 = FUN_00412a00(2);
      fVar9 = (float)(int)uVar22;
    }
    else {
      uVar22 = FUN_00412a00(3);
      fVar9 = (float)(int)uVar22;
    }
    pfVar15 = *(float **)(*(int *)((int)param_1 + 0x14d8) + 4);
    *pfVar15 = *pfVar15 - fVar9;
    break;
  case 400:
    uVar22 = FUN_0044fdb0(uVar8,*(int *)(iVar26 + 4),0);
    iVar26 = (int)uVar22;
    iVar11 = iVar26 * 0x210 + (int)param_1;
    puVar5 = (undefined4 *)(iVar11 + 0x2c4);
    for (iVar27 = 0x84; iVar27 != 0; iVar27 = iVar27 + -1) {
      *puVar5 = 0;
      puVar5 = puVar5 + 1;
    }
    *(undefined2 *)(iVar11 + 0x4b8) = 1;
    *(undefined2 *)(iVar11 + 0x4ba) = 1;
    *(undefined4 *)(iVar11 + 0x2d4) = 0;
    *(undefined4 *)(iVar11 + 0x2dc) = 0x40000000;
    *(undefined4 *)(iVar11 + 0x4c4) = 7;
    *(undefined4 *)(iVar11 + 0x4c8) = 0x18;
    *(undefined4 *)(iVar11 + 0x4c0) = 0x203;
    *(undefined4 *)((int)param_1 + (iVar26 * 3 + 0x4d1) * 4) = 0;
    *(undefined4 *)((int)param_1 + 0x1348 + iVar26 * 0xc) = 0;
    return 0;
  case 0x191:
    uVar22 = FUN_0044fdb0(uVar8,*(int *)(iVar26 + 4),0);
    iVar27 = (int)uVar22 * 3 + 0x4d1;
    local_2b4 = *(float *)((int)param_1 + iVar27 * 4) + *(float *)((int)param_1 + 0x2c);
    local_2b0 = *(float *)((int)param_1 + 4 + iVar27 * 4) + *(float *)((int)param_1 + 0x30);
    iVar26 = (int)uVar22 * 0x210 + (int)param_1;
    local_2ac = *(float *)((int)param_1 + iVar27 * 4 + 8) + *(float *)((int)param_1 + 0x34);
    *(float *)(iVar26 + 0x2c8) = local_2b4;
    *(float *)(iVar26 + 0x2cc) = local_2b0;
    fVar9 = _DAT_00470b04;
    *(float *)(iVar26 + 0x2d0) = local_2ac;
    if ((*(float *)((int)param_1 + 0x1454) == fVar9) ||
       (fVar9 = *(float *)(iVar26 + 0x2cc) - *(float *)(DAT_00477834 + 0x3c4),
       fVar10 = *(float *)(iVar26 + 0x2c8) - *(float *)(DAT_00477834 + 0x3c0),
       fVar9 = fVar9 * fVar9 + fVar10 * fVar10,
       *(float *)((int)param_1 + 0x1454) < fVar9 != (*(float *)((int)param_1 + 0x1454) == fVar9))) {
      FUN_004073e0(DAT_004776f0,iVar26,DAT_004776f0);
      return 0;
    }
    break;
  case 0x192:
    uVar22 = FUN_0044fdb0(uVar8,*(int *)(iVar26 + 4),0);
    iVar26 = (int)uVar22 * 0x210 + (int)param_1;
    uVar22 = FUN_0044fdb0(*(int *)((int)param_1 + 0x14d8),
                          *(int *)(*(int *)((int)param_1 + 0x14d8) + 4),1);
    *(short *)(iVar26 + 0x2c4) = (short)uVar22;
    uVar22 = FUN_0044fdb0(extraout_ECX_29,*(int *)(*(int *)((int)param_1 + 0x14d8) + 4),2);
    *(short *)(iVar26 + 0x2c6) = (short)uVar22;
    return 0;
  case 0x193:
    uVar22 = FUN_0044fdb0(uVar8,*(int *)(iVar26 + 4),0);
    fVar19 = FUN_0044fe40(1.4013e-45);
    *(float *)((int)param_1 + ((int)uVar22 * 3 + 0x4d1) * 4) = (float)fVar19;
    fVar19 = FUN_0044fe40(2.8026e-45);
    *(float *)((int)param_1 + 0x1348 + (int)uVar22 * 0xc) = (float)fVar19;
    return 0;
  case 0x194:
    uVar22 = FUN_0044fdb0(uVar8,*(int *)(iVar26 + 4),0);
    iVar26 = (int)uVar22 * 0x210 + (int)param_1;
    fVar19 = FUN_0044fe40(1.4013e-45);
    *(float *)(iVar26 + 0x2d4) = (float)fVar19;
    fVar19 = FUN_0044fe40(2.8026e-45);
    *(float *)(iVar26 + 0x2d8) = (float)fVar19;
    return 0;
  case 0x195:
    uVar22 = FUN_0044fdb0(uVar8,*(int *)(iVar26 + 4),0);
    iVar26 = (int)uVar22 * 0x210 + (int)param_1;
    goto LAB_00410408;
  case 0x196:
    uVar22 = FUN_0044fdb0(uVar8,*(int *)(iVar26 + 4),0);
    iVar26 = (int)uVar22 * 0x210 + (int)param_1;
    uVar22 = FUN_0044fdb0(*(int *)((int)param_1 + 0x14d8),
                          *(int *)(*(int *)((int)param_1 + 0x14d8) + 4),1);
    *(short *)(iVar26 + 0x4b8) = (short)uVar22;
    uVar22 = FUN_0044fdb0(extraout_ECX_30,*(int *)(*(int *)((int)param_1 + 0x14d8) + 4),2);
    *(short *)(iVar26 + 0x4ba) = (short)uVar22;
    return 0;
  case 0x197:
    uVar22 = FUN_0044fdb0(uVar8,*(int *)(iVar26 + 4),0);
    uVar23 = FUN_0044fdb0(extraout_ECX_42,*(int *)(*(int *)((int)param_1 + 0x14d8) + 4),1);
    *(short *)((int)uVar22 * 0x210 + 0x4bc + (int)param_1) = (short)uVar23;
    return 0;
  case 0x198:
    uVar22 = FUN_0044fdb0(uVar8,*(int *)(iVar26 + 4),0);
    iVar26 = (int)uVar22 * 0x210 + (int)param_1;
    uVar22 = FUN_0044fdb0(*(int *)((int)param_1 + 0x14d8),
                          *(int *)(*(int *)((int)param_1 + 0x14d8) + 4),1);
    *(int *)(iVar26 + 0x4c4) = (int)uVar22;
    uVar22 = FUN_0044fdb0(extraout_ECX_43,*(int *)(*(int *)((int)param_1 + 0x14d8) + 4),2);
    *(int *)(iVar26 + 0x4c8) = (int)uVar22;
    return 0;
  case 0x199:
    uVar22 = FUN_0044fdb0(uVar8,*(int *)(iVar26 + 4),0);
    uVar23 = FUN_0044fdb0(extraout_ECX_44,*(int *)(*(int *)((int)param_1 + 0x14d8) + 4),1);
    iVar26 = (int)uVar22 * 0x16 + (int)uVar23;
    iVar27 = (int)param_1 + iVar26 * 0x18;
    uVar22 = FUN_0044fdb0(*(int *)((int)param_1 + 0x14d8),
                          *(int *)(*(int *)((int)param_1 + 0x14d8) + 4),2);
    *(int *)(iVar27 + 0x2f8) = (int)uVar22;
    uVar22 = FUN_0044fdb0(extraout_ECX_45,*(int *)(*(int *)((int)param_1 + 0x14d8) + 4),3);
    *(int *)(iVar27 + 0x2f4) = (int)uVar22;
    uVar22 = FUN_0044fdb0(extraout_ECX_46,*(int *)(*(int *)((int)param_1 + 0x14d8) + 4),4);
    *(int *)(iVar27 + 0x2ec) = (int)uVar22;
    uVar22 = FUN_0044fdb0(extraout_ECX_47,*(int *)(*(int *)((int)param_1 + 0x14d8) + 4),5);
    *(int *)(iVar27 + 0x2f0) = (int)uVar22;
    fVar19 = FUN_0044fe40(8.40779e-45);
    *(float *)(iVar27 + 0x2e4) = (float)fVar19;
    fVar19 = FUN_0044fe40(9.80909e-45);
    *(float *)((int)param_1 + (iVar26 * 3 + 0x5d) * 8) = (float)fVar19;
    return 0;
  case 0x19a:
    FUN_00408210(1);
    FUN_0041c850();
    return 0;
  case 0x19b:
    uVar22 = FUN_0044fdb0(uVar8,*(int *)(iVar26 + 4),1);
    uVar23 = FUN_0044fdb0(extraout_ECX_28,*(int *)(*(int *)((int)param_1 + 0x14d8) + 4),0);
    puVar5 = (undefined4 *)((int)uVar22 * 0x210 + 0x2c4 + (int)param_1);
    puVar14 = (undefined4 *)((int)uVar23 * 0x210 + 0x2c4 + (int)param_1);
    for (iVar26 = 0x84; iVar26 != 0; iVar26 = iVar26 + -1) {
      *puVar14 = *puVar5;
      puVar5 = puVar5 + 1;
      puVar14 = puVar14 + 1;
    }
    return 0;
  case 0x19c:
  case 0x1af:
    pfVar15 = local_288;
    for (iVar27 = 0x77; iVar27 != 0; iVar27 = iVar27 + -1) {
      *pfVar15 = 0.0;
      pfVar15 = pfVar15 + 1;
    }
    if (sVar1 == 0x1af) {
      puVar5 = (undefined4 *)((int)param_1 + 0x2e4);
      puVar14 = local_25c;
      for (iVar27 = 0x6c; iVar27 != 0; iVar27 = iVar27 + -1) {
        *puVar14 = *puVar5;
        puVar5 = puVar5 + 1;
        puVar14 = puVar14 + 1;
      }
    }
    local_2b4 = *(float *)((int)param_1 + 0x1344) + *(float *)((int)param_1 + 0x2c);
    local_2b0 = *(float *)((int)param_1 + 0x1348) + *(float *)((int)param_1 + 0x30);
    local_2ac = *(float *)((int)param_1 + 0x134c) + *(float *)((int)param_1 + 0x34);
    local_288[0] = local_2b4;
    local_288[1] = local_2b0;
    local_288[2] = local_2ac;
    uVar22 = FUN_0044fdb0(local_2ac,*(int *)(iVar26 + 4),0);
    local_264 = (float)CONCAT22(local_264._2_2_,(short)uVar22);
    uVar22 = FUN_0044fdb0(extraout_ECX_54,*(int *)(*(int *)((int)param_1 + 0x14d8) + 4),1);
    local_264 = (float)CONCAT22((short)uVar22,(undefined2)local_264);
    fVar19 = FUN_0044fe40(2.8026e-45);
    local_288[3] = (float)fVar19;
    fVar19 = FUN_0044fe40(4.2039e-45);
    local_268 = (float)fVar19;
    fVar19 = FUN_0044fe40(5.60519e-45);
    local_274 = (float)fVar19;
    fVar19 = FUN_0044fe40(7.00649e-45);
    local_278 = (float)fVar19;
    fVar19 = FUN_0044fe40(8.40779e-45);
    local_270 = (float)fVar19;
    fVar19 = FUN_0044fe40(9.80909e-45);
    local_26c = (float)fVar19;
    local_260 = (float)((uint)local_260 | 1);
    FUN_0041c510(0);
    return 0;
  case 0x19d:
  case 0x1b0:
    pfVar15 = local_288;
    for (iVar26 = 0x7e; iVar26 != 0; iVar26 = iVar26 + -1) {
      *pfVar15 = 0.0;
      pfVar15 = pfVar15 + 1;
    }
    local_25c[0] = 0x41000000;
    puVar5 = (undefined4 *)FUN_00412a10(0);
    if (*(short *)(iVar27 + 4) == 0x1b0) {
      puVar14 = (undefined4 *)((int)param_1 + 0x2e4);
      puVar13 = local_240;
      for (iVar26 = 0x6c; iVar26 != 0; iVar26 = iVar26 + -1) {
        *puVar13 = *puVar14;
        puVar14 = puVar14 + 1;
        puVar13 = puVar13 + 1;
      }
    }
    local_2b4 = *(float *)((int)param_1 + 0x1344) + *(float *)((int)param_1 + 0x2c);
    local_2b0 = *(float *)((int)param_1 + 0x1348) + *(float *)((int)param_1 + 0x30);
    local_2ac = *(float *)((int)param_1 + 0x134c) + *(float *)((int)param_1 + 0x34);
    local_288[0] = local_2b4;
    local_288[1] = local_2b0;
    local_288[2] = local_2ac;
    uVar22 = FUN_0044fdb0(local_2ac,*(int *)(*(int *)((int)param_1 + 0x14d8) + 4),1);
    local_248 = (undefined2)uVar22;
    uVar22 = FUN_0044fdb0(extraout_ECX_55,*(int *)(*(int *)((int)param_1 + 0x14d8) + 4),2);
    local_246 = (undefined2)uVar22;
    fVar19 = FUN_0044fe40(4.2039e-45);
    local_270 = (float)fVar19;
    fVar19 = FUN_0044fe40(5.60519e-45);
    local_264 = (float)fVar19;
    fVar19 = FUN_0044fe40(7.00649e-45);
    local_268 = (float)fVar19;
    uVar22 = FUN_0044fdb0(extraout_ECX_56,*(int *)(*(int *)((int)param_1 + 0x14d8) + 4),6);
    local_25c[1] = (undefined4)uVar22;
    uVar22 = FUN_0044fdb0(extraout_ECX_57,*(int *)(*(int *)((int)param_1 + 0x14d8) + 4),7);
    local_25c[2] = (undefined4)uVar22;
    uVar22 = FUN_0044fdb0(extraout_ECX_58,*(int *)(*(int *)((int)param_1 + 0x14d8) + 4),8);
    local_25c[3] = (undefined4)uVar22;
    uVar22 = FUN_0044fdb0(extraout_ECX_59,*(int *)(*(int *)((int)param_1 + 0x14d8) + 4),9);
    local_24c = (undefined4)uVar22;
    fVar19 = FUN_0044fe40(1.4013e-44);
    local_260 = (float)fVar19;
    uVar22 = FUN_0044fdb0(extraout_ECX_60,*(int *)(*(int *)((int)param_1 + 0x14d8) + 4),0xb);
    local_244 = (uint)uVar22 | 2;
    uVar6 = FUN_0041c510(1);
    if (puVar5 != (undefined4 *)0x0) {
      *puVar5 = uVar6;
      return 0;
    }
    break;
  case 0x19e:
    uVar22 = FUN_00412a00(0);
    iVar26 = FUN_0040cf90((int)uVar22);
    if (iVar26 != 0) {
      fVar19 = FUN_0044fe40(2.8026e-45);
      fVar21 = FUN_0044fe40(1.4013e-45);
      *(float *)(iVar26 + 0x24) = (float)fVar21;
      *(float *)(iVar26 + 0x28) = (float)fVar19;
      *(undefined4 *)(iVar26 + 0x2c) = 0;
      return 0;
    }
    break;
  case 0x19f:
    uVar22 = FUN_00412a00(0);
    iVar26 = FUN_0040cf90((int)uVar22);
    if (iVar26 != 0) {
      fVar19 = FUN_0044fe40(2.8026e-45);
      fVar21 = FUN_0044fe40(1.4013e-45);
      local_2b4 = (float)fVar21;
      local_2ac = 0.0;
      local_2b0 = (float)fVar19;
      FUN_0040cf60(iVar26);
      return 0;
    }
    break;
  case 0x1a0:
    uVar22 = FUN_00412a00(0);
    iVar26 = FUN_0040cf90((int)uVar22);
    if (iVar26 != 0) {
      fVar19 = FUN_0044fe40(1.4013e-45);
      *(float *)(iVar26 + 0x48) = (float)fVar19;
      return 0;
    }
    break;
  case 0x1a1:
    uVar22 = FUN_00412a00(0);
    iVar26 = FUN_0040cf90((int)uVar22);
    if (iVar26 != 0) {
      fVar19 = FUN_0044fe40(1.4013e-45);
      *(float *)(iVar26 + 0x44) = (float)fVar19;
      return 0;
    }
    break;
  case 0x1a2:
    uVar22 = FUN_00412a00(0);
    iVar26 = FUN_0040cf90((int)uVar22);
    if (iVar26 != 0) {
      fVar19 = FUN_0044fe40(1.4013e-45);
      *(float *)(iVar26 + 0x3c) = (float)fVar19;
      return 0;
    }
    break;
  case 0x1a3:
    uVar22 = FUN_00412a00(0);
    iVar26 = FUN_0040cf90((int)uVar22);
    if (iVar26 != 0) {
      fVar19 = FUN_0044fe40(1.4013e-45);
      *(float *)(iVar26 + 0x440) = (float)fVar19;
      return 0;
    }
    break;
  case 0x1a4:
    fVar19 = FUN_0044fe40(0.0);
    FUN_00408100((float)fVar19,1,0);
    FUN_0041c800();
    return 0;
  case 0x1a5:
    fVar19 = FUN_0044fe40(0.0);
    FUN_00408100((float)fVar19,0,0);
    FUN_0041c800();
    return 0;
  case 0x1a6:
    uVar22 = FUN_0044fdb0(uVar8,*(int *)(iVar26 + 4),0);
    iVar26 = (int)uVar22;
    if (0x1ff < DAT_00474c98) {
LAB_004106da:
      iVar26 = iVar26 * 0x210 + (int)param_1;
      fVar19 = FUN_0044fe40(7.00649e-45);
      *(float *)(iVar26 + 0x2dc) = (float)fVar19;
      fVar19 = FUN_0044fe40(8.40779e-45);
      *(float *)(iVar26 + 0x2e0) = (float)fVar19;
      return 0;
    }
    bVar18 = SBORROW4(DAT_00474c98,-0x200);
    iVar27 = DAT_00474c98 + 0x200;
    goto LAB_00410738;
  case 0x1a7:
    uVar22 = FUN_0044fdb0(uVar8,*(int *)(iVar26 + 4),0);
    iVar26 = (int)uVar22;
    if (599 < DAT_00474c98) {
      iVar26 = iVar26 * 0x210 + (int)param_1;
      fVar19 = FUN_0044fe40(1.26117e-44);
      *(float *)(iVar26 + 0x2dc) = (float)fVar19;
      fVar19 = FUN_0044fe40(1.4013e-44);
      *(float *)(iVar26 + 0x2e0) = (float)fVar19;
      return 0;
    }
    if (199 < DAT_00474c98) {
      iVar26 = iVar26 * 0x210 + (int)param_1;
      fVar19 = FUN_0044fe40(9.80909e-45);
      *(float *)(iVar26 + 0x2dc) = (float)fVar19;
      fVar19 = FUN_0044fe40(1.12104e-44);
      *(float *)(iVar26 + 0x2e0) = (float)fVar19;
      return 0;
    }
    if (-0xc9 < DAT_00474c98) goto LAB_004106da;
    bVar18 = SBORROW4(DAT_00474c98,-600);
    iVar27 = DAT_00474c98 + 600;
LAB_00410738:
    iVar26 = iVar26 * 0x210 + (int)param_1;
    if (bVar18 == iVar27 < 0) {
      fVar19 = FUN_0044fe40(4.2039e-45);
      *(float *)(iVar26 + 0x2dc) = (float)fVar19;
      fVar19 = FUN_0044fe40(5.60519e-45);
      *(float *)(iVar26 + 0x2e0) = (float)fVar19;
      return 0;
    }
LAB_00410408:
    fVar19 = FUN_0044fe40(1.4013e-45);
    *(float *)(iVar26 + 0x2dc) = (float)fVar19;
    fVar19 = FUN_0044fe40(2.8026e-45);
    *(float *)(iVar26 + 0x2e0) = (float)fVar19;
    return 0;
  case 0x1a8:
    uVar22 = FUN_0044fdb0(uVar8,*(int *)(iVar26 + 4),0);
    fVar19 = FUN_0044fe40(1.4013e-45);
    fVar21 = FUN_0044fe40(2.8026e-45);
    local_2a8 = (float)fVar21;
    fVar21 = FUN_0044fe40(4.2039e-45);
    fVar20 = FUN_0044fe40(5.60519e-45);
    iVar26 = (int)uVar22 * 0x210 + (int)param_1;
    *(float *)(iVar26 + 0x2dc) =
         ((float)fVar21 - (float)fVar19) * ((float)DAT_00474c98 + _DAT_00470d4c) * _DAT_00470d48 +
         (float)fVar19;
    *(float *)(iVar26 + 0x2e0) =
         (float)((fVar20 - (float10)local_2a8) * ((float10)DAT_00474c98 + (float10)_DAT_00470d4c) *
                 (float10)_DAT_00470d48 + (float10)local_2a8);
    return 0;
  case 0x1a9:
    uVar22 = FUN_0044fdb0(uVar8,*(int *)(iVar26 + 4),0);
    iVar26 = (int)uVar22;
    if (0x1ff < DAT_00474c98) {
LAB_00410949:
      iVar26 = iVar26 * 0x210 + (int)param_1;
      uVar22 = FUN_0044fdb0(*(int *)((int)param_1 + 0x14d8),
                            *(int *)(*(int *)((int)param_1 + 0x14d8) + 4),5);
      *(short *)(iVar26 + 0x4b8) = (short)uVar22;
      uVar22 = FUN_0044fdb0(extraout_ECX_35,*(int *)(*(int *)((int)param_1 + 0x14d8) + 4),6);
      *(short *)(iVar26 + 0x4ba) = (short)uVar22;
      return 0;
    }
    bVar18 = SBORROW4(DAT_00474c98,-0x200);
    iVar27 = DAT_00474c98 + 0x200;
    goto LAB_004109a3;
  case 0x1aa:
    uVar22 = FUN_0044fdb0(uVar8,*(int *)(iVar26 + 4),0);
    iVar26 = (int)uVar22;
    if (599 < DAT_00474c98) {
      iVar26 = iVar26 * 0x210 + (int)param_1;
      uVar22 = FUN_0044fdb0(*(int *)((int)param_1 + 0x14d8),
                            *(int *)(*(int *)((int)param_1 + 0x14d8) + 4),9);
      *(short *)(iVar26 + 0x4b8) = (short)uVar22;
      uVar22 = FUN_0044fdb0(extraout_ECX_33,*(int *)(*(int *)((int)param_1 + 0x14d8) + 4),10);
      *(short *)(iVar26 + 0x4ba) = (short)uVar22;
      return 0;
    }
    if (199 < DAT_00474c98) {
      iVar26 = iVar26 * 0x210 + (int)param_1;
      uVar22 = FUN_0044fdb0(*(int *)((int)param_1 + 0x14d8),
                            *(int *)(*(int *)((int)param_1 + 0x14d8) + 4),7);
      *(short *)(iVar26 + 0x4b8) = (short)uVar22;
      uVar22 = FUN_0044fdb0(extraout_ECX_34,*(int *)(*(int *)((int)param_1 + 0x14d8) + 4),8);
      *(short *)(iVar26 + 0x4ba) = (short)uVar22;
      return 0;
    }
    if (-0xc9 < DAT_00474c98) goto LAB_00410949;
    bVar18 = SBORROW4(DAT_00474c98,-600);
    iVar27 = DAT_00474c98 + 600;
LAB_004109a3:
    iVar11 = *(int *)((int)param_1 + 0x14d8);
    iVar26 = iVar26 * 0x210 + (int)param_1;
    if (bVar18 == iVar27 < 0) {
      uVar22 = FUN_0044fdb0(iVar11,*(int *)(iVar11 + 4),3);
      *(short *)(iVar26 + 0x4b8) = (short)uVar22;
      uVar22 = FUN_0044fdb0(extraout_ECX_36,*(int *)(*(int *)((int)param_1 + 0x14d8) + 4),4);
      *(short *)(iVar26 + 0x4ba) = (short)uVar22;
      return 0;
    }
    uVar22 = FUN_0044fdb0(iVar11,*(int *)(iVar11 + 4),1);
    *(short *)(iVar26 + 0x4b8) = (short)uVar22;
    uVar22 = FUN_0044fdb0(extraout_ECX_37,*(int *)(*(int *)((int)param_1 + 0x14d8) + 4),2);
    *(short *)(iVar26 + 0x4ba) = (short)uVar22;
    return 0;
  case 0x1ab:
    uVar22 = FUN_0044fdb0(uVar8,*(int *)(iVar26 + 4),0);
    uVar23 = FUN_0044fdb0(extraout_ECX_38,*(int *)(*(int *)((int)param_1 + 0x14d8) + 4),1);
    uVar24 = FUN_0044fdb0(extraout_ECX_39,*(int *)(*(int *)((int)param_1 + 0x14d8) + 4),2);
    local_2a8 = (float)uVar24;
    uVar24 = FUN_0044fdb0(extraout_ECX_40,*(int *)(*(int *)((int)param_1 + 0x14d8) + 4),3);
    uVar25 = FUN_0044fdb0(extraout_ECX_41,*(int *)(*(int *)((int)param_1 + 0x14d8) + 4),4);
    iVar27 = (int)uVar22 * 0x210;
    iVar26 = ((int)uVar24 - (int)uVar23) * (DAT_00474c98 + 0x400);
    *(short *)(iVar27 + 0x4b8 + (int)param_1) =
         (short)((int)(iVar26 + (iVar26 >> 0x1f & 0x7ffU)) >> 0xb) + (short)uVar23;
    iVar26 = ((int)uVar25 - (int)local_2a8) * (DAT_00474c98 + 0x400);
    *(short *)(iVar27 + (int)param_1 + 0x4ba) =
         (short)((int)(iVar26 + (iVar26 >> 0x1f & 0x7ffU)) >> 0xb) + SUB42(local_2a8,0);
    return 0;
  case 0x1ac:
  case 0x1b1:
    pfVar15 = local_288;
    for (iVar26 = 0x77; iVar26 != 0; iVar26 = iVar26 + -1) {
      *pfVar15 = 0.0;
      pfVar15 = pfVar15 + 1;
    }
    if (sVar1 == 0x1b1) {
      puVar5 = (undefined4 *)((int)param_1 + 0x2e4);
      puVar14 = local_25c;
      for (iVar26 = 0x6c; iVar26 != 0; iVar26 = iVar26 + -1) {
        *puVar14 = *puVar5;
        puVar5 = puVar5 + 1;
        puVar14 = puVar14 + 1;
      }
    }
    local_2b4 = *(float *)((int)param_1 + 0x1344) + *(float *)((int)param_1 + 0x2c);
    local_2b0 = *(float *)((int)param_1 + 0x1348) + *(float *)((int)param_1 + 0x30);
    local_2ac = *(float *)((int)param_1 + 0x134c) + *(float *)((int)param_1 + 0x34);
    local_288[0] = local_2b4;
    local_288[1] = local_2b0;
    local_288[2] = local_2ac;
    uVar22 = FUN_00412a00(0);
    local_264 = (float)CONCAT22(local_264._2_2_,(short)uVar22);
    uVar22 = FUN_00412a00(1);
    local_264 = (float)CONCAT22((short)uVar22,(undefined2)local_264);
    fVar19 = FUN_0044fe40(2.8026e-45);
    local_288[3] = (float)fVar19;
    fVar19 = FUN_0044fe40(4.2039e-45);
    local_268 = (float)fVar19;
    fVar19 = FUN_0044fe40(5.60519e-45);
    local_274 = (float)fVar19;
    fVar19 = FUN_0044fe40(7.00649e-45);
    local_278 = (float)fVar19;
    fVar19 = FUN_0044fe40(8.40779e-45);
    local_270 = (float)fVar19;
    fVar19 = FUN_0044fe40(9.80909e-45);
    local_26c = (float)fVar19;
    local_260 = (float)((uint)local_260 & 0xfffffffe);
    FUN_0041c510(0);
    return 0;
  case 0x1ad:
  case 0x1b2:
    FUN_0040cf40(uVar8,local_288);
    puVar5 = (undefined4 *)FUN_00412a10(0);
    if (*(short *)(iVar27 + 4) == 0x1b2) {
      puVar14 = (undefined4 *)((int)param_1 + 0x2e4);
      puVar13 = local_240;
      for (iVar26 = 0x6c; iVar26 != 0; iVar26 = iVar26 + -1) {
        *puVar13 = *puVar14;
        puVar14 = puVar14 + 1;
        puVar13 = puVar13 + 1;
      }
    }
    local_2b4 = *(float *)((int)param_1 + 0x1344) + *(float *)((int)param_1 + 0x2c);
    local_2b0 = *(float *)((int)param_1 + 0x1348) + *(float *)((int)param_1 + 0x30);
    local_2ac = *(float *)((int)param_1 + 0x134c) + *(float *)((int)param_1 + 0x34);
    local_288[0] = local_2b4;
    local_288[1] = local_2b0;
    local_288[2] = local_2ac;
    uVar22 = FUN_00412a00(1);
    local_248 = (undefined2)uVar22;
    uVar22 = FUN_00412a00(2);
    local_246 = (undefined2)uVar22;
    fVar19 = FUN_0044fe40(4.2039e-45);
    local_270 = (float)fVar19;
    fVar19 = FUN_0044fe40(5.60519e-45);
    local_264 = (float)fVar19;
    fVar19 = FUN_0044fe40(7.00649e-45);
    local_268 = (float)fVar19;
    uVar22 = FUN_00412a00(6);
    local_25c[1] = (undefined4)uVar22;
    uVar22 = FUN_00412a00(7);
    local_25c[2] = (undefined4)uVar22;
    uVar22 = FUN_00412a00(8);
    local_25c[3] = (undefined4)uVar22;
    uVar22 = FUN_00412a00(9);
    local_24c = (undefined4)uVar22;
    fVar19 = FUN_0044fe40(1.4013e-44);
    local_260 = (float)fVar19;
    uVar22 = FUN_00412a00(0xb);
    local_244 = (uint)uVar22 & 0xfffffffd;
    uVar6 = FUN_0041c510(1);
    if (puVar5 != (undefined4 *)0x0) {
      *puVar5 = uVar6;
      return 0;
    }
    break;
  case 0x1ae:
    pfVar15 = (float *)(DAT_00477834 + 0x3c0);
    fVar19 = FUN_0044fe40(1.4013e-45);
    iVar26 = DAT_00477834;
    fVar21 = FUN_0044fe40(2.8026e-45);
    fVar19 = (float10)fpatan((float10)*(float *)(iVar26 + 0x3c4) - fVar21,
                             (float10)*pfVar15 - (float10)(float)fVar19);
    goto LAB_00411956;
  case 0x1b3:
    uVar22 = FUN_0044fdb0(uVar8,*(int *)(iVar26 + 4),0);
    if (DAT_00474c74 == 0) {
      fVar9 = 1.4013e-45;
    }
    else if (DAT_00474c74 == 1) {
      fVar9 = 2.8026e-45;
    }
    else {
      fVar9 = 4.2039e-45;
      if (DAT_00474c74 != 2) {
        fVar9 = 5.60519e-45;
      }
    }
    fVar19 = FUN_0044fe40(fVar9);
    iVar26 = (int)uVar22 * 0x210;
    *(float *)(iVar26 + 0x2dc + (int)param_1) = (float)fVar19;
    if (DAT_00474c74 == 0) {
      fVar9 = 7.00649e-45;
    }
    else if (DAT_00474c74 == 1) {
      fVar9 = 8.40779e-45;
    }
    else {
      fVar9 = 9.80909e-45;
      if (DAT_00474c74 != 2) {
        fVar9 = 1.12104e-44;
      }
    }
    fVar19 = FUN_0044fe40(fVar9);
    *(float *)(iVar26 + (int)param_1 + 0x2e0) = (float)fVar19;
    return 0;
  case 0x1b4:
    uVar22 = FUN_0044fdb0(uVar8,*(int *)(iVar26 + 4),0);
    if (DAT_00474c74 == 0) {
      iVar26 = 1;
    }
    else if (DAT_00474c74 == 1) {
      iVar26 = 2;
    }
    else if (DAT_00474c74 == 2) {
      iVar26 = 3;
    }
    else {
      iVar26 = 4;
    }
    uVar23 = FUN_0044fdb0(extraout_ECX_31,*(int *)(*(int *)((int)param_1 + 0x14d8) + 4),iVar26);
    iVar26 = (int)uVar22 * 0x210 + (int)param_1;
    *(short *)(iVar26 + 0x4b8) = (short)uVar23;
    if (DAT_00474c74 == 0) {
      iVar27 = 5;
    }
    else if (DAT_00474c74 == 1) {
      iVar27 = 6;
    }
    else if (DAT_00474c74 == 2) {
      iVar27 = 7;
    }
    else {
      iVar27 = 8;
    }
    uVar22 = FUN_0044fdb0(extraout_ECX_32,*(int *)(*(int *)((int)param_1 + 0x14d8) + 4),iVar27);
    *(short *)(iVar26 + 0x4ba) = (short)uVar22;
    return 0;
  }
switchD_0040e7c9_caseD_112:
  return 0;
switchD_0040e7c9_caseD_105:
  iVar26 = *(int *)(iVar27 + 0x10) + 4;
  pfVar15 = local_90;
  for (iVar11 = 0x10; iVar11 != 0; iVar11 = iVar11 + -1) {
    *pfVar15 = 0.0;
    pfVar15 = pfVar15 + 1;
  }
  iVar26 = (int)(iVar26 + (iVar26 >> 0x1f & 3U)) >> 2;
  fVar19 = (float10)FUN_00412aa0(1,*(float *)(iVar27 + 0x10 + iVar26 * 4));
  local_90[0] = (float)fVar19;
  fVar19 = (float10)FUN_00412aa0(2,*(float *)(iVar27 + 0x14 + iVar26 * 4));
  local_90[1] = (float)fVar19;
  uVar22 = FUN_0044ff00(*(int *)((int)param_1 + 0x14d8),
                        *(int *)(*(int *)((int)param_1 + 0x14d8) + 4),3,
                        *(int *)(iVar27 + 0x18 + iVar26 * 4));
  local_7c = (undefined4)uVar22;
  uVar22 = FUN_0044ff00(*(int *)((int)param_1 + 0x14d8),
                        *(int *)(*(int *)((int)param_1 + 0x14d8) + 4),4,
                        *(int *)(iVar27 + 0x1c + iVar26 * 4));
  local_90[3] = (float)uVar22;
  uVar22 = FUN_0044ff00(extraout_ECX_02,*(int *)(*(int *)((int)param_1 + 0x14d8) + 4),5,
                        *(int *)(iVar27 + 0x20 + iVar26 * 4));
  local_80 = (undefined4)uVar22;
  puVar5 = (undefined4 *)((int)param_1 + 0xfc);
  pbVar16 = local_70;
  for (iVar26 = 8; iVar26 != 0; iVar26 = iVar26 + -1) {
    *(undefined4 *)pbVar16 = *puVar5;
    puVar5 = puVar5 + 1;
    pbVar16 = pbVar16 + 4;
  }
  local_78 = 1;
  goto LAB_0040ecfb;
switchD_0040e7c9_caseD_101:
  iVar26 = *(int *)(iVar27 + 0x10) + 4;
  pfVar15 = local_90;
  for (iVar11 = 0x10; iVar11 != 0; iVar11 = iVar11 + -1) {
    *pfVar15 = 0.0;
    pfVar15 = pfVar15 + 1;
  }
  iVar26 = (int)(iVar26 + (iVar26 >> 0x1f & 3U)) >> 2;
  fVar19 = (float10)FUN_00412aa0(1,*(float *)(iVar27 + 0x10 + iVar26 * 4));
  local_90[0] = (float)fVar19;
  fVar19 = (float10)FUN_00412aa0(2,*(float *)(iVar27 + 0x14 + iVar26 * 4));
  goto LAB_0040e900;
switchD_0040e7c9_caseD_126:
  iVar26 = *(int *)(DAT_00477704 + 0x10);
  *(undefined4 *)((int)param_1 + 0x58) = *(undefined4 *)(iVar26 + 0x1068);
  *(undefined4 *)((int)param_1 + 0x5c) = *(undefined4 *)(iVar26 + 0x106c);
  *(undefined4 *)((int)param_1 + 0x60) = *(undefined4 *)(iVar26 + 0x1070);
  return 0;
}

