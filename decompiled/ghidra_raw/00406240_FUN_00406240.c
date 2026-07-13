/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00406240
 * Tracking name: FUN_00406240
 * Ghidra name: FUN_00406240
 * Tracked span: 896 bytes
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __fastcall FUN_00406240(uint param_1,uint param_2,uint *param_3)

{
  float *pfVar1;
  short sVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  int iVar6;
  uint extraout_ECX;
  uint extraout_ECX_00;
  uint extraout_ECX_01;
  uint extraout_ECX_02;
  uint extraout_ECX_03;
  uint extraout_ECX_04;
  uint extraout_ECX_05;
  uint extraout_ECX_06;
  uint extraout_ECX_07;
  uint extraout_ECX_08;
  uint extraout_ECX_09;
  uint extraout_ECX_10;
  uint extraout_ECX_11;
  uint extraout_ECX_12;
  uint extraout_ECX_13;
  uint extraout_ECX_14;
  uint extraout_EDX;
  uint extraout_EDX_00;
  uint extraout_EDX_01;
  uint extraout_EDX_02;
  uint extraout_EDX_03;
  uint extraout_EDX_04;
  uint extraout_EDX_05;
  uint extraout_EDX_06;
  uint extraout_EDX_07;
  uint extraout_EDX_08;
  uint extraout_EDX_09;
  uint extraout_EDX_10;
  uint extraout_EDX_11;
  uint extraout_EDX_12;
  uint extraout_EDX_13;
  uint extraout_EDX_14;
  ulonglong uVar7;
  
  if ((*param_3 & 8) != 0) {
    FUN_00405be0();
    return 0xffffffff;
  }
  sVar2 = *(short *)((int)param_3 + 0x446);
  if (sVar2 == 1) {
LAB_00406373:
    FUN_00406d90((int)param_3);
    param_1 = extraout_ECX;
    param_2 = extraout_EDX;
    if (param_3[0x10f] != 0) {
      if ((param_3[0x10f] & 1) != 0) {
        FUN_004074b0();
        param_1 = extraout_ECX_00;
        param_2 = extraout_EDX_00;
      }
      if ((param_3[0x10f] & 0x10) != 0) {
        FUN_00407560();
        param_1 = extraout_ECX_01;
        param_2 = extraout_EDX_01;
      }
      if ((param_3[0x10f] & 0x20) != 0) {
        FUN_004076a0();
        param_1 = extraout_ECX_02;
        param_2 = extraout_EDX_02;
      }
      if ((param_3[0x10f] & 0x40) != 0) {
        FUN_00407780();
        param_1 = extraout_ECX_03;
        param_2 = extraout_EDX_03;
      }
      if ((param_3[0x10f] & 0x100) != 0) {
        FUN_004078e0();
        param_1 = extraout_ECX_04;
        param_2 = extraout_EDX_04;
      }
      if ((char)param_3[0x10f] < '\0') {
        FUN_00407a30();
        param_1 = extraout_ECX_05;
        param_2 = extraout_EDX_05;
      }
      if ((param_3[0x10f] & 0x8000c00) != 0) {
        FUN_00407be0();
        param_1 = extraout_ECX_06;
        param_2 = extraout_EDX_06;
      }
      if ((param_3[0x10f] & 0x4000000) != 0) {
        FUN_00407ef0();
        param_1 = extraout_ECX_07;
        param_2 = extraout_EDX_07;
      }
      if ((char)(param_3[0x10f] >> 8) < '\0') {
        param_1 = param_3[0x1c7];
        if ((int)param_1 < 1) {
          param_3[0x10f] = param_3[0x10f] ^ 0x8000;
        }
        else {
          FUN_0044bf40(-1.0);
          param_1 = extraout_ECX_08;
          param_2 = extraout_EDX_08;
        }
      }
    }
    pfVar1 = (float *)(param_3 + 0xed);
    fVar3 = DAT_00476f78 * (float)param_3[0xf1];
    fVar4 = DAT_00476f78 * (float)param_3[0xf2];
    *pfVar1 = DAT_00476f78 * (float)param_3[0xf0] + *pfVar1;
    param_3[0xee] = (uint)(fVar3 + (float)param_3[0xee]);
    param_3[0xef] = (uint)(fVar4 + (float)param_3[0xef]);
    if ((*param_3 & 2) != 0) {
      iVar5 = FUN_004266b0(pfVar1,DAT_00477834);
      iVar6 = DAT_004776f0;
      param_1 = extraout_ECX_09;
      param_2 = extraout_EDX_09;
      if (iVar5 == 1) {
        *(undefined2 *)((int)param_3 + 0x446) = 3;
        *(undefined2 *)(param_3 + 0xc3) = 1;
        if (-1 < (int)param_3[0x10e]) {
          FUN_00448db0(*(undefined2 **)(DAT_004776f0 + 0x3e0b50));
          param_1 = extraout_ECX_10;
          param_2 = extraout_EDX_10;
        }
      }
      else if ((iVar5 == 2) && ((*param_3 & 4) == 0)) {
        *param_3 = *param_3 | 4;
        FUN_00448db0(*(undefined2 **)(iVar6 + 0x3e0b50));
        FUN_0043dd10();
        param_1 = extraout_ECX_11;
        param_2 = extraout_EDX_11;
      }
    }
  }
  else if (sVar2 == 2) {
    fVar3 = DAT_00476f78 * (float)param_3[0xf1] * _DAT_00470b0c;
    fVar4 = DAT_00476f78 * (float)param_3[0xf2] * _DAT_00470b0c;
    param_3[0xed] =
         (uint)(DAT_00476f78 * (float)param_3[0xf0] * _DAT_00470b0c + (float)param_3[0xed]);
    param_3[0xee] = (uint)(fVar3 + (float)param_3[0xee]);
    param_3[0xef] = (uint)(fVar4 + (float)param_3[0xef]);
    if (param_3[0xc5] != 0) {
      *(undefined2 *)((int)param_3 + 0x446) = 1;
      goto LAB_00406373;
    }
  }
  else if (sVar2 == 3) {
    fVar3 = DAT_00476f78 * (float)param_3[0xf1] * _DAT_00470b0c;
    fVar4 = DAT_00476f78 * (float)param_3[0xf2] * _DAT_00470b0c;
    param_3[0xed] =
         (uint)(DAT_00476f78 * (float)param_3[0xf0] * _DAT_00470b0c + (float)param_3[0xed]);
    param_3[0xee] = (uint)(fVar3 + (float)param_3[0xee]);
    param_3[0xef] = (uint)(fVar4 + (float)param_3[0xef]);
  }
  if (param_3[0xe7] != 0) {
    if ((param_3[0x10f] & 0x100000) != 0) {
      FUN_00407da0();
      param_1 = extraout_ECX_12;
      param_2 = extraout_EDX_12;
    }
    if ((param_3[0x10f] & 0x200000) != 0) {
      FUN_00407e40();
      param_1 = extraout_ECX_13;
      param_2 = extraout_EDX_13;
    }
    if (((int)param_3[0x10d] < 1) &&
       (iVar6 = FUN_00406160(param_3 + 0xed,*(float *)(param_3[0xe7] + 0x34),
                             *(float *)(param_3[0xe7] + 0x30)), param_1 = extraout_ECX_14,
       param_2 = extraout_EDX_14, iVar6 != 0)) goto LAB_00406572;
  }
  if (param_3[1] != 0) {
    param_3[1] = param_3[1] - 1;
  }
  if (0 < (int)param_3[0x10d]) {
    param_3[0x10d] = param_3[0x10d] - 1;
  }
  uVar7 = FUN_0043ee30(param_1,param_2,(int)(param_3 + 2));
  if ((int)uVar7 == 0) {
    return 0;
  }
LAB_00406572:
  FUN_00405be0();
  return 0xffffffff;
}

