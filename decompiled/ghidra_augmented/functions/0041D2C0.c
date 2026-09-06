/* Raw Ghidra reference; not compilable reconstruction. Address: 0041D2C0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_0041d2c0(int param_1)

{
  float *pfVar1;
  float fVar2;
  float fVar3;
  float10 fVar4;
  ulonglong uVar5;
  
  if (*(int *)(param_1 + 0x90) < *(int *)(param_1 + 0xb4)) {
    *(float *)(param_1 + 0x48) =
         DAT_00476f78 * *(float *)(param_1 + 0xa0) + *(float *)(param_1 + 0x48);
    fVar2 = DAT_00476f78 * *(float *)(param_1 + 0xac);
    fVar3 = DAT_00476f78 * *(float *)(param_1 + 0xb0);
    *(float *)(param_1 + 0x30) =
         DAT_00476f78 * *(float *)(param_1 + 0xa8) + *(float *)(param_1 + 0x30);
    *(float *)(param_1 + 0x34) = fVar2 + *(float *)(param_1 + 0x34);
    *(float *)(param_1 + 0x38) = fVar3 + *(float *)(param_1 + 0x38);
    if ((_DAT_00470c58 < ABS(*(float *)(param_1 + 0x30))) ||
       (_DAT_00470c58 < ABS(*(float *)(param_1 + 0x34)))) {
      fVar4 = (float10)fpatan((float10)*(float *)(param_1 + 0x34),
                              (float10)*(float *)(param_1 + 0x30));
      *(float *)(param_1 + 0x3c) = (float)fVar4;
    }
  }
  else {
    *(uint *)(param_1 + 0x404) = *(uint *)(param_1 + 0x404) & 0xffffffef;
  }
  pfVar1 = *(float **)(param_1 + 0x98);
  *(int *)(param_1 + 0x8c) = *(int *)(param_1 + 0x90);
  if ((_DAT_00470b68 < *pfVar1) && (*pfVar1 < _DAT_00470b64)) {
    fVar2 = *(float *)(param_1 + 0x94) + _DAT_00470afc;
    *(int *)(param_1 + 0x90) = *(int *)(param_1 + 0x90) + 1;
    *(float *)(param_1 + 0x94) = fVar2;
    return;
  }
  *(float *)(param_1 + 0x94) = *(float *)(param_1 + 0x94) + *pfVar1;
  uVar5 = FUN_00463b2c();
  *(int *)(param_1 + 0x90) = (int)uVar5;
  return;
}

