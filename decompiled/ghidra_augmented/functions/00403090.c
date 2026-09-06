/* Raw Ghidra reference; not compilable reconstruction. Address: 00403090 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __fastcall FUN_00403090(int param_1,float *param_2,float param_3)

{
  float fVar1;
  float fVar2;
  float *pfVar3;
  float *in_EAX;
  float *unaff_ESI;
  float fVar4;
  float *pfVar5;
  float *pfVar6;
  float *pfVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float *local_120;
  float local_11c;
  float local_118;
  float *local_114;
  float fStack_110;
  float fStack_10c;
  float *pfStack_108;
  float fStack_104;
  float fStack_100;
  float *pfStack_fc;
  float fStack_f8;
  float fStack_f4;
  float *pfStack_f0;
  float fStack_ec;
  float fStack_e8;
  float local_b0;
  float local_ac;
  float *local_a8;
  float local_a4;
  float local_a0;
  float local_9c;
  float local_98;
  float local_94;
  float local_90;
  float local_8c;
  float local_88;
  float local_84;
  float local_80;
  float local_7c;
  float local_78;
  float local_74;
  float *local_70;
  float local_6c;
  float local_68;
  float *local_64;
  float local_60;
  float local_5c;
  float *local_58;
  float local_54;
  float local_50;
  float *local_4c;
  float local_48;
  float local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  fVar10 = (*(float *)(param_1 + 4) + *param_2) - (in_EAX[0xf] + *in_EAX);
  fVar11 = (*(float *)(param_1 + 8) + param_2[1]) - (in_EAX[0x10] + in_EAX[1]);
  fVar1 = (*(float *)(param_1 + 0xc) + param_2[2]) - (in_EAX[0x11] + in_EAX[2]);
  if (fVar10 * fVar10 + fVar11 * fVar11 + fVar1 * fVar1 <= param_3) {
    local_8 = 0;
    local_11c = *(float *)(param_1 + 0x10) * _DAT_00470b0c;
    local_c = 0;
    local_10 = 0;
    local_14 = 0;
    local_118 = *(float *)(param_1 + 0x14) * _DAT_00470b0c;
    local_1c = 0;
    local_20 = 0;
    local_24 = 0;
    local_114 = (float *)(*(float *)(param_1 + 0x18) * _DAT_00470b0c);
    local_28 = 0;
    local_30 = 0;
    local_a0 = local_11c + *(float *)(param_1 + 4);
    local_9c = local_118 + *(float *)(param_1 + 8);
    local_a4 = (float)local_114 + *(float *)(param_1 + 0xc);
    fVar1 = *(float *)(param_1 + 0xc) - (float)local_114;
    fVar2 = *(float *)(param_1 + 8) - local_118;
    local_120 = (float *)(*(float *)(param_1 + 4) - local_11c);
    fVar10 = param_2[2];
    fVar11 = param_2[1];
    pfVar6 = (float *)*param_2;
    local_34 = 0;
    local_38 = 0;
    local_3c = 0;
    local_4 = 0x3f800000;
    local_18 = 0x3f800000;
    local_2c = 0x3f800000;
    local_40 = 0x3f800000;
    local_b0 = local_11c;
    local_ac = local_118;
    local_a8 = local_114;
    local_98 = local_a4;
    local_94 = local_a0;
    local_90 = local_9c;
    local_8c = fVar1;
    local_88 = local_a0;
    local_84 = fVar2;
    local_80 = local_a4;
    local_7c = local_a0;
    local_78 = fVar2;
    local_74 = fVar1;
    local_70 = local_120;
    local_6c = local_9c;
    local_68 = local_a4;
    local_64 = local_120;
    local_60 = local_9c;
    local_5c = fVar1;
    local_58 = local_120;
    local_54 = fVar2;
    local_50 = local_a4;
    local_4c = local_120;
    local_48 = fVar2;
    local_44 = fVar1;
    D3DXMatrixTranslation();
    D3DXVec3ProjectArray(&local_120,0xc,&local_b0,0xc,in_EAX + 0x33,in_EAX + 0x23,in_EAX + 0x13);
    pfVar5 = (float *)0x43d40000;
    fVar8 = 472.0;
    fVar4 = 8.0;
    pfVar7 = pfVar5;
    pfVar3 = _DAT_00470be8;
    if ((_DAT_00470b04 <= (float)&local_40) && ((float)&local_40 < _DAT_00470afc)) {
      pfVar7 = &local_50;
      if ((_DAT_00470be4 <= (float)&local_50) &&
         (pfVar7 = pfVar5, (float)_DAT_00470be8 < (float)&local_50)) {
        pfVar3 = &local_50;
      }
      if (_DAT_00470be0 <= 1.12104e-44) {
        if (_DAT_00470bd0 <= 1.12104e-44) {
          fVar4 = 1.12104e-44;
        }
      }
      else {
        fVar8 = 1.12104e-44;
      }
    }
    pfVar5 = pfVar7;
    fVar9 = fVar8;
    if ((_DAT_00470b04 <= fVar10) && (fVar10 < _DAT_00470afc)) {
      pfVar5 = pfVar6;
      if (((float)pfVar7 <= (float)pfVar6) && (pfVar5 = pfVar7, (float)pfVar3 < (float)pfVar6)) {
        pfVar3 = pfVar6;
      }
      fVar9 = fVar11;
      if ((fVar8 <= fVar11) && (fVar9 = fVar8, fVar4 <= fVar11)) {
        fVar4 = fVar11;
      }
    }
    pfVar6 = pfVar5;
    fVar10 = fVar9;
    if ((_DAT_00470b04 <= fVar1) && (fVar1 < _DAT_00470afc)) {
      pfVar6 = unaff_ESI;
      if (((float)pfVar5 <= (float)unaff_ESI) && (pfVar6 = pfVar5, (float)pfVar3 < (float)unaff_ESI)
         ) {
        pfVar3 = unaff_ESI;
      }
      fVar10 = fVar2;
      if ((fVar9 <= fVar2) && (fVar10 = fVar9, fVar4 <= fVar2)) {
        fVar4 = fVar2;
      }
    }
    pfVar7 = pfVar6;
    fVar11 = fVar10;
    if ((_DAT_00470b04 <= local_118) && (local_118 < _DAT_00470afc)) {
      pfVar7 = local_120;
      if (((float)pfVar6 <= (float)local_120) && (pfVar7 = pfVar6, (float)pfVar3 < (float)local_120)
         ) {
        pfVar3 = local_120;
      }
      fVar11 = local_11c;
      if ((fVar10 <= local_11c) && (fVar11 = fVar10, fVar4 <= local_11c)) {
        fVar4 = local_11c;
      }
    }
    pfVar6 = pfVar7;
    fVar10 = fVar11;
    if ((_DAT_00470b04 <= fStack_10c) && (fStack_10c < _DAT_00470afc)) {
      pfVar6 = local_114;
      if (((float)pfVar7 <= (float)local_114) && (pfVar6 = pfVar7, (float)pfVar3 < (float)local_114)
         ) {
        pfVar3 = local_114;
      }
      fVar10 = fStack_110;
      if ((fVar11 <= fStack_110) && (fVar10 = fVar11, fVar4 <= fStack_110)) {
        fVar4 = fStack_110;
      }
    }
    pfVar7 = pfVar6;
    fVar11 = fVar10;
    if ((_DAT_00470b04 <= fStack_100) && (fStack_100 < _DAT_00470afc)) {
      pfVar7 = pfStack_108;
      if (((float)pfVar6 <= (float)pfStack_108) &&
         (pfVar7 = pfVar6, (float)pfVar3 < (float)pfStack_108)) {
        pfVar3 = pfStack_108;
      }
      fVar11 = fStack_104;
      if ((fVar10 <= fStack_104) && (fVar11 = fVar10, fVar4 <= fStack_104)) {
        fVar4 = fStack_104;
      }
    }
    pfVar6 = pfVar7;
    fVar10 = fVar11;
    if ((_DAT_00470b04 <= fStack_f4) && (fStack_f4 < _DAT_00470afc)) {
      pfVar6 = pfStack_fc;
      if (((float)pfVar7 <= (float)pfStack_fc) &&
         (pfVar6 = pfVar7, (float)pfVar3 < (float)pfStack_fc)) {
        pfVar3 = pfStack_fc;
      }
      fVar10 = fStack_f8;
      if ((fVar11 <= fStack_f8) && (fVar10 = fVar11, fVar4 <= fStack_f8)) {
        fVar4 = fStack_f8;
      }
    }
    pfVar7 = pfVar6;
    fVar11 = fVar10;
    if ((_DAT_00470b04 <= fStack_e8) && (fStack_e8 < _DAT_00470afc)) {
      pfVar7 = pfStack_f0;
      if (((float)pfVar6 <= (float)pfStack_f0) &&
         (pfVar7 = pfVar6, (float)pfVar3 < (float)pfStack_f0)) {
        pfVar3 = pfStack_f0;
      }
      fVar11 = fStack_ec;
      if ((fVar10 <= fStack_ec) && (fVar11 = fVar10, fVar4 <= fStack_ec)) {
        fVar4 = fStack_ec;
      }
    }
    if ((((_DAT_00470bcc <= (float)pfVar3) &&
         ((float)pfVar7 < _DAT_00470bdc != ((float)pfVar7 == _DAT_00470bdc))) &&
        (_DAT_00470b48 <= fVar4)) && (fVar11 < _DAT_00470bd8 != (fVar11 == _DAT_00470bd8))) {
      return 0;
    }
  }
  return 1;
}

