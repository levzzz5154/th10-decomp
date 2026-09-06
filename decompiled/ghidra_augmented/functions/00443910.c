/* Raw Ghidra reference; not compilable reconstruction. Address: 00443910 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_00443910(void *param_1,int param_2)

{
  float fVar1;
  float fVar2;
  float10 fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  uint uVar8;
  float10 fVar9;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  float local_4;
  
  if (*(float *)(param_2 + 0x2c) != _DAT_00470b04) {
    fVar3 = (float10)fcos((float10)*(float *)(param_2 + 0x2c));
    fVar9 = (float10)fsin((float10)*(float *)(param_2 + 0x2c));
    fVar1 = (float)fVar3;
    fVar2 = (float)fVar9;
    fVar5 = *(float *)(param_2 + 0x34c) + *(float *)(param_2 + 0x340) + *(float *)(param_2 + 0x334);
    uVar8 = *(uint *)(param_2 + 0x35c) >> 0x12 & 3;
    fVar6 = *(float *)(param_2 + 0x350) + *(float *)(param_2 + 0x344) + *(float *)(param_2 + 0x338);
    fVar7 = *(float *)(param_2 + 0x4c) * *(float *)(param_2 + 0x3c);
    fVar4 = *(float *)(param_2 + 0x50) * *(float *)(param_2 + 0x40);
    if (uVar8 == 0) {
      local_10 = _DAT_00470b78 * fVar7;
      local_4 = fVar7 * _DAT_00470b0c;
      local_8 = local_10;
      local_c = local_4;
    }
    else if (uVar8 == 1) {
      local_8 = 0.0;
      local_10 = 0.0;
      local_4 = fVar7;
      local_c = fVar7;
    }
    else if (uVar8 == 2) {
      local_10 = -fVar7;
      local_4 = 0.0;
      local_8 = local_10;
      local_c = _DAT_00470b04;
    }
    uVar8 = *(uint *)(param_2 + 0x35c) >> 0x14 & 3;
    if (uVar8 == 0) {
      local_20 = fVar4 * _DAT_00470b78;
      local_14 = fVar4 * _DAT_00470b0c;
      local_1c = local_20;
      local_18 = local_14;
    }
    else if (uVar8 == 1) {
      local_1c = 0.0;
      local_20 = 0.0;
      local_14 = fVar4;
      local_18 = fVar4;
    }
    else if (uVar8 == 2) {
      local_14 = 0.0;
      local_20 = -fVar4;
      local_1c = local_20;
      local_18 = _DAT_00470b04;
    }
    DAT_004978c0 = (local_10 * fVar1 - local_20 * fVar2) + fVar5;
    DAT_004978c4 = local_10 * fVar2 + local_20 * fVar1 + fVar6;
    DAT_004978dc = (local_c * fVar1 - local_1c * fVar2) + fVar5;
    DAT_004978e0 = local_1c * fVar1 + local_c * fVar2 + fVar6;
    DAT_004978f8 = (local_8 * fVar1 - local_18 * fVar2) + fVar5;
    DAT_004978fc = local_8 * fVar2 + fVar1 * local_18 + fVar6;
    DAT_00497914 = (local_4 * fVar1 - local_14 * fVar2) + fVar5;
    DAT_00497918 = local_4 * fVar2 + local_14 * fVar1 + fVar6;
    _DAT_004978c8 =
         *(float *)(param_2 + 0x354) + *(float *)(param_2 + 0x348) + *(float *)(param_2 + 0x33c);
    _DAT_004978e4 = _DAT_004978c8;
    _DAT_00497900 = _DAT_004978c8;
    _DAT_0049791c = _DAT_004978c8;
    FUN_00442670(param_1,0);
    return;
  }
  FUN_00443290(param_1);
  return;
}

