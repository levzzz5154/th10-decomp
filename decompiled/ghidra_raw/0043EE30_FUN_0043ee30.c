/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0043EE30
 * Tracking name: FUN_0043ee30
 * Ghidra name: FUN_0043ee30
 * Tracked span: 10192 bytes
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

ulonglong __fastcall FUN_0043ee30(undefined4 param_1,uint param_2,int param_3)

{
  float fVar1;
  float fVar2;
  short sVar3;
  undefined2 *puVar4;
  bool bVar5;
  undefined1 uVar6;
  byte bVar7;
  short sVar8;
  float fVar9;
  undefined4 uVar10;
  void *pvVar11;
  undefined4 *puVar12;
  int iVar13;
  uint *puVar14;
  float *pfVar15;
  int *piVar16;
  int *piVar17;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  undefined4 extraout_ECX_02;
  int *extraout_ECX_03;
  int *extraout_ECX_04;
  int *extraout_ECX_05;
  int *extraout_ECX_06;
  int *extraout_ECX_07;
  int *extraout_ECX_08;
  int *extraout_ECX_09;
  int *extraout_ECX_10;
  int *extraout_ECX_11;
  int *extraout_ECX_12;
  int *extraout_ECX_13;
  int *extraout_ECX_14;
  int *extraout_ECX_15;
  int *extraout_ECX_16;
  int *extraout_ECX_17;
  int *extraout_ECX_18;
  int *extraout_ECX_19;
  int *extraout_ECX_20;
  int *extraout_ECX_21;
  int *extraout_ECX_22;
  int *extraout_ECX_23;
  int *extraout_ECX_24;
  int *extraout_ECX_25;
  int *extraout_ECX_26;
  int *extraout_ECX_27;
  int *extraout_ECX_28;
  int *extraout_ECX_29;
  int *extraout_ECX_30;
  int *extraout_ECX_31;
  int *extraout_ECX_32;
  int *extraout_ECX_33;
  int *extraout_ECX_34;
  int *extraout_ECX_35;
  int *extraout_ECX_36;
  int *extraout_ECX_37;
  int *extraout_ECX_38;
  int *extraout_ECX_39;
  int *extraout_ECX_40;
  int *extraout_ECX_41;
  int *extraout_ECX_42;
  int *extraout_ECX_43;
  int *extraout_ECX_44;
  int *extraout_ECX_45;
  undefined4 extraout_ECX_46;
  int *extraout_ECX_47;
  int *extraout_ECX_48;
  int *extraout_ECX_49;
  int *extraout_ECX_50;
  int *extraout_ECX_51;
  int *extraout_ECX_52;
  int *extraout_ECX_53;
  undefined4 extraout_ECX_54;
  int *extraout_ECX_55;
  int *extraout_ECX_56;
  ushort *puVar18;
  int *extraout_ECX_57;
  int *extraout_ECX_58;
  int *extraout_ECX_59;
  int *extraout_ECX_60;
  int *extraout_ECX_61;
  int *extraout_ECX_62;
  int *extraout_ECX_63;
  int *extraout_ECX_64;
  int *extraout_ECX_65;
  int *extraout_ECX_66;
  int *extraout_ECX_67;
  int *extraout_ECX_68;
  int *extraout_ECX_69;
  int *extraout_ECX_70;
  int *extraout_ECX_71;
  int *extraout_ECX_72;
  int *extraout_ECX_73;
  int *extraout_ECX_74;
  int *extraout_ECX_75;
  int *extraout_ECX_76;
  int *extraout_ECX_77;
  int *extraout_ECX_78;
  int *extraout_ECX_79;
  int *extraout_ECX_80;
  int *extraout_ECX_81;
  int *extraout_ECX_82;
  int *extraout_ECX_83;
  int *extraout_ECX_84;
  int *extraout_ECX_85;
  int *extraout_ECX_86;
  int *extraout_ECX_87;
  int *extraout_ECX_88;
  int *extraout_ECX_89;
  int *extraout_ECX_90;
  int *extraout_ECX_91;
  undefined4 extraout_ECX_92;
  int *extraout_ECX_93;
  int *extraout_ECX_94;
  undefined4 extraout_ECX_95;
  int iVar19;
  short *psVar20;
  int extraout_EDX;
  int extraout_EDX_00;
  int extraout_EDX_01;
  int extraout_EDX_02;
  undefined4 extraout_EDX_03;
  undefined4 extraout_EDX_04;
  float extraout_EDX_05;
  float extraout_EDX_06;
  uint uVar21;
  float *pfVar22;
  short *psVar23;
  float *pfVar24;
  float10 fVar25;
  float10 extraout_ST1;
  ulonglong uVar26;
  ulonglong uVar27;
  undefined4 local_fc;
  float local_f8;
  float local_f4;
  float local_f0;
  float local_ec;
  undefined4 local_e8;
  float local_e4;
  int *local_e0;
  byte local_dc;
  undefined1 local_db;
  undefined1 local_da;
  float local_d8;
  byte local_d4;
  undefined1 local_d3;
  undefined1 local_d2;
  byte local_d0;
  undefined1 local_cf;
  undefined1 local_ce;
  float fStack_cc;
  float local_c8;
  float local_c4;
  float local_c0;
  float local_bc;
  float local_b8;
  int *piStack_b4;
  float local_b0;
  float fStack_ac;
  float local_a8;
  float fStack_a4;
  float local_a0;
  float fStack_9c;
  int *local_98;
  float fStack_94;
  int *local_90;
  float local_8c;
  int *local_88;
  float fStack_84;
  int *local_80;
  float fStack_7c;
  int *local_78;
  float fStack_74;
  float local_70;
  float local_6c;
  int *local_68;
  float fStack_64;
  float local_60;
  float fStack_5c;
  float local_58;
  float fStack_54;
  float fStack_50;
  float fStack_4c;
  int *local_48;
  float local_44;
  float fStack_40;
  float local_3c;
  int *local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_24;
  int *local_20;
  float local_1c;
  float local_14;
  int *local_10;
  float local_c;
  float local_8;
  float local_4;
  
  piVar17 = DAT_00476f78;
  if (*(int *)(param_3 + 0x390) == 0) {
    return CONCAT44(param_2,1);
  }
  if ((*(uint *)(param_3 + 0x35c) & 0x20000) != 0) {
    return (ulonglong)param_2 << 0x20;
  }
  local_68 = DAT_00476f78;
  if ((*(uint *)(param_3 + 0x35c) & 0x20000000) != 0) {
    DAT_00476f78 = (int *)0x3f800000;
  }
  sVar8 = *(short *)(param_3 + 0x304);
  if (sVar8 != 0) goto LAB_0043f62d;
LAB_0043eea4:
  puVar4 = *(undefined2 **)(param_3 + 0x390);
  iVar19 = (int)(short)puVar4[2];
  if (*(int *)(param_3 + 0x60) < iVar19) {
LAB_00440e42:
    if (*(float *)(param_3 + 0x30) != _DAT_00470b04) {
      fVar25 = (float10)FUN_0044bc10(*(float *)(param_3 + 0x24),
                                     (float)DAT_00476f78 * *(float *)(param_3 + 0x30));
      *(float *)(param_3 + 0x24) = (float)fVar25;
      *(uint *)(param_3 + 0x35c) = *(uint *)(param_3 + 0x35c) | 4;
      piVar17 = extraout_ECX_89;
      iVar19 = extraout_EDX_00;
    }
    if (*(float *)(param_3 + 0x34) != _DAT_00470b04) {
      fVar25 = (float10)FUN_0044bc10(*(float *)(param_3 + 0x28),
                                     (float)DAT_00476f78 * *(float *)(param_3 + 0x34));
      *(float *)(param_3 + 0x28) = (float)fVar25;
      *(uint *)(param_3 + 0x35c) = *(uint *)(param_3 + 0x35c) | 4;
      piVar17 = extraout_ECX_90;
      iVar19 = extraout_EDX_01;
    }
    if (*(float *)(param_3 + 0x38) != _DAT_00470b04) {
      fVar25 = (float10)FUN_0044bc10(*(float *)(param_3 + 0x2c),
                                     (float)DAT_00476f78 * *(float *)(param_3 + 0x38));
      *(float *)(param_3 + 0x2c) = (float)fVar25;
      *(uint *)(param_3 + 0x35c) = *(uint *)(param_3 + 0x35c) | 4;
      piVar17 = extraout_ECX_91;
      iVar19 = extraout_EDX_02;
    }
    if (*(float *)(param_3 + 0x48) != _DAT_00470b04) {
      fVar9 = (float)DAT_00476f78 * *(float *)(param_3 + 0x48);
      *(uint *)(param_3 + 0x35c) = *(uint *)(param_3 + 0x35c) | 8;
      *(float *)(param_3 + 0x40) = fVar9 + *(float *)(param_3 + 0x40);
    }
    if (*(float *)(param_3 + 0x44) != _DAT_00470b04) {
      fVar9 = (float)DAT_00476f78 * *(float *)(param_3 + 0x44);
      *(uint *)(param_3 + 0x35c) = *(uint *)(param_3 + 0x35c) | 0xc;
      *(float *)(param_3 + 0x3c) = fVar9 + *(float *)(param_3 + 0x3c);
    }
    fVar9 = (float)DAT_00476f78 * *(float *)(param_3 + 0x234) + *(float *)(param_3 + 0x54);
    bVar5 = fVar9 < _DAT_00470afc;
    *(float *)(param_3 + 0x54) = fVar9;
    if (bVar5) {
      if (fVar9 < _DAT_00470b04) {
        *(float *)(param_3 + 0x54) = fVar9 + _DAT_00470afc;
      }
    }
    else {
      *(float *)(param_3 + 0x54) = fVar9 - _DAT_00470afc;
    }
    fVar9 = (float)DAT_00476f78 * *(float *)(param_3 + 0x238) + *(float *)(param_3 + 0x58);
    bVar5 = fVar9 < _DAT_00470afc;
    *(float *)(param_3 + 0x58) = fVar9;
    if (bVar5) {
      if (fVar9 < _DAT_00470b04) {
        *(float *)(param_3 + 0x58) = fVar9 + _DAT_00470afc;
      }
    }
    else {
      *(float *)(param_3 + 0x58) = fVar9 - _DAT_00470afc;
    }
    if ((*(uint *)(param_3 + 0x35c) & 0x2000) != 0) {
      *(float *)(param_3 + 0x340) = _DAT_00491e6c + *(float *)(param_3 + 0x340);
      *(float *)(param_3 + 0x344) = _DAT_00491e70 + *(float *)(param_3 + 0x344);
      *(float *)(param_3 + 0x348) = _DAT_00491e74 + *(float *)(param_3 + 0x348);
    }
    if (*(int *)(param_3 + 0xb4) != 0) {
      if ((*(uint *)(param_3 + 0x35c) & 0x100) == 0) {
        piVar16 = (int *)FUN_00404610();
        piVar17 = (int *)(param_3 + 0x334);
      }
      else {
        piVar16 = (int *)FUN_00404610();
        piVar17 = (int *)(param_3 + 0x34c);
      }
      *piVar17 = *piVar16;
      iVar19 = piVar16[1];
      piVar17[1] = iVar19;
      piVar17[2] = piVar16[2];
    }
    if (*(int *)(param_3 + 0x100) != 0) {
      FUN_00441600((int *)&local_f4);
      iVar19 = CONCAT31((int3)((uint)extraout_EDX_03 >> 8),local_ec._0_1_);
      piVar17 = (int *)CONCAT31((int3)((uint)extraout_ECX_92 >> 8),local_f4._0_1_);
      *(undefined1 *)(param_3 + 0x2fe) = local_ec._0_1_;
      *(undefined1 *)(param_3 + 0x2fd) = local_f0._0_1_;
      *(undefined1 *)(param_3 + 0x2fc) = local_f4._0_1_;
    }
    if (*(int *)(param_3 + 300) != 0) {
      uVar27 = FUN_00441950(piVar17,iVar19);
      iVar19 = (int)(uVar27 >> 0x20);
      *(char *)(param_3 + 0x2ff) = (char)uVar27;
      piVar17 = extraout_ECX_93;
    }
    if (*(int *)(param_3 + 0x1b4) != 0) {
      piVar17 = (int *)FUN_00441ad0();
      iVar19 = *piVar17;
      *(int *)(param_3 + 0x3c) = iVar19;
      *(int *)(param_3 + 0x40) = piVar17[1];
      *(uint *)(param_3 + 0x35c) = *(uint *)(param_3 + 0x35c) | 8;
      piVar17 = extraout_ECX_94;
    }
    if (*(int *)(param_3 + 0x178) != 0) {
      piVar16 = (int *)FUN_00404610();
      piVar17 = (int *)(param_3 + 0x24);
      *piVar17 = *piVar16;
      iVar19 = piVar16[1];
      *(int *)(param_3 + 0x28) = iVar19;
      *(int *)(param_3 + 0x2c) = piVar16[2];
      *(uint *)(param_3 + 0x35c) = *(uint *)(param_3 + 0x35c) | 4;
    }
    if (*(int *)(param_3 + 0x200) != 0) {
      FUN_00441600((int *)&local_f4);
      iVar19 = CONCAT31((int3)((uint)extraout_EDX_04 >> 8),local_ec._0_1_);
      piVar17 = (int *)CONCAT31((int3)((uint)extraout_ECX_95 >> 8),local_f4._0_1_);
      *(undefined1 *)(param_3 + 0x302) = local_ec._0_1_;
      *(undefined1 *)(param_3 + 0x301) = local_f0._0_1_;
      *(undefined1 *)(param_3 + 0x300) = local_f4._0_1_;
    }
    if (*(int *)(param_3 + 0x22c) != 0) {
      uVar27 = FUN_00441950(piVar17,iVar19);
      *(char *)(param_3 + 0x303) = (char)uVar27;
    }
    if ((*(uint *)(param_3 + 0x35c) & 0x3c00000) == 0x2400000) {
      iVar19 = *(int *)(param_3 + 0x30c) + -1;
      local_e0 = *(int **)(param_3 + 0x2c);
      pfVar15 = *(float **)(param_3 + 0x358);
      fVar9 = _DAT_00470b14 / (float)iVar19;
      local_fc = 0.0;
      local_d8 = (float)*(int *)(param_3 + 0x310) / (float)iVar19;
      pfVar22 = pfVar15;
      local_e4 = fVar9;
      if (0 < iVar19) {
        do {
          pfVar22[3] = 1.0;
          pfVar22[4] = *(float *)(param_3 + 0x2fc);
          pfVar22[5] = *(float *)(*(int *)(param_3 + 0x394) + 0x20) + *(float *)(param_3 + 0x54);
          pfVar22[6] = local_fc + *(float *)(param_3 + 0x58);
          FUN_00441ef0(pfVar22,(float)local_e0,
                       *(float *)(param_3 + 0x3c) * _DAT_00470b0c + *(float *)(param_3 + 0x40));
          pfVar22[2] = 0.0;
          local_f0 = *(float *)(param_3 + 0x344) + *(float *)(param_3 + 0x338);
          fVar1 = *(float *)(param_3 + 0x348);
          fVar2 = *(float *)(param_3 + 0x33c);
          *pfVar22 = *(float *)(param_3 + 0x340) + *(float *)(param_3 + 0x334) + *pfVar22;
          pfVar22[1] = local_f0 + pfVar22[1];
          pfVar22[2] = fVar1 + fVar2;
          pfVar22[10] = 1.0;
          pfVar22[0xb] = *(float *)(param_3 + 0x2fc);
          pfVar22[0xc] = *(float *)(*(int *)(param_3 + 0x394) + 0x28) + *(float *)(param_3 + 0x54);
          pfVar22[0xd] = local_fc + *(float *)(param_3 + 0x58);
          FUN_00441ef0(pfVar22 + 7,extraout_EDX_05,
                       *(float *)(param_3 + 0x40) - *(float *)(param_3 + 0x3c) * _DAT_00470b0c);
          pfVar22[9] = 0.0;
          local_30 = *(float *)(param_3 + 0x344) + *(float *)(param_3 + 0x338);
          pfVar15 = pfVar22 + 0xe;
          fVar1 = *(float *)(param_3 + 0x33c);
          fVar2 = *(float *)(param_3 + 0x348);
          pfVar22[7] = *(float *)(param_3 + 0x340) + *(float *)(param_3 + 0x334) + pfVar22[7];
          pfVar22[8] = local_30 + pfVar22[8];
          pfVar22[9] = fVar1 + fVar2;
          local_fc = local_d8 + local_fc;
          fVar25 = (float10)FUN_0044bc10(extraout_EDX_06,fVar9);
          iVar19 = iVar19 + -1;
          local_e0 = (int *)(float)fVar25;
          pfVar22 = pfVar15;
        } while (iVar19 != 0);
      }
      pfVar22 = *(float **)(param_3 + 0x358);
      pfVar24 = pfVar15;
      for (iVar19 = 7; iVar19 != 0; iVar19 = iVar19 + -1) {
        *pfVar24 = *pfVar22;
        pfVar22 = pfVar22 + 1;
        pfVar24 = pfVar24 + 1;
      }
      pfVar15[6] = local_fc + *(float *)(param_3 + 0x58);
      pfVar22 = (float *)(*(int *)(param_3 + 0x358) + 0x1c);
      pfVar24 = pfVar15 + 7;
      for (iVar19 = 7; iVar19 != 0; iVar19 = iVar19 + -1) {
        *pfVar24 = *pfVar22;
        pfVar22 = pfVar22 + 1;
        pfVar24 = pfVar24 + 1;
      }
      pfVar15[0xd] = local_fc + *(float *)(param_3 + 0x58);
    }
    pfVar15 = *(float **)(param_3 + 0x68);
    *(int *)(param_3 + 0x5c) = *(int *)(param_3 + 0x60);
    if ((*pfVar15 <= _DAT_00470b68) || (_DAT_00470b64 <= *pfVar15)) {
      *(float *)(param_3 + 100) = *pfVar15 + *(float *)(param_3 + 100);
      uVar27 = FUN_00463b2c();
      *(int *)(param_3 + 0x60) = (int)uVar27;
    }
    else {
      uVar21 = *(int *)(param_3 + 0x60) + 1;
      uVar27 = (ulonglong)uVar21 << 0x20;
      fVar9 = *(float *)(param_3 + 100) + _DAT_00470afc;
      *(uint *)(param_3 + 0x60) = uVar21;
      *(float *)(param_3 + 100) = fVar9;
    }
    DAT_00476f78 = local_68;
    return uVar27 & 0xffffffff00000000;
  }
  switch(*puVar4) {
  default:
    goto switchD_0043eec4_caseD_0;
  case 3:
    *(uint *)(param_3 + 0x35c) = *(uint *)(param_3 + 0x35c) | 1;
    iVar19 = *(int *)(puVar4 + 4);
    if ((*(byte *)(puVar4 + 3) & 1) != 0) {
      uVar27 = FUN_0043ec70(param_3);
      iVar19 = (int)uVar27;
    }
    FUN_0043e5a0(*(int *)(param_3 + 0x308),iVar19);
    *(undefined4 *)(param_3 + 0x380) = *(undefined4 *)(param_3 + 0x60);
    *(uint *)(param_3 + 0x390) = (uint)(ushort)puVar4[1] + (int)puVar4;
    piVar17 = extraout_ECX_03;
    goto LAB_0043eea4;
  case 4:
    FUN_00405410(*(int *)(puVar4 + 6));
    piVar17 = (int *)(*(int *)(param_3 + 0x38c) + *(int *)(puVar4 + 4));
    *(int **)(param_3 + 0x390) = piVar17;
    goto LAB_0043eea4;
  case 5:
    piVar17 = FUN_0043eda0(0,param_3,puVar4[3]);
    *piVar17 = *piVar17 + -1;
    iVar19 = *(int *)(puVar4 + 4);
    piVar17 = extraout_ECX_14;
    if ((*(byte *)(puVar4 + 3) & 1) != 0) {
      uVar27 = FUN_0043ec70(param_3);
      iVar19 = (int)uVar27;
      piVar17 = extraout_ECX_15;
    }
    if (iVar19 < 1) goto switchD_0043eec4_caseD_0;
    FUN_00405410(*(int *)(puVar4 + 8));
    piVar17 = (int *)(*(int *)(param_3 + 0x38c) + *(int *)(puVar4 + 6));
    *(int **)(param_3 + 0x390) = piVar17;
    goto LAB_0043eea4;
  case 6:
    if ((*(byte *)(puVar4 + 3) & 2) == 0) {
      uVar10 = *(undefined4 *)(puVar4 + 6);
    }
    else {
      uVar27 = FUN_0043ec70(param_3);
      uVar10 = (undefined4)uVar27;
    }
    puVar12 = FUN_0043eda0(0,param_3,puVar4[3]);
    *puVar12 = uVar10;
    *(uint *)(param_3 + 0x390) = (uint)(ushort)puVar4[1] + (int)puVar4;
    piVar17 = extraout_ECX_38;
    goto LAB_0043eea4;
  case 7:
    if ((*(byte *)(puVar4 + 3) & 2) == 0) {
      piStack_b4 = *(int **)(puVar4 + 6);
    }
    else {
      fVar25 = FUN_0043eac0(*(float *)(puVar4 + 6));
      piStack_b4 = (int *)(float)fVar25;
    }
    pfVar15 = (float *)FUN_0043ed00(0,puVar4[3]);
    *pfVar15 = (float)piStack_b4;
    *(uint *)(param_3 + 0x390) = (uint)(ushort)puVar4[1] + (int)puVar4;
    piVar17 = piStack_b4;
    goto LAB_0043eea4;
  case 8:
    if ((*(byte *)(puVar4 + 3) & 2) == 0) {
      iVar19 = *(int *)(puVar4 + 6);
    }
    else {
      uVar27 = FUN_0043ec70(param_3);
      iVar19 = (int)uVar27;
    }
    piVar17 = FUN_0043eda0(0,param_3,puVar4[3]);
    *piVar17 = *piVar17 + iVar19;
    *(uint *)(param_3 + 0x390) = (uint)(ushort)puVar4[1] + (int)puVar4;
    piVar17 = extraout_ECX_48;
    goto LAB_0043eea4;
  case 9:
    if ((*(byte *)(puVar4 + 3) & 2) == 0) {
      fStack_cc = *(float *)(puVar4 + 6);
    }
    else {
      fVar25 = FUN_0043eac0(*(float *)(puVar4 + 6));
      fStack_cc = (float)fVar25;
    }
    pfVar15 = (float *)FUN_0043ed00(0,puVar4[3]);
    *pfVar15 = fStack_cc + *pfVar15;
    *(uint *)(param_3 + 0x390) = (uint)(ushort)puVar4[1] + (int)puVar4;
    piVar17 = extraout_ECX_49;
    goto LAB_0043eea4;
  case 10:
    if ((*(byte *)(puVar4 + 3) & 2) == 0) {
      iVar19 = *(int *)(puVar4 + 6);
    }
    else {
      uVar27 = FUN_0043ec70(param_3);
      iVar19 = (int)uVar27;
    }
    piVar17 = FUN_0043eda0(0,param_3,puVar4[3]);
    *piVar17 = *piVar17 - iVar19;
    *(uint *)(param_3 + 0x390) = (uint)(ushort)puVar4[1] + (int)puVar4;
    piVar17 = extraout_ECX_50;
    goto LAB_0043eea4;
  case 0xb:
    if ((*(byte *)(puVar4 + 3) & 2) == 0) {
      fStack_84 = *(float *)(puVar4 + 6);
    }
    else {
      fVar25 = FUN_0043eac0(*(float *)(puVar4 + 6));
      fStack_84 = (float)fVar25;
    }
    pfVar15 = (float *)FUN_0043ed00(0,puVar4[3]);
    *pfVar15 = *pfVar15 - fStack_84;
    *(uint *)(param_3 + 0x390) = (uint)(ushort)puVar4[1] + (int)puVar4;
    piVar17 = extraout_ECX_51;
    goto LAB_0043eea4;
  case 0xc:
    if ((*(byte *)(puVar4 + 3) & 2) == 0) {
      iVar19 = *(int *)(puVar4 + 6);
    }
    else {
      uVar27 = FUN_0043ec70(param_3);
      iVar19 = (int)uVar27;
    }
    pfVar15 = (float *)FUN_0043eda0(0,param_3,puVar4[3]);
    fVar9 = *pfVar15;
    *pfVar15 = (float)((int)fVar9 * iVar19);
    *(uint *)(param_3 + 0x390) = (uint)(ushort)puVar4[1] + (int)puVar4;
    piVar17 = (int *)((int)fVar9 * iVar19);
    goto LAB_0043eea4;
  case 0xd:
    if ((*(byte *)(puVar4 + 3) & 2) == 0) {
      fStack_50 = *(float *)(puVar4 + 6);
    }
    else {
      fVar25 = FUN_0043eac0(*(float *)(puVar4 + 6));
      fStack_50 = (float)fVar25;
    }
    pfVar15 = (float *)FUN_0043ed00(0,puVar4[3]);
    *pfVar15 = fStack_50 * *pfVar15;
    *(uint *)(param_3 + 0x390) = (uint)(ushort)puVar4[1] + (int)puVar4;
    piVar17 = extraout_ECX_52;
    goto LAB_0043eea4;
  case 0xe:
    if ((*(byte *)(puVar4 + 3) & 2) == 0) {
      iVar19 = *(int *)(puVar4 + 6);
    }
    else {
      uVar27 = FUN_0043ec70(param_3);
      iVar19 = (int)uVar27;
    }
    piVar17 = FUN_0043eda0(0,param_3,puVar4[3]);
    *piVar17 = *piVar17 / iVar19;
    *(uint *)(param_3 + 0x390) = (uint)(ushort)puVar4[1] + (int)puVar4;
    goto LAB_0043eea4;
  case 0xf:
    if ((*(byte *)(puVar4 + 3) & 2) == 0) {
      fStack_7c = *(float *)(puVar4 + 6);
    }
    else {
      fVar25 = FUN_0043eac0(*(float *)(puVar4 + 6));
      fStack_7c = (float)fVar25;
    }
    pfVar15 = (float *)FUN_0043ed00(0,puVar4[3]);
    *pfVar15 = *pfVar15 / fStack_7c;
    *(uint *)(param_3 + 0x390) = (uint)(ushort)puVar4[1] + (int)puVar4;
    piVar17 = extraout_ECX_53;
    goto LAB_0043eea4;
  case 0x10:
    if ((*(byte *)(puVar4 + 3) & 2) == 0) {
      iVar19 = *(int *)(puVar4 + 6);
    }
    else {
      uVar27 = FUN_0043ec70(param_3);
      iVar19 = (int)uVar27;
    }
    piVar17 = FUN_0043eda0(0,param_3,puVar4[3]);
    *piVar17 = *piVar17 % iVar19;
    *(uint *)(param_3 + 0x390) = (uint)(ushort)puVar4[1] + (int)puVar4;
    goto LAB_0043eea4;
  case 0x11:
    if ((*(byte *)(puVar4 + 3) & 2) == 0) {
      fStack_74 = *(float *)(puVar4 + 6);
    }
    else {
      fVar25 = FUN_0043eac0(*(float *)(puVar4 + 6));
      fStack_74 = (float)fVar25;
    }
    if ((*(byte *)(puVar4 + 3) & 1) == 0) {
      fStack_40 = *(float *)(puVar4 + 4);
    }
    else {
      fVar25 = FUN_0043eac0(*(float *)(puVar4 + 4));
      fStack_40 = (float)fVar25;
    }
    pfVar15 = (float *)FUN_0043ed00(0,puVar4[3]);
    fVar25 = (float10)FUN_00463bba(extraout_ECX_54);
    *pfVar15 = (float)fVar25;
    *(uint *)(param_3 + 0x390) = (uint)(ushort)puVar4[1] + (int)puVar4;
    piVar17 = extraout_ECX_55;
    goto LAB_0043eea4;
  case 0x12:
    if ((*(byte *)(puVar4 + 3) & 2) == 0) {
      iVar19 = *(int *)(puVar4 + 6);
    }
    else {
      uVar27 = FUN_0043ec70(param_3);
      iVar19 = (int)uVar27;
    }
    if ((*(byte *)(puVar4 + 3) & 4) == 0) {
      iVar13 = *(int *)(puVar4 + 8);
    }
    else {
      uVar27 = FUN_0043ec70(param_3);
      iVar13 = (int)uVar27;
    }
    piVar17 = FUN_0043eda0(0,param_3,puVar4[3]);
    *piVar17 = iVar13 + iVar19;
    *(uint *)(param_3 + 0x390) = (uint)(ushort)puVar4[1] + (int)puVar4;
    piVar17 = extraout_ECX_39;
    goto LAB_0043eea4;
  case 0x13:
    if ((*(byte *)(puVar4 + 3) & 2) == 0) {
      fStack_ac = *(float *)(puVar4 + 6);
    }
    else {
      fVar25 = FUN_0043eac0(*(float *)(puVar4 + 6));
      fStack_ac = (float)fVar25;
    }
    if ((*(byte *)(puVar4 + 3) & 4) == 0) {
      fStack_5c = *(float *)(puVar4 + 8);
    }
    else {
      fVar25 = FUN_0043eac0(*(float *)(puVar4 + 8));
      fStack_5c = (float)fVar25;
    }
    pfVar15 = (float *)FUN_0043ed00(0,puVar4[3]);
    *pfVar15 = fStack_5c + fStack_ac;
    *(uint *)(param_3 + 0x390) = (uint)(ushort)puVar4[1] + (int)puVar4;
    piVar17 = extraout_ECX_40;
    goto LAB_0043eea4;
  case 0x14:
    if ((*(byte *)(puVar4 + 3) & 2) == 0) {
      iVar19 = *(int *)(puVar4 + 6);
    }
    else {
      uVar27 = FUN_0043ec70(param_3);
      iVar19 = (int)uVar27;
    }
    if ((*(byte *)(puVar4 + 3) & 4) == 0) {
      iVar13 = *(int *)(puVar4 + 8);
    }
    else {
      uVar27 = FUN_0043ec70(param_3);
      iVar13 = (int)uVar27;
    }
    piVar17 = FUN_0043eda0(0,param_3,puVar4[3]);
    *piVar17 = iVar19 - iVar13;
    *(uint *)(param_3 + 0x390) = (uint)(ushort)puVar4[1] + (int)puVar4;
    piVar17 = extraout_ECX_41;
    goto LAB_0043eea4;
  case 0x15:
    if ((*(byte *)(puVar4 + 3) & 2) == 0) {
      fStack_64 = *(float *)(puVar4 + 6);
    }
    else {
      fVar25 = FUN_0043eac0(*(float *)(puVar4 + 6));
      fStack_64 = (float)fVar25;
    }
    if ((*(byte *)(puVar4 + 3) & 4) == 0) {
      fStack_a4 = *(float *)(puVar4 + 8);
    }
    else {
      fVar25 = FUN_0043eac0(*(float *)(puVar4 + 8));
      fStack_a4 = (float)fVar25;
    }
    pfVar15 = (float *)FUN_0043ed00(0,puVar4[3]);
    *pfVar15 = fStack_64 - fStack_a4;
    *(uint *)(param_3 + 0x390) = (uint)(ushort)puVar4[1] + (int)puVar4;
    piVar17 = extraout_ECX_42;
    goto LAB_0043eea4;
  case 0x16:
    if ((*(byte *)(puVar4 + 3) & 2) == 0) {
      iVar19 = *(int *)(puVar4 + 6);
    }
    else {
      uVar27 = FUN_0043ec70(param_3);
      iVar19 = (int)uVar27;
    }
    if ((*(byte *)(puVar4 + 3) & 4) == 0) {
      iVar13 = *(int *)(puVar4 + 8);
    }
    else {
      uVar27 = FUN_0043ec70(param_3);
      iVar13 = (int)uVar27;
    }
    piVar17 = FUN_0043eda0(0,param_3,puVar4[3]);
    *piVar17 = iVar13 * iVar19;
    *(uint *)(param_3 + 0x390) = (uint)(ushort)puVar4[1] + (int)puVar4;
    piVar17 = extraout_ECX_43;
    goto LAB_0043eea4;
  case 0x17:
    if ((*(byte *)(puVar4 + 3) & 2) == 0) {
      fStack_9c = *(float *)(puVar4 + 6);
    }
    else {
      fVar25 = FUN_0043eac0(*(float *)(puVar4 + 6));
      fStack_9c = (float)fVar25;
    }
    if ((*(byte *)(puVar4 + 3) & 4) == 0) {
      fStack_54 = *(float *)(puVar4 + 8);
    }
    else {
      fVar25 = FUN_0043eac0(*(float *)(puVar4 + 8));
      fStack_54 = (float)fVar25;
    }
    pfVar15 = (float *)FUN_0043ed00(0,puVar4[3]);
    *pfVar15 = fStack_54 * fStack_9c;
    *(uint *)(param_3 + 0x390) = (uint)(ushort)puVar4[1] + (int)puVar4;
    piVar17 = extraout_ECX_44;
    goto LAB_0043eea4;
  case 0x18:
    if ((*(byte *)(puVar4 + 3) & 2) == 0) {
      iVar19 = *(int *)(puVar4 + 6);
    }
    else {
      uVar27 = FUN_0043ec70(param_3);
      iVar19 = (int)uVar27;
    }
    if ((*(byte *)(puVar4 + 3) & 4) == 0) {
      iVar13 = *(int *)(puVar4 + 8);
    }
    else {
      uVar27 = FUN_0043ec70(param_3);
      iVar13 = (int)uVar27;
    }
    piVar17 = FUN_0043eda0(0,param_3,puVar4[3]);
    *piVar17 = iVar19 / iVar13;
    *(uint *)(param_3 + 0x390) = (uint)(ushort)puVar4[1] + (int)puVar4;
    goto LAB_0043eea4;
  case 0x19:
    if ((*(byte *)(puVar4 + 3) & 2) == 0) {
      fStack_4c = *(float *)(puVar4 + 6);
    }
    else {
      fVar25 = FUN_0043eac0(*(float *)(puVar4 + 6));
      fStack_4c = (float)fVar25;
    }
    if ((*(byte *)(puVar4 + 3) & 4) == 0) {
      fStack_94 = *(float *)(puVar4 + 8);
    }
    else {
      fVar25 = FUN_0043eac0(*(float *)(puVar4 + 8));
      fStack_94 = (float)fVar25;
    }
    pfVar15 = (float *)FUN_0043ed00(0,puVar4[3]);
    *pfVar15 = fStack_4c / fStack_94;
    *(uint *)(param_3 + 0x390) = (uint)(ushort)puVar4[1] + (int)puVar4;
    piVar17 = extraout_ECX_45;
    goto LAB_0043eea4;
  case 0x1a:
    if ((*(byte *)(puVar4 + 3) & 2) == 0) {
      iVar19 = *(int *)(puVar4 + 6);
    }
    else {
      uVar27 = FUN_0043ec70(param_3);
      iVar19 = (int)uVar27;
    }
    if ((*(byte *)(puVar4 + 3) & 4) == 0) {
      iVar13 = *(int *)(puVar4 + 8);
    }
    else {
      uVar27 = FUN_0043ec70(param_3);
      iVar13 = (int)uVar27;
    }
    piVar17 = FUN_0043eda0(0,param_3,puVar4[3]);
    *piVar17 = iVar19 % iVar13;
    *(uint *)(param_3 + 0x390) = (uint)(ushort)puVar4[1] + (int)puVar4;
    goto LAB_0043eea4;
  case 0x1b:
    if ((*(byte *)(puVar4 + 3) & 4) == 0) {
      local_8c = *(float *)(puVar4 + 8);
    }
    else {
      fVar25 = FUN_0043eac0(*(float *)(puVar4 + 8));
      local_8c = (float)fVar25;
    }
    if ((*(byte *)(puVar4 + 3) & 2) == 0) {
      local_58 = *(float *)(puVar4 + 6);
    }
    else {
      fVar25 = FUN_0043eac0(*(float *)(puVar4 + 6));
      local_58 = (float)fVar25;
    }
    pfVar15 = (float *)FUN_0043ed00(0,puVar4[3]);
    fVar25 = (float10)FUN_00463bba(extraout_ECX_46);
    *pfVar15 = (float)fVar25;
    *(uint *)(param_3 + 0x390) = (uint)(ushort)puVar4[1] + (int)puVar4;
    piVar17 = extraout_ECX_47;
    goto LAB_0043eea4;
  case 0x1c:
    if ((*(byte *)(puVar4 + 3) & 1) == 0) {
      iVar19 = *(int *)(puVar4 + 4);
    }
    else {
      uVar27 = FUN_0043ec70(param_3);
      iVar19 = (int)uVar27;
      piVar17 = extraout_ECX_64;
    }
    iVar13 = *(int *)(puVar4 + 6);
    if ((*(byte *)(puVar4 + 3) & 2) != 0) {
      uVar27 = FUN_0043ec70(param_3);
      iVar13 = (int)uVar27;
      piVar17 = extraout_ECX_65;
    }
    if (iVar19 != iVar13) {
      *(uint *)(param_3 + 0x390) = (uint)(ushort)puVar4[1] + (int)puVar4;
      goto LAB_0043eea4;
    }
    break;
  case 0x1d:
    if ((*(byte *)(puVar4 + 3) & 1) == 0) {
      piVar17 = *(int **)(puVar4 + 4);
      local_98 = piVar17;
    }
    else {
      fVar25 = FUN_0043eac0(*(float *)(puVar4 + 4));
      piVar17 = extraout_ECX_66;
      local_98 = (int *)(float)fVar25;
    }
    if ((*(byte *)(puVar4 + 3) & 2) == 0) {
      fVar25 = (float10)*(float *)(puVar4 + 6);
    }
    else {
      fVar25 = FUN_0043eac0(*(float *)(puVar4 + 6));
      piVar17 = extraout_ECX_67;
    }
    if ((float10)(float)local_98 != fVar25) {
      *(uint *)(param_3 + 0x390) = (uint)(ushort)puVar4[1] + (int)puVar4;
      goto LAB_0043eea4;
    }
    break;
  case 0x1e:
    if ((*(byte *)(puVar4 + 3) & 1) == 0) {
      iVar19 = *(int *)(puVar4 + 4);
    }
    else {
      uVar27 = FUN_0043ec70(param_3);
      iVar19 = (int)uVar27;
      piVar17 = extraout_ECX_68;
    }
    iVar13 = *(int *)(puVar4 + 6);
    if ((*(byte *)(puVar4 + 3) & 2) != 0) {
      uVar27 = FUN_0043ec70(param_3);
      iVar13 = (int)uVar27;
      piVar17 = extraout_ECX_69;
    }
    if (iVar19 == iVar13) {
      *(uint *)(param_3 + 0x390) = (uint)(ushort)puVar4[1] + (int)puVar4;
      goto LAB_0043eea4;
    }
    break;
  case 0x1f:
    if ((*(byte *)(puVar4 + 3) & 1) == 0) {
      piVar17 = *(int **)(puVar4 + 4);
      local_90 = piVar17;
    }
    else {
      fVar25 = FUN_0043eac0(*(float *)(puVar4 + 4));
      piVar17 = extraout_ECX_70;
      local_90 = (int *)(float)fVar25;
    }
    if ((*(byte *)(puVar4 + 3) & 2) == 0) {
      fVar25 = (float10)*(float *)(puVar4 + 6);
    }
    else {
      fVar25 = FUN_0043eac0(*(float *)(puVar4 + 6));
      piVar17 = extraout_ECX_71;
    }
    if ((float10)(float)local_90 == fVar25) {
      *(uint *)(param_3 + 0x390) = (uint)(ushort)puVar4[1] + (int)puVar4;
      goto LAB_0043eea4;
    }
    break;
  case 0x20:
    if ((*(byte *)(puVar4 + 3) & 1) == 0) {
      iVar19 = *(int *)(puVar4 + 4);
    }
    else {
      uVar27 = FUN_0043ec70(param_3);
      iVar19 = (int)uVar27;
      piVar17 = extraout_ECX_72;
    }
    iVar13 = *(int *)(puVar4 + 6);
    if ((*(byte *)(puVar4 + 3) & 2) != 0) {
      uVar27 = FUN_0043ec70(param_3);
      iVar13 = (int)uVar27;
      piVar17 = extraout_ECX_73;
    }
    if (iVar13 <= iVar19) {
      *(uint *)(param_3 + 0x390) = (uint)(ushort)puVar4[1] + (int)puVar4;
      goto LAB_0043eea4;
    }
    break;
  case 0x21:
    if ((*(byte *)(puVar4 + 3) & 1) == 0) {
      piVar17 = *(int **)(puVar4 + 4);
      local_88 = piVar17;
    }
    else {
      fVar25 = FUN_0043eac0(*(float *)(puVar4 + 4));
      piVar17 = extraout_ECX_74;
      local_88 = (int *)(float)fVar25;
    }
    if ((*(byte *)(puVar4 + 3) & 2) == 0) {
      fVar25 = (float10)*(float *)(puVar4 + 6);
    }
    else {
      fVar25 = FUN_0043eac0(*(float *)(puVar4 + 6));
      piVar17 = extraout_ECX_75;
    }
    if (fVar25 <= (float10)(float)local_88) {
      *(uint *)(param_3 + 0x390) = (uint)(ushort)puVar4[1] + (int)puVar4;
      goto LAB_0043eea4;
    }
    break;
  case 0x22:
    if ((*(byte *)(puVar4 + 3) & 1) == 0) {
      iVar19 = *(int *)(puVar4 + 4);
    }
    else {
      uVar27 = FUN_0043ec70(param_3);
      iVar19 = (int)uVar27;
      piVar17 = extraout_ECX_76;
    }
    iVar13 = *(int *)(puVar4 + 6);
    if ((*(byte *)(puVar4 + 3) & 2) != 0) {
      uVar27 = FUN_0043ec70(param_3);
      iVar13 = (int)uVar27;
      piVar17 = extraout_ECX_77;
    }
    if (iVar13 < iVar19) {
      *(uint *)(param_3 + 0x390) = (uint)(ushort)puVar4[1] + (int)puVar4;
      goto LAB_0043eea4;
    }
    break;
  case 0x23:
    if ((*(byte *)(puVar4 + 3) & 1) == 0) {
      piVar17 = *(int **)(puVar4 + 4);
      local_80 = piVar17;
    }
    else {
      fVar25 = FUN_0043eac0(*(float *)(puVar4 + 4));
      piVar17 = extraout_ECX_78;
      local_80 = (int *)(float)fVar25;
    }
    if ((*(byte *)(puVar4 + 3) & 2) == 0) {
      fVar25 = (float10)*(float *)(puVar4 + 6);
    }
    else {
      fVar25 = FUN_0043eac0(*(float *)(puVar4 + 6));
      piVar17 = extraout_ECX_79;
    }
    if ((float10)(float)local_80 < fVar25 == ((float10)(float)local_80 == fVar25)) {
      *(uint *)(param_3 + 0x390) = (uint)(ushort)puVar4[1] + (int)puVar4;
      goto LAB_0043eea4;
    }
    break;
  case 0x24:
    if ((*(byte *)(puVar4 + 3) & 1) == 0) {
      iVar19 = *(int *)(puVar4 + 4);
    }
    else {
      uVar27 = FUN_0043ec70(param_3);
      iVar19 = (int)uVar27;
      piVar17 = extraout_ECX_80;
    }
    iVar13 = *(int *)(puVar4 + 6);
    if ((*(byte *)(puVar4 + 3) & 2) != 0) {
      uVar27 = FUN_0043ec70(param_3);
      iVar13 = (int)uVar27;
      piVar17 = extraout_ECX_81;
    }
    if (iVar19 <= iVar13) {
      *(uint *)(param_3 + 0x390) = (uint)(ushort)puVar4[1] + (int)puVar4;
      goto LAB_0043eea4;
    }
    break;
  case 0x25:
    if ((*(byte *)(puVar4 + 3) & 1) == 0) {
      piVar17 = *(int **)(puVar4 + 4);
      local_78 = piVar17;
    }
    else {
      fVar25 = FUN_0043eac0(*(float *)(puVar4 + 4));
      piVar17 = extraout_ECX_82;
      local_78 = (int *)(float)fVar25;
    }
    if ((*(byte *)(puVar4 + 3) & 2) == 0) {
      fVar25 = (float10)*(float *)(puVar4 + 6);
    }
    else {
      fVar25 = FUN_0043eac0(*(float *)(puVar4 + 6));
      piVar17 = extraout_ECX_83;
    }
    if ((float10)(float)local_78 <= fVar25) {
      *(uint *)(param_3 + 0x390) = (uint)(ushort)puVar4[1] + (int)puVar4;
      goto LAB_0043eea4;
    }
    break;
  case 0x26:
    if ((*(byte *)(puVar4 + 3) & 1) == 0) {
      iVar19 = *(int *)(puVar4 + 4);
    }
    else {
      uVar27 = FUN_0043ec70(param_3);
      iVar19 = (int)uVar27;
      piVar17 = extraout_ECX_84;
    }
    iVar13 = *(int *)(puVar4 + 6);
    if ((*(byte *)(puVar4 + 3) & 2) != 0) {
      uVar27 = FUN_0043ec70(param_3);
      iVar13 = (int)uVar27;
      piVar17 = extraout_ECX_85;
    }
    if (iVar19 < iVar13) {
      *(uint *)(param_3 + 0x390) = (uint)(ushort)puVar4[1] + (int)puVar4;
      goto LAB_0043eea4;
    }
    break;
  case 0x27:
    if ((*(byte *)(puVar4 + 3) & 1) == 0) {
      piVar17 = *(int **)(puVar4 + 4);
      local_e0 = piVar17;
    }
    else {
      fVar25 = FUN_0043eac0(*(float *)(puVar4 + 4));
      piVar17 = extraout_ECX_86;
      local_e0 = (int *)(float)fVar25;
    }
    if ((*(byte *)(puVar4 + 3) & 2) == 0) {
      fVar25 = (float10)*(float *)(puVar4 + 6);
    }
    else {
      fVar25 = FUN_0043eac0(*(float *)(puVar4 + 6));
      piVar17 = extraout_ECX_87;
    }
    if (fVar25 <= (float10)(float)local_e0) break;
    goto switchD_0043eec4_caseD_0;
  case 0x28:
    if ((*(uint *)(param_3 + 0x35c) & 0x40000000) == 0) {
      if ((*(byte *)(puVar4 + 3) & 2) != 0) {
        FUN_0043ec70(param_3);
      }
      puVar18 = &DAT_004918b0;
    }
    else {
      if ((*(byte *)(puVar4 + 3) & 2) != 0) {
        FUN_0043ec70(param_3);
      }
      puVar18 = (ushort *)&DAT_004918a8;
    }
    uVar21 = FUN_0043cb80(puVar18);
    puVar14 = FUN_0043eda0(0,param_3,puVar4[3]);
    *puVar14 = uVar21;
    *(uint *)(param_3 + 0x390) = (uint)(ushort)puVar4[1] + (int)puVar4;
    piVar17 = extraout_ECX_56;
    goto LAB_0043eea4;
  case 0x29:
    if ((*(uint *)(param_3 + 0x35c) & 0x40000000) == 0) {
      if ((*(byte *)(puVar4 + 3) & 2) != 0) {
        FUN_0043eac0(*(float *)(puVar4 + 6));
      }
      puVar18 = &DAT_004918b0;
    }
    else if ((*(byte *)(puVar4 + 3) & 2) == 0) {
      puVar18 = (ushort *)&DAT_004918a8;
    }
    else {
      FUN_0043eac0(*(float *)(puVar4 + 6));
      puVar18 = (ushort *)&DAT_004918a8;
    }
    fVar25 = FUN_0044bb20(puVar18);
    local_f8 = (float)(fVar25 * extraout_ST1);
    pfVar15 = (float *)FUN_0043ed00(0,puVar4[3]);
    *pfVar15 = local_f8;
    *(uint *)(param_3 + 0x390) = (uint)(ushort)puVar4[1] + (int)puVar4;
    piVar17 = extraout_ECX_57;
    goto LAB_0043eea4;
  case 0x2a:
    if ((*(byte *)(puVar4 + 3) & 2) == 0) {
      local_c8 = *(float *)(puVar4 + 6);
    }
    else {
      fVar25 = FUN_0043eac0(*(float *)(puVar4 + 6));
      local_c8 = (float)fVar25;
    }
    pfVar15 = (float *)FUN_0043ed00(0,puVar4[3]);
    fVar25 = (float10)fsin((float10)local_c8);
    *pfVar15 = (float)fVar25;
    *(uint *)(param_3 + 0x390) = (uint)(ushort)puVar4[1] + (int)puVar4;
    piVar17 = extraout_ECX_58;
    goto LAB_0043eea4;
  case 0x2b:
    if ((*(byte *)(puVar4 + 3) & 2) == 0) {
      local_c0 = *(float *)(puVar4 + 6);
    }
    else {
      fVar25 = FUN_0043eac0(*(float *)(puVar4 + 6));
      local_c0 = (float)fVar25;
    }
    pfVar15 = (float *)FUN_0043ed00(0,puVar4[3]);
    fVar25 = (float10)fcos((float10)local_c0);
    *pfVar15 = (float)fVar25;
    *(uint *)(param_3 + 0x390) = (uint)(ushort)puVar4[1] + (int)puVar4;
    piVar17 = extraout_ECX_59;
    goto LAB_0043eea4;
  case 0x2c:
    if ((*(byte *)(puVar4 + 3) & 2) == 0) {
      local_b8 = *(float *)(puVar4 + 6);
    }
    else {
      fVar25 = FUN_0043eac0(*(float *)(puVar4 + 6));
      local_b8 = (float)fVar25;
    }
    pfVar15 = (float *)FUN_0043ed00(0,puVar4[3]);
    fVar25 = (float10)fptan((float10)local_b8);
    *pfVar15 = (float)fVar25;
    *(uint *)(param_3 + 0x390) = (uint)(ushort)puVar4[1] + (int)puVar4;
    piVar17 = extraout_ECX_60;
    goto LAB_0043eea4;
  case 0x2d:
    if ((*(byte *)(puVar4 + 3) & 2) == 0) {
      local_b0 = *(float *)(puVar4 + 6);
    }
    else {
      fVar25 = FUN_0043eac0(*(float *)(puVar4 + 6));
      local_b0 = (float)fVar25;
    }
    pfVar15 = (float *)FUN_0043ed00(0,puVar4[3]);
    fVar25 = (float10)FUN_00463bf0();
    *pfVar15 = (float)fVar25;
    *(uint *)(param_3 + 0x390) = (uint)(ushort)puVar4[1] + (int)puVar4;
    piVar17 = extraout_ECX_61;
    goto LAB_0043eea4;
  case 0x2e:
    if ((*(byte *)(puVar4 + 3) & 2) == 0) {
      local_a8 = *(float *)(puVar4 + 6);
    }
    else {
      fVar25 = FUN_0043eac0(*(float *)(puVar4 + 6));
      local_a8 = (float)fVar25;
    }
    pfVar15 = (float *)FUN_0043ed00(0,puVar4[3]);
    fVar25 = (float10)fpatan((float10)local_a8,(float10)1);
    *pfVar15 = (float)fVar25;
    *(uint *)(param_3 + 0x390) = (uint)(ushort)puVar4[1] + (int)puVar4;
    piVar17 = extraout_ECX_62;
    goto LAB_0043eea4;
  case 0x2f:
    if ((*(byte *)(puVar4 + 3) & 1) == 0) {
      local_a0 = *(float *)(puVar4 + 4);
    }
    else {
      fVar25 = FUN_0043eac0(*(float *)(puVar4 + 4));
      local_a0 = (float)fVar25;
    }
    pfVar15 = (float *)FUN_0043ed00(0,puVar4[3]);
    fVar25 = (float10)FUN_0044bc10(local_a0,0.0);
    *pfVar15 = (float)fVar25;
    *(uint *)(param_3 + 0x390) = (uint)(ushort)puVar4[1] + (int)puVar4;
    piVar17 = extraout_ECX_63;
    goto LAB_0043eea4;
  case 0x30:
    if ((*(uint *)(param_3 + 0x35c) & 0x100) == 0) {
      if ((*(byte *)(puVar4 + 3) & 4) == 0) {
        local_c4 = *(float *)(puVar4 + 8);
      }
      else {
        fVar25 = FUN_0043eac0(*(float *)(puVar4 + 8));
        local_c4 = (float)fVar25;
      }
      if ((*(byte *)(puVar4 + 3) & 2) == 0) {
        local_48 = *(int **)(puVar4 + 6);
      }
      else {
        fVar25 = FUN_0043eac0(*(float *)(puVar4 + 6));
        local_48 = (int *)(float)fVar25;
      }
      if ((*(byte *)(puVar4 + 3) & 1) == 0) {
        fVar25 = (float10)*(float *)(puVar4 + 4);
      }
      else {
        fVar25 = FUN_0043eac0(*(float *)(puVar4 + 4));
      }
      local_14 = (float)fVar25;
      local_10 = local_48;
      pfVar15 = (float *)(param_3 + 0x334);
      local_c = local_c4;
      *pfVar15 = local_14;
      *(int **)(param_3 + 0x338) = local_48;
      fVar9 = local_c4;
      piVar17 = local_48;
    }
    else {
      if ((*(byte *)(puVar4 + 3) & 4) == 0) {
        local_70 = *(float *)(puVar4 + 8);
      }
      else {
        fVar25 = FUN_0043eac0(*(float *)(puVar4 + 8));
        local_70 = (float)fVar25;
      }
      if ((*(byte *)(puVar4 + 3) & 2) == 0) {
        local_38 = *(int **)(puVar4 + 6);
      }
      else {
        fVar25 = FUN_0043eac0(*(float *)(puVar4 + 6));
        local_38 = (int *)(float)fVar25;
      }
      if ((*(byte *)(puVar4 + 3) & 1) == 0) {
        fVar25 = (float10)*(float *)(puVar4 + 4);
      }
      else {
        fVar25 = FUN_0043eac0(*(float *)(puVar4 + 4));
      }
      local_20 = local_38;
      local_24 = (float)fVar25;
      local_1c = local_70;
      pfVar15 = (float *)(param_3 + 0x34c);
      *pfVar15 = local_24;
      *(int **)(param_3 + 0x350) = local_38;
      fVar9 = local_70;
      piVar17 = local_38;
    }
    pfVar15[2] = fVar9;
    goto switchD_0043eec4_caseD_0;
  case 0x31:
    if ((*(byte *)(puVar4 + 3) & 1) == 0) {
      fVar25 = (float10)*(float *)(puVar4 + 4);
    }
    else {
      fVar25 = FUN_0043eac0(*(float *)(puVar4 + 4));
      piVar17 = extraout_ECX_16;
    }
    *(float *)(param_3 + 0x24) = (float)fVar25;
    if ((*(byte *)(puVar4 + 3) & 2) == 0) {
      fVar25 = (float10)*(float *)(puVar4 + 6);
    }
    else {
      fVar25 = FUN_0043eac0(*(float *)(puVar4 + 6));
      piVar17 = extraout_ECX_17;
    }
    *(float *)(param_3 + 0x28) = (float)fVar25;
    if ((*(byte *)(puVar4 + 3) & 4) == 0) {
      fVar25 = (float10)*(float *)(puVar4 + 8);
    }
    else {
      fVar25 = FUN_0043eac0(*(float *)(puVar4 + 8));
      piVar17 = extraout_ECX_18;
    }
    *(float *)(param_3 + 0x2c) = (float)fVar25;
    *(uint *)(param_3 + 0x35c) = *(uint *)(param_3 + 0x35c) | 4;
    *(uint *)(param_3 + 0x390) = (uint)(ushort)puVar4[1] + (int)puVar4;
    goto LAB_0043eea4;
  case 0x32:
    if ((*(byte *)(puVar4 + 3) & 1) == 0) {
      fVar25 = (float10)*(float *)(puVar4 + 4);
    }
    else {
      fVar25 = FUN_0043eac0(*(float *)(puVar4 + 4));
      piVar17 = extraout_ECX_04;
    }
    *(float *)(param_3 + 0x3c) = (float)fVar25;
    if ((*(byte *)(puVar4 + 3) & 2) == 0) {
      fVar25 = (float10)*(float *)(puVar4 + 6);
    }
    else {
      fVar25 = FUN_0043eac0(*(float *)(puVar4 + 6));
      piVar17 = extraout_ECX_05;
    }
    *(float *)(param_3 + 0x40) = (float)fVar25;
    *(uint *)(param_3 + 0x35c) = *(uint *)(param_3 + 0x35c) | 8;
    *(uint *)(param_3 + 0x390) = (uint)(ushort)puVar4[1] + (int)puVar4;
    goto LAB_0043eea4;
  case 0x33:
    uVar6 = (undefined1)*(undefined4 *)(puVar4 + 4);
    if ((*(byte *)(puVar4 + 3) & 1) != 0) {
      uVar27 = FUN_0043ec70(param_3);
      uVar6 = (undefined1)uVar27;
      piVar17 = extraout_ECX_06;
    }
    *(undefined1 *)(param_3 + 0x2ff) = uVar6;
    *(uint *)(param_3 + 0x390) = (uint)(ushort)puVar4[1] + (int)puVar4;
    goto LAB_0043eea4;
  case 0x34:
    uVar6 = (undefined1)*(undefined4 *)(puVar4 + 4);
    if ((*(byte *)(puVar4 + 3) & 1) != 0) {
      uVar27 = FUN_0043ec70(param_3);
      uVar6 = (undefined1)uVar27;
      piVar17 = extraout_ECX_07;
    }
    *(undefined1 *)(param_3 + 0x2fe) = uVar6;
    uVar6 = (undefined1)*(undefined4 *)(puVar4 + 6);
    if ((*(byte *)(puVar4 + 3) & 2) != 0) {
      uVar27 = FUN_0043ec70(param_3);
      uVar6 = (undefined1)uVar27;
      piVar17 = extraout_ECX_08;
    }
    *(undefined1 *)(param_3 + 0x2fd) = uVar6;
    uVar6 = (undefined1)*(undefined4 *)(puVar4 + 8);
    if ((*(byte *)(puVar4 + 3) & 4) != 0) {
      uVar27 = FUN_0043ec70(param_3);
      uVar6 = (undefined1)uVar27;
      piVar17 = extraout_ECX_09;
    }
    *(undefined1 *)(param_3 + 0x2fc) = uVar6;
    *(uint *)(param_3 + 0x390) = (uint)(ushort)puVar4[1] + (int)puVar4;
    goto LAB_0043eea4;
  case 0x35:
    if ((*(byte *)(puVar4 + 3) & 1) == 0) {
      fVar25 = (float10)*(float *)(puVar4 + 4);
    }
    else {
      fVar25 = FUN_0043eac0(*(float *)(puVar4 + 4));
      piVar17 = extraout_ECX_19;
    }
    *(float *)(param_3 + 0x30) = (float)fVar25;
    if ((*(byte *)(puVar4 + 3) & 2) == 0) {
      fVar25 = (float10)*(float *)(puVar4 + 6);
    }
    else {
      fVar25 = FUN_0043eac0(*(float *)(puVar4 + 6));
      piVar17 = extraout_ECX_20;
    }
    *(float *)(param_3 + 0x34) = (float)fVar25;
    if ((*(byte *)(puVar4 + 3) & 4) == 0) {
      fVar25 = (float10)*(float *)(puVar4 + 8);
    }
    else {
      fVar25 = FUN_0043eac0(*(float *)(puVar4 + 8));
      piVar17 = extraout_ECX_21;
    }
    *(float *)(param_3 + 0x38) = (float)fVar25;
    *(uint *)(param_3 + 0x35c) = *(uint *)(param_3 + 0x35c) | 4;
    *(uint *)(param_3 + 0x390) = (uint)(ushort)puVar4[1] + (int)puVar4;
    goto LAB_0043eea4;
  case 0x36:
    if ((*(byte *)(puVar4 + 3) & 1) == 0) {
      fVar25 = (float10)*(float *)(puVar4 + 4);
    }
    else {
      fVar25 = FUN_0043eac0(*(float *)(puVar4 + 4));
      piVar17 = extraout_ECX_22;
    }
    *(float *)(param_3 + 0x44) = (float)fVar25;
    if ((*(byte *)(puVar4 + 3) & 2) == 0) {
      *(undefined4 *)(param_3 + 0x48) = *(undefined4 *)(puVar4 + 6);
      *(uint *)(param_3 + 0x390) = (uint)(ushort)puVar4[1] + (int)puVar4;
    }
    else {
      fVar25 = FUN_0043eac0(*(float *)(puVar4 + 6));
      *(float *)(param_3 + 0x48) = (float)fVar25;
      *(uint *)(param_3 + 0x390) = (uint)(ushort)puVar4[1] + (int)puVar4;
      piVar17 = extraout_ECX_23;
    }
    goto LAB_0043eea4;
  case 0x37:
    uVar27 = CONCAT44(iVar19,*(undefined4 *)(puVar4 + 6));
    if ((*(byte *)(puVar4 + 3) & 2) != 0) {
      uVar27 = FUN_0043ec70(param_3);
    }
    FUN_00442300((void *)uVar27,0,*(byte *)(param_3 + 0x2ff),*(byte *)(puVar4 + 4));
    *(uint *)(param_3 + 0x390) = (uint)(ushort)puVar4[1] + (int)puVar4;
    piVar17 = extraout_ECX_24;
    goto LAB_0043eea4;
  case 0x38:
    uVar10 = *(undefined4 *)(puVar4 + 4);
    if ((*(byte *)(puVar4 + 3) & 1) != 0) {
      uVar27 = FUN_0043ec70(param_3);
      uVar10 = (undefined4)uVar27;
    }
    *(undefined4 *)(param_3 + 0xb4) = uVar10;
    *(undefined4 *)(param_3 + 0x88) = DAT_00491c14;
    *(undefined4 *)(param_3 + 0x8c) = DAT_00491c18;
    *(undefined4 *)(param_3 + 0x90) = DAT_00491c1c;
    *(undefined4 *)(param_3 + 0x94) = DAT_00491c14;
    *(undefined4 *)(param_3 + 0x98) = DAT_00491c18;
    *(undefined4 *)(param_3 + 0x9c) = DAT_00491c1c;
    *(undefined4 *)(param_3 + 0xb8) = *(undefined4 *)(puVar4 + 6);
    if ((*(uint *)(param_3 + 0x35c) & 0x100) == 0) {
      *(undefined4 *)(param_3 + 0x70) = *(undefined4 *)(param_3 + 0x334);
      *(undefined4 *)(param_3 + 0x74) = *(undefined4 *)(param_3 + 0x338);
      *(undefined4 *)(param_3 + 0x78) = *(undefined4 *)(param_3 + 0x33c);
    }
    else {
      *(undefined4 *)(param_3 + 0x70) = *(undefined4 *)(param_3 + 0x34c);
      *(undefined4 *)(param_3 + 0x74) = *(undefined4 *)(param_3 + 0x350);
      *(undefined4 *)(param_3 + 0x78) = *(undefined4 *)(param_3 + 0x354);
    }
    if ((*(byte *)(puVar4 + 3) & 0x10) == 0) {
      local_3c = *(float *)(puVar4 + 0xc);
    }
    else {
      fVar25 = FUN_0043eac0(*(float *)(puVar4 + 0xc));
      local_3c = (float)fVar25;
    }
    if ((*(byte *)(puVar4 + 3) & 8) == 0) {
      local_44 = *(float *)(puVar4 + 10);
    }
    else {
      fVar25 = FUN_0043eac0(*(float *)(puVar4 + 10));
      local_44 = (float)fVar25;
    }
    if ((*(byte *)(puVar4 + 3) & 4) == 0) {
      fVar25 = (float10)*(float *)(puVar4 + 8);
    }
    else {
      fVar25 = FUN_0043eac0(*(float *)(puVar4 + 8));
    }
    local_34 = (float)fVar25;
    local_30 = local_44;
    local_2c = local_3c;
    *(float *)(param_3 + 0x7c) = local_34;
    *(float *)(param_3 + 0x80) = local_44;
    *(float *)(param_3 + 0x84) = local_3c;
    FUN_004050d0();
    *(uint *)(param_3 + 0x390) = (uint)(ushort)puVar4[1] + (int)puVar4;
    piVar17 = extraout_ECX_29;
    goto LAB_0043eea4;
  case 0x39:
    local_d0 = *(byte *)(param_3 + 0x2fc);
    local_cf = *(undefined1 *)(param_3 + 0x2fd);
    local_ce = *(undefined1 *)(param_3 + 0x2fe);
    uVar27 = (ulonglong)*(uint *)(puVar4 + 0xc);
    if ((*(byte *)(puVar4 + 3) & 0x10) != 0) {
      uVar27 = FUN_0043ec70(param_3);
    }
    local_e8 = (undefined4)uVar27;
    if ((*(byte *)(puVar4 + 3) & 8) == 0) {
      local_f8 = *(float *)(puVar4 + 10);
    }
    else {
      uVar27 = FUN_0043ec70(param_3);
      local_f8 = (float)uVar27;
    }
    uVar6 = (undefined1)*(undefined4 *)(puVar4 + 8);
    if ((*(byte *)(puVar4 + 3) & 4) != 0) {
      uVar27 = FUN_0043ec70(param_3);
      uVar6 = (undefined1)uVar27;
    }
    uVar27 = (ulonglong)*(uint *)(puVar4 + 4);
    local_fc = (float)CONCAT22(CONCAT11(local_fc._3_1_,uVar6),
                               CONCAT11(local_f8._0_1_,(undefined1)local_e8));
    if ((*(byte *)(puVar4 + 3) & 1) != 0) {
      uVar27 = FUN_0043ec70(param_3);
    }
    FUN_00442220((byte *)&local_fc,&local_d0,(int)uVar27,*(byte *)(puVar4 + 6));
    *(uint *)(param_3 + 0x390) = (uint)(ushort)puVar4[1] + (int)puVar4;
    piVar17 = extraout_ECX_30;
    goto LAB_0043eea4;
  case 0x3a:
    if ((*(byte *)(puVar4 + 3) & 4) == 0) {
      bVar7 = (byte)*(undefined4 *)(puVar4 + 8);
    }
    else {
      uVar27 = FUN_0043ec70(param_3);
      bVar7 = (byte)uVar27;
    }
    uVar27 = (ulonglong)*(uint *)(puVar4 + 4);
    if ((*(byte *)(puVar4 + 3) & 1) != 0) {
      uVar27 = FUN_0043ec70(param_3);
    }
    FUN_00442300((void *)uVar27,*(byte *)(puVar4 + 6),*(byte *)(param_3 + 0x2ff),bVar7);
    *(uint *)(param_3 + 0x390) = (uint)(ushort)puVar4[1] + (int)puVar4;
    piVar17 = extraout_ECX_31;
    goto LAB_0043eea4;
  case 0x3b:
    if ((*(byte *)(puVar4 + 3) & 0x10) == 0) {
      local_bc = *(float *)(puVar4 + 0xc);
    }
    else {
      fVar25 = FUN_0043eac0(*(float *)(puVar4 + 0xc));
      local_bc = (float)fVar25;
    }
    if ((*(byte *)(puVar4 + 3) & 8) == 0) {
      local_60 = *(float *)(puVar4 + 10);
    }
    else {
      fVar25 = FUN_0043eac0(*(float *)(puVar4 + 10));
      local_60 = (float)fVar25;
    }
    if ((*(byte *)(puVar4 + 3) & 4) == 0) {
      fVar25 = (float10)*(float *)(puVar4 + 8);
    }
    else {
      fVar25 = FUN_0043eac0(*(float *)(puVar4 + 8));
    }
    local_f4 = (float)fVar25;
    uVar10 = *(undefined4 *)(puVar4 + 4);
    local_f0 = local_60;
    local_ec = local_bc;
    if ((*(byte *)(puVar4 + 3) & 1) != 0) {
      uVar27 = FUN_0043ec70(param_3);
      uVar10 = (undefined4)uVar27;
    }
    *(undefined4 *)(param_3 + 0x178) = uVar10;
    *(undefined4 *)(param_3 + 0x14c) = DAT_00491c14;
    *(undefined4 *)(param_3 + 0x150) = DAT_00491c18;
    *(undefined4 *)(param_3 + 0x154) = DAT_00491c1c;
    *(undefined4 *)(param_3 + 0x158) = DAT_00491c14;
    *(undefined4 *)(param_3 + 0x15c) = DAT_00491c18;
    *(undefined4 *)(param_3 + 0x160) = DAT_00491c1c;
    *(undefined4 *)(param_3 + 0x17c) = *(undefined4 *)(puVar4 + 6);
    *(undefined4 *)(param_3 + 0x134) = *(undefined4 *)(param_3 + 0x24);
    *(undefined4 *)(param_3 + 0x138) = *(undefined4 *)(param_3 + 0x28);
    *(undefined4 *)(param_3 + 0x13c) = *(undefined4 *)(param_3 + 0x2c);
    *(float *)(param_3 + 0x140) = local_f4;
    *(float *)(param_3 + 0x144) = local_f0;
    *(float *)(param_3 + 0x148) = local_ec;
    FUN_004050d0();
    *(uint *)(param_3 + 0x35c) = *(uint *)(param_3 + 0x35c) | 4;
    *(uint *)(param_3 + 0x390) = (uint)(ushort)puVar4[1] + (int)puVar4;
    piVar17 = extraout_ECX_34;
    goto LAB_0043eea4;
  case 0x3c:
    if ((*(byte *)(puVar4 + 3) & 8) == 0) {
      local_6c = *(float *)(puVar4 + 10);
    }
    else {
      fVar25 = FUN_0043eac0(*(float *)(puVar4 + 10));
      local_6c = (float)fVar25;
    }
    if ((*(byte *)(puVar4 + 3) & 4) == 0) {
      fVar25 = (float10)*(float *)(puVar4 + 8);
    }
    else {
      fVar25 = FUN_0043eac0(*(float *)(puVar4 + 8));
    }
    local_8 = (float)fVar25;
    local_4 = local_6c;
    if ((*(byte *)(puVar4 + 3) & 1) == 0) {
      uVar10 = *(undefined4 *)(puVar4 + 4);
    }
    else {
      uVar27 = FUN_0043ec70(param_3);
      uVar10 = (undefined4)uVar27;
    }
    FUN_0041ab70(&local_8,(undefined4 *)(param_3 + 0x3c),uVar10,*(byte *)(puVar4 + 6));
    *(uint *)(param_3 + 0x35c) = *(uint *)(param_3 + 0x35c) | 8;
    *(uint *)(param_3 + 0x390) = (uint)(ushort)puVar4[1] + (int)puVar4;
    piVar17 = extraout_ECX_35;
    goto LAB_0043eea4;
  case 0x3d:
    fVar9 = *(float *)(param_3 + 0x3c) * _DAT_00470b60;
    *(uint *)(param_3 + 0x35c) = *(uint *)(param_3 + 0x35c) ^ 0x200 | 8;
    *(float *)(param_3 + 0x3c) = fVar9;
    *(uint *)(param_3 + 0x390) = (uint)(ushort)puVar4[1] + (int)puVar4;
    goto LAB_0043eea4;
  case 0x3e:
    fVar9 = *(float *)(param_3 + 0x40) * _DAT_00470b60;
    *(uint *)(param_3 + 0x35c) = *(uint *)(param_3 + 0x35c) ^ 0x400 | 8;
    *(float *)(param_3 + 0x40) = fVar9;
    *(uint *)(param_3 + 0x390) = (uint)(ushort)puVar4[1] + (int)puVar4;
    goto LAB_0043eea4;
  case 0x3f:
    goto switchD_0043eec4_caseD_3f;
  case 0x41:
    uVar21 = *(uint *)(param_3 + 0x35c) ^
             ((uint)(ushort)puVar4[4] << 0x12 ^ *(uint *)(param_3 + 0x35c)) & 0xc0000;
    *(uint *)(param_3 + 0x35c) = uVar21;
    piVar17 = (int *)(((uint)(ushort)puVar4[5] << 0x14 ^ uVar21) & 0x300000 ^ uVar21);
    *(int **)(param_3 + 0x35c) = piVar17;
    *(uint *)(param_3 + 0x390) = (uint)(ushort)puVar4[1] + (int)puVar4;
    goto LAB_0043eea4;
  case 0x42:
    piVar17 = (int *)(*(uint *)(param_3 + 0x35c) ^
                     (*(int *)(puVar4 + 4) << 4 ^ *(uint *)(param_3 + 0x35c)) & 0x30);
    *(int **)(param_3 + 0x35c) = piVar17;
    *(uint *)(param_3 + 0x390) = (uint)(ushort)puVar4[1] + (int)puVar4;
    goto LAB_0043eea4;
  case 0x43:
    uVar21 = *(uint *)(param_3 + 0x35c) ^
             (*(int *)(puVar4 + 4) << 0x16 ^ *(uint *)(param_3 + 0x35c)) & 0x3c00000;
    *(uint *)(param_3 + 0x35c) = uVar21;
    if ((uVar21 & 0x3c00000) == 0x2800000) {
      FUN_004452f0();
      *(uint *)(param_3 + 0x390) = (uint)(ushort)puVar4[1] + (int)puVar4;
      piVar17 = extraout_ECX_36;
    }
    else {
switchD_0043eec4_caseD_0:
      *(uint *)(param_3 + 0x390) = (uint)(ushort)puVar4[1] + (int)puVar4;
    }
    goto LAB_0043eea4;
  case 0x44:
    *(uint *)(param_3 + 0x20) = (uint)*(byte *)(puVar4 + 4);
    *(uint *)(param_3 + 0x390) = (uint)(ushort)puVar4[1] + (int)puVar4;
    goto LAB_0043eea4;
  case 0x45:
    *(uint *)(param_3 + 0x35c) = *(uint *)(param_3 + 0x35c) & 0xfffffffe;
switchD_0043eec4_caseD_3f:
    sVar8 = *(short *)(param_3 + 0x304);
    if (sVar8 == 0) {
      *(uint *)(param_3 + 0x35c) = *(uint *)(param_3 + 0x35c) | 0x1000;
    }
    else {
LAB_0043f62d:
      psVar20 = (short *)0x0;
      for (psVar23 = *(short **)(param_3 + 0x38c);
          ((sVar3 = *psVar23, sVar3 != 0x40 || ((int)sVar8 != *(int *)(psVar23 + 4))) &&
          (sVar3 != -1)); psVar23 = (short *)((int)psVar23 + (uint)(ushort)psVar23[1])) {
        if ((sVar3 == 0x40) && (*(int *)(psVar23 + 4) == -1)) {
          psVar20 = psVar23;
        }
      }
      *(undefined2 *)(param_3 + 0x304) = 0;
      *(uint *)(param_3 + 0x35c) = *(uint *)(param_3 + 0x35c) & 0xffffefff;
      if ((*psVar23 == 0x40) || (psVar23 = psVar20, psVar20 != (short *)0x0)) {
        *(undefined4 *)(param_3 + 0x368) = *(undefined4 *)(param_3 + 0x5c);
        *(undefined4 *)(param_3 + 0x36c) = *(undefined4 *)(param_3 + 0x60);
        *(undefined4 *)(param_3 + 0x370) = *(undefined4 *)(param_3 + 100);
        *(undefined4 *)(param_3 + 0x374) = *(undefined4 *)(param_3 + 0x68);
        *(undefined4 *)(param_3 + 0x378) = *(undefined4 *)(param_3 + 0x6c);
        *(undefined4 *)(param_3 + 0x37c) = *(undefined4 *)(param_3 + 0x390);
        FUN_00405410((int)psVar23[2]);
        *(uint *)(param_3 + 0x390) = (uint)(ushort)psVar23[1] + (int)psVar23;
        *(uint *)(param_3 + 0x35c) = *(uint *)(param_3 + 0x35c) | 1;
        piVar17 = extraout_ECX_26;
        goto LAB_0043eea4;
      }
    }
    FUN_0044bf40(-1.0);
    piVar17 = extraout_ECX_88;
    iVar19 = extraout_EDX;
    goto LAB_00440e42;
  case 0x46:
    if ((*(byte *)(puVar4 + 3) & 1) == 0) {
      *(undefined4 *)(param_3 + 0x234) = *(undefined4 *)(puVar4 + 4);
      *(uint *)(param_3 + 0x390) = (uint)(ushort)puVar4[1] + (int)puVar4;
    }
    else {
      fVar25 = FUN_0043eac0(*(float *)(puVar4 + 4));
      *(float *)(param_3 + 0x234) = (float)fVar25;
      *(uint *)(param_3 + 0x390) = (uint)(ushort)puVar4[1] + (int)puVar4;
      piVar17 = extraout_ECX_27;
    }
    goto LAB_0043eea4;
  case 0x47:
    if ((*(byte *)(puVar4 + 3) & 1) == 0) {
      *(undefined4 *)(param_3 + 0x238) = *(undefined4 *)(puVar4 + 4);
      *(uint *)(param_3 + 0x390) = (uint)(ushort)puVar4[1] + (int)puVar4;
    }
    else {
      fVar25 = FUN_0043eac0(*(float *)(puVar4 + 4));
      *(float *)(param_3 + 0x238) = (float)fVar25;
      *(uint *)(param_3 + 0x390) = (uint)(ushort)puVar4[1] + (int)puVar4;
      piVar17 = extraout_ECX_28;
    }
    goto LAB_0043eea4;
  case 0x48:
    *(uint *)(param_3 + 0x35c) =
         *(uint *)(param_3 + 0x35c) ^ (*(uint *)(puVar4 + 4) ^ *(uint *)(param_3 + 0x35c)) & 1;
    *(uint *)(param_3 + 0x390) = (uint)(ushort)puVar4[1] + (int)puVar4;
    goto LAB_0043eea4;
  case 0x49:
    piVar17 = (int *)((*(int *)(puVar4 + 4) << 0xb ^ *(uint *)(param_3 + 0x35c)) & 0x800);
    *(uint *)(param_3 + 0x35c) = *(uint *)(param_3 + 0x35c) ^ (uint)piVar17;
    *(uint *)(param_3 + 0x390) = (uint)(ushort)puVar4[1] + (int)puVar4;
    goto LAB_0043eea4;
  case 0x4a:
    *(uint *)(param_3 + 0x35c) =
         *(uint *)(param_3 + 0x35c) ^
         (*(int *)(puVar4 + 4) << 0xd ^ *(uint *)(param_3 + 0x35c)) & 0x2000;
    *(uint *)(param_3 + 0x390) = (uint)(ushort)puVar4[1] + (int)puVar4;
    goto LAB_0043eea4;
  case 0x4b:
    if ((*(byte *)(puVar4 + 3) & 1) != 0) {
      FUN_0043ec70(param_3);
    }
    FUN_00428dd0();
    *(uint *)(param_3 + 0x390) = (uint)(ushort)puVar4[1] + (int)puVar4;
    piVar17 = extraout_ECX_25;
    goto LAB_0043eea4;
  case 0x4c:
    uVar6 = (undefined1)*(undefined4 *)(puVar4 + 4);
    if ((*(byte *)(puVar4 + 3) & 1) != 0) {
      uVar27 = FUN_0043ec70(param_3);
      uVar6 = (undefined1)uVar27;
      piVar17 = extraout_ECX_11;
    }
    *(undefined1 *)(param_3 + 0x302) = uVar6;
    uVar6 = (undefined1)*(undefined4 *)(puVar4 + 6);
    if ((*(byte *)(puVar4 + 3) & 2) != 0) {
      uVar27 = FUN_0043ec70(param_3);
      uVar6 = (undefined1)uVar27;
      piVar17 = extraout_ECX_12;
    }
    *(undefined1 *)(param_3 + 0x301) = uVar6;
    uVar6 = (undefined1)*(undefined4 *)(puVar4 + 8);
    if ((*(byte *)(puVar4 + 3) & 4) != 0) {
      uVar27 = FUN_0043ec70(param_3);
      uVar6 = (undefined1)uVar27;
      piVar17 = extraout_ECX_13;
    }
    *(undefined1 *)(param_3 + 0x300) = uVar6;
    *(uint *)(param_3 + 0x390) = (uint)(ushort)puVar4[1] + (int)puVar4;
    goto LAB_0043eea4;
  case 0x4d:
    uVar6 = (undefined1)*(undefined4 *)(puVar4 + 4);
    if ((*(byte *)(puVar4 + 3) & 1) != 0) {
      uVar27 = FUN_0043ec70(param_3);
      uVar6 = (undefined1)uVar27;
      piVar17 = extraout_ECX_10;
    }
    *(undefined1 *)(param_3 + 0x303) = uVar6;
    *(uint *)(param_3 + 0x390) = (uint)(ushort)puVar4[1] + (int)puVar4;
    goto LAB_0043eea4;
  case 0x4e:
    local_dc = *(byte *)(param_3 + 0x300);
    local_db = *(undefined1 *)(param_3 + 0x301);
    local_da = *(undefined1 *)(param_3 + 0x302);
    uVar27 = (ulonglong)*(uint *)(puVar4 + 0xc);
    if ((*(byte *)(puVar4 + 3) & 0x10) != 0) {
      uVar27 = FUN_0043ec70(param_3);
    }
    local_f8 = (float)uVar27;
    if ((*(byte *)(puVar4 + 3) & 8) == 0) {
      local_e8 = *(undefined4 *)(puVar4 + 10);
    }
    else {
      uVar27 = FUN_0043ec70(param_3);
      local_e8 = (undefined4)uVar27;
    }
    uVar6 = (char)*(undefined4 *)(puVar4 + 8);
    if ((*(byte *)(puVar4 + 3) & 4) != 0) {
      uVar27 = FUN_0043ec70(param_3);
      uVar6 = (char)uVar27;
    }
    local_d2 = uVar6;
    uVar27 = (ulonglong)*(uint *)(puVar4 + 4);
    local_d4 = local_f8._0_1_;
    local_d3 = (undefined1)local_e8;
    if ((*(byte *)(puVar4 + 3) & 1) != 0) {
      uVar27 = FUN_0043ec70(param_3);
    }
    FUN_00442050(&local_d4,&local_dc,(int)uVar27,*(byte *)(puVar4 + 6));
    *(uint *)(param_3 + 0x390) = (uint)(ushort)puVar4[1] + (int)puVar4;
    piVar17 = extraout_ECX_32;
    goto LAB_0043eea4;
  case 0x4f:
    if ((*(byte *)(puVar4 + 3) & 4) == 0) {
      uVar27 = CONCAT44(iVar19,*(undefined4 *)(puVar4 + 8));
    }
    else {
      uVar27 = FUN_0043ec70(param_3);
    }
    uVar26 = CONCAT44((int)(uVar27 >> 0x20),*(undefined4 *)(puVar4 + 4));
    if ((*(byte *)(puVar4 + 3) & 1) != 0) {
      uVar26 = FUN_0043ec70(param_3);
    }
    FUN_00441f50((int)uVar26,CONCAT31((int3)(uVar26 >> 0x28),*(undefined1 *)(puVar4 + 6)),
                 *(byte *)(param_3 + 0x303),(byte)uVar27);
    *(uint *)(param_3 + 0x390) = (uint)(ushort)puVar4[1] + (int)puVar4;
    piVar17 = extraout_ECX_33;
    goto LAB_0043eea4;
  case 0x50:
    piVar17 = (int *)(*(uint *)(param_3 + 0x35c) ^
                     ((uint)*(byte *)(puVar4 + 4) << 0xf ^ *(uint *)(param_3 + 0x35c)) & 0x8000);
    *(int **)(param_3 + 0x35c) = piVar17;
    *(uint *)(param_3 + 0x390) = (uint)(ushort)puVar4[1] + (int)puVar4;
    goto LAB_0043eea4;
  case 0x51:
    *(undefined4 *)(param_3 + 0x5c) = *(undefined4 *)(param_3 + 0x368);
    *(undefined4 *)(param_3 + 0x60) = *(undefined4 *)(param_3 + 0x36c);
    *(undefined4 *)(param_3 + 100) = *(undefined4 *)(param_3 + 0x370);
    *(undefined4 *)(param_3 + 0x68) = *(undefined4 *)(param_3 + 0x374);
    *(undefined4 *)(param_3 + 0x6c) = *(undefined4 *)(param_3 + 0x378);
    *(int **)(param_3 + 0x390) = *(int **)(param_3 + 0x37c);
    piVar17 = *(int **)(param_3 + 0x37c);
    goto LAB_0043eea4;
  case 0x52:
    piVar17 = (int *)(((uint)*(byte *)(puVar4 + 4) << 0x1b ^ *(uint *)(param_3 + 0x35c)) & 0x8000000
                     );
    *(uint *)(param_3 + 0x35c) = *(uint *)(param_3 + 0x35c) ^ (uint)piVar17;
    *(uint *)(param_3 + 0x390) = (uint)(ushort)puVar4[1] + (int)puVar4;
    goto LAB_0043eea4;
  case 0x53:
    *(undefined4 *)(param_3 + 0x334) = *(undefined4 *)(param_3 + 0x340);
    *(undefined4 *)(param_3 + 0x338) = *(undefined4 *)(param_3 + 0x344);
    *(undefined4 *)(param_3 + 0x33c) = *(undefined4 *)(param_3 + 0x348);
    *(undefined4 *)(param_3 + 0x340) = 0;
    *(undefined4 *)(param_3 + 0x344) = 0;
    *(undefined4 *)(param_3 + 0x348) = 0;
    *(uint *)(param_3 + 0x390) = (uint)(ushort)puVar4[1] + (int)puVar4;
    piVar17 = (int *)0x0;
    goto LAB_0043eea4;
  case 0x54:
    *(uint *)(param_3 + 0x35c) = *(uint *)(param_3 + 0x35c) & 0xfe7fffff | 0x2400000;
    iVar19 = *(int *)(puVar4 + 4);
    if ((*(byte *)(puVar4 + 3) & 1) != 0) {
      uVar27 = FUN_0043ec70(param_3);
      iVar19 = (int)uVar27;
    }
    pvVar11 = _malloc(iVar19 * 0x38);
    *(void **)(param_3 + 0x358) = pvVar11;
    *(uint *)(param_3 + 0x390) = (uint)(ushort)puVar4[1] + (int)puVar4;
    piVar17 = extraout_ECX_37;
    goto LAB_0043eea4;
  case 0x55:
    piVar17 = (int *)(((uint)*(byte *)(puVar4 + 4) << 0x1c ^ *(uint *)(param_3 + 0x35c)) &
                     0x10000000);
    *(uint *)(param_3 + 0x35c) = *(uint *)(param_3 + 0x35c) ^ (uint)piVar17;
    *(uint *)(param_3 + 0x390) = (uint)(ushort)puVar4[1] + (int)puVar4;
    goto LAB_0043eea4;
  case 0x56:
    iVar19 = *(int *)(puVar4 + 4);
    if ((*(byte *)(puVar4 + 3) & 1) != 0) {
      uVar27 = FUN_0043ec70(param_3);
      iVar19 = (int)uVar27;
    }
    piVar17 = (int *)(*(uint *)(param_3 + 0x35c) ^
                     (iVar19 << 0x1d ^ *(uint *)(param_3 + 0x35c)) & 0x20000000);
    *(int **)(param_3 + 0x35c) = piVar17;
    *(uint *)(param_3 + 0x390) = (uint)(ushort)puVar4[1] + (int)puVar4;
    goto LAB_0043eea4;
  case 0x57:
    *(uint *)(param_3 + 0x35c) =
         *(uint *)(param_3 + 0x35c) ^
         ((uint)*(byte *)(puVar4 + 4) << 0x1e ^ *(uint *)(param_3 + 0x35c)) & 0x40000000;
    *(uint *)(param_3 + 0x390) = (uint)(ushort)puVar4[1] + (int)puVar4;
    goto LAB_0043eea4;
  case 0x58:
    iVar19 = *(int *)(puVar4 + 4);
    if ((*(byte *)(puVar4 + 3) & 1) != 0) {
      uVar27 = FUN_0043ec70(param_3);
      iVar19 = (int)uVar27;
    }
    FUN_00448d00(*(undefined4 *)(param_3 + 0x308),iVar19,*(undefined4 *)(param_3 + 0x20));
    uVar10 = extraout_ECX;
    goto LAB_0043ef88;
  case 0x59:
    piVar17 = (int *)((uint)*(float *)(param_3 + 0x35c) & 0x7fffffff);
    *(uint *)(param_3 + 0x35c) = *(int *)(puVar4 + 4) << 0x1f | (uint)piVar17;
    *(uint *)(param_3 + 0x390) = (uint)(ushort)puVar4[1] + (int)puVar4;
    goto LAB_0043eea4;
  case 0x5a:
    iVar19 = *(int *)(puVar4 + 4);
    if ((*(byte *)(puVar4 + 3) & 1) != 0) {
      uVar27 = FUN_0043ec70(param_3);
      iVar19 = (int)uVar27;
    }
    FUN_00448f60(*(undefined4 *)(param_3 + 0x308),iVar19,*(undefined4 *)(param_3 + 0x20));
    uVar10 = extraout_ECX_01;
LAB_0043ef88:
    iVar19 = FUN_00449450(uVar10);
    FUN_00413200(param_3 + 0x10);
    *(undefined4 *)(iVar19 + 0x34c) = *(undefined4 *)(param_3 + 0x334);
    *(undefined4 *)(iVar19 + 0x350) = *(undefined4 *)(param_3 + 0x338);
    *(undefined4 *)(iVar19 + 0x354) = *(undefined4 *)(param_3 + 0x33c);
    *(undefined4 *)(iVar19 + 0x340) = *(undefined4 *)(param_3 + 0x340);
    *(undefined4 *)(iVar19 + 0x344) = *(undefined4 *)(param_3 + 0x344);
    piVar17 = *(int **)(param_3 + 0x348);
    *(int **)(iVar19 + 0x348) = piVar17;
    *(uint *)(param_3 + 0x390) = (uint)(ushort)puVar4[1] + (int)puVar4;
    goto LAB_0043eea4;
  case 0x5b:
    iVar19 = *(int *)(puVar4 + 4);
    if ((*(byte *)(puVar4 + 3) & 1) != 0) {
      uVar27 = FUN_0043ec70(param_3);
      iVar19 = (int)uVar27;
    }
    FUN_00448e30(*(undefined4 *)(param_3 + 0x308),iVar19,*(undefined4 *)(param_3 + 0x20));
    uVar10 = extraout_ECX_00;
    goto LAB_0043f00d;
  case 0x5c:
    iVar19 = *(int *)(puVar4 + 4);
    if ((*(byte *)(puVar4 + 3) & 1) != 0) {
      uVar27 = FUN_0043ec70(param_3);
      iVar19 = (int)uVar27;
    }
    FUN_00449090(*(undefined4 *)(param_3 + 0x308),iVar19,*(undefined4 *)(param_3 + 0x20));
    uVar10 = extraout_ECX_02;
LAB_0043f00d:
    iVar19 = FUN_00449450(uVar10);
    FUN_00413200(param_3 + 0x10);
    *(undefined4 *)(iVar19 + 0x34c) = *(undefined4 *)(param_3 + 0x334);
    *(undefined4 *)(iVar19 + 0x350) = *(undefined4 *)(param_3 + 0x338);
    *(undefined4 *)(iVar19 + 0x354) = *(undefined4 *)(param_3 + 0x33c);
    *(undefined4 *)(iVar19 + 0x340) = *(undefined4 *)(param_3 + 0x340);
    piVar17 = *(int **)(param_3 + 0x344);
    *(int **)(iVar19 + 0x344) = piVar17;
    *(undefined4 *)(iVar19 + 0x348) = *(undefined4 *)(param_3 + 0x348);
    *(uint *)(param_3 + 0x390) = (uint)(ushort)puVar4[1] + (int)puVar4;
    goto LAB_0043eea4;
  case 0xffff:
  case 1:
    *(uint *)(param_3 + 0x35c) = *(uint *)(param_3 + 0x35c) & 0xfffffffe;
  case 2:
    *(undefined4 *)(param_3 + 0x390) = 0;
    DAT_00476f78 = local_68;
    return CONCAT44(iVar19,1);
  }
  FUN_00405410(*(int *)(puVar4 + 10));
  piVar17 = (int *)(*(int *)(param_3 + 0x38c) + *(int *)(puVar4 + 8));
  *(int **)(param_3 + 0x390) = piVar17;
  goto LAB_0043eea4;
}

