/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00443290
 * Tracking name: FUN_00443290
 * Ghidra name: FUN_00443290
 * Tracked span: 2256 bytes
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00443290(void *param_1)

{
  float fVar1;
  float fVar2;
  int in_EAX;
  uint uVar3;
  
  fVar1 = *(float *)(in_EAX + 0x4c) * *(float *)(in_EAX + 0x3c);
  uVar3 = *(uint *)(in_EAX + 0x35c) >> 0x12 & 3;
  fVar2 = *(float *)(in_EAX + 0x50) * *(float *)(in_EAX + 0x40);
  if (uVar3 == 0) {
    DAT_004978c0 = (*(float *)(in_EAX + 0x34c) + *(float *)(in_EAX + 0x340) +
                   *(float *)(in_EAX + 0x334)) - fVar1 * _DAT_00470b0c;
    DAT_004978dc = fVar1 + DAT_004978c0;
    DAT_004978f8 = DAT_004978c0;
    DAT_00497914 = DAT_004978dc;
  }
  else {
    if (uVar3 == 1) {
      DAT_004978f8 = *(float *)(in_EAX + 0x334) + *(float *)(in_EAX + 0x340) +
                     *(float *)(in_EAX + 0x34c);
      fVar1 = *(float *)(in_EAX + 0x334) + *(float *)(in_EAX + 0x340) + fVar1;
    }
    else {
      if (uVar3 != 2) goto LAB_00443379;
      DAT_004978f8 = (*(float *)(in_EAX + 0x334) + *(float *)(in_EAX + 0x340) +
                     *(float *)(in_EAX + 0x34c)) - fVar1;
      fVar1 = *(float *)(in_EAX + 0x334) + *(float *)(in_EAX + 0x340);
    }
    DAT_004978dc = fVar1 + *(float *)(in_EAX + 0x34c);
    DAT_004978c0 = DAT_004978f8;
    DAT_00497914 = DAT_004978dc;
  }
LAB_00443379:
  uVar3 = *(uint *)(in_EAX + 0x35c) >> 0x14 & 3;
  if (uVar3 == 0) {
    DAT_004978c4 = (*(float *)(in_EAX + 0x350) + *(float *)(in_EAX + 0x344) +
                   *(float *)(in_EAX + 0x338)) - fVar2 * _DAT_00470b0c;
    DAT_004978fc = DAT_004978c4 + fVar2;
    DAT_004978e0 = DAT_004978c4;
    DAT_00497918 = DAT_004978fc;
  }
  else if (uVar3 == 1) {
    DAT_004978c4 = *(float *)(in_EAX + 0x350) + *(float *)(in_EAX + 0x338) +
                   *(float *)(in_EAX + 0x344);
    DAT_004978fc = *(float *)(in_EAX + 0x350) + *(float *)(in_EAX + 0x338) + fVar2 +
                   *(float *)(in_EAX + 0x344);
    DAT_004978e0 = DAT_004978c4;
    DAT_00497918 = DAT_004978fc;
  }
  else if (uVar3 == 2) {
    DAT_004978c4 = (*(float *)(in_EAX + 0x350) + *(float *)(in_EAX + 0x338) +
                   *(float *)(in_EAX + 0x344)) - fVar2;
    DAT_004978fc = *(float *)(in_EAX + 0x350) + *(float *)(in_EAX + 0x338) +
                   *(float *)(in_EAX + 0x344);
    DAT_004978e0 = DAT_004978c4;
    DAT_00497918 = DAT_004978fc;
  }
  _DAT_004978c8 =
       *(float *)(in_EAX + 0x350) + *(float *)(in_EAX + 0x348) + *(float *)(in_EAX + 0x33c);
  _DAT_004978e4 = _DAT_004978c8;
  _DAT_00497900 = _DAT_004978c8;
  _DAT_0049791c = _DAT_004978c8;
  FUN_00442670(param_1,0);
  return;
}

