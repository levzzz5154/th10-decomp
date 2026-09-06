/* Raw Ghidra reference; not compilable reconstruction. Address: 0043C550 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 __fastcall FUN_0043c550(int param_1,int param_2)

{
  float *pfVar1;
  float fVar2;
  float fVar3;
  ushort uVar4;
  short sVar5;
  uint uVar6;
  int iVar7;
  ulonglong uVar8;
  
  if (DAT_004918a4 == 0) {
    pfVar1 = *(float **)(param_1 + 0x3c);
    *(int *)(param_1 + 0x30) = *(int *)(param_1 + 0x34);
    if ((*pfVar1 <= _DAT_00470b68) || (_DAT_00470b64 <= *pfVar1)) {
      *(float *)(param_1 + 0x38) = *(float *)(param_1 + 0x38) + *pfVar1;
      uVar8 = FUN_00463b2c();
      param_2 = (int)(uVar8 >> 0x20);
      *(int *)(param_1 + 0x34) = (int)uVar8;
    }
    else {
      param_2 = *(int *)(param_1 + 0x34) + 1;
      fVar2 = *(float *)(param_1 + 0x38) + _DAT_00470afc;
      *(int *)(param_1 + 0x34) = param_2;
      *(float *)(param_1 + 0x38) = fVar2;
    }
    if (*(int *)(param_1 + 0x34) < *(int *)(param_1 + 0x1c)) {
      uVar4 = ((ushort)_DAT_004918b0 ^ 0x9630) + 0x9aad;
      uVar4 = ((uVar4 >> 0xe) + uVar4 * 4 ^ 0x9630) + 0x9aad;
      uVar4 = (uVar4 >> 0xe) + uVar4 * 4;
      uVar6 = CONCAT22(uVar4,uVar4) % 3;
      fVar2 = ((float)(*(int *)(param_1 + 0x24) - *(int *)(param_1 + 0x20)) *
              *(float *)(param_1 + 0x38)) / (float)*(int *)(param_1 + 0x1c) +
              (float)*(int *)(param_1 + 0x20);
      if (uVar6 == 0) {
        DAT_00491e64 = 0.0;
        fVar3 = DAT_00491e64;
      }
      else {
        fVar3 = fVar2;
        if ((uVar6 != 1) && (fVar3 = DAT_00491e64, uVar6 == 2)) {
          fVar3 = -fVar2;
        }
      }
      DAT_00491e64 = fVar3;
      uVar4 = (uVar4 ^ 0x9630) + 0x9aad;
      uVar4 = ((uVar4 >> 0xe) + uVar4 * 4 ^ 0x9630) + 0x9aad;
      sVar5 = (uVar4 >> 0xe) + uVar4 * 4;
      _DAT_004918b0 = CONCAT22(DAT_004918b0_2,sVar5);
      uVar6 = CONCAT22(sVar5,sVar5) % 3;
      DAT_004918b4 = DAT_004918b4 + 4;
      if (uVar6 == 0) {
        DAT_00491e68 = 0.0;
        iVar7 = 0;
LAB_0043c6fb:
        return CONCAT44(iVar7,1);
      }
      if (uVar6 != 1) {
        iVar7 = uVar6 - 2;
        if (iVar7 != 0) goto LAB_0043c6fb;
        fVar2 = -fVar2;
      }
      DAT_00491e68 = fVar2;
      return 1;
    }
  }
  return CONCAT44(param_2,7);
}

