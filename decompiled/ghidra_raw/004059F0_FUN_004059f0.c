/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x004059F0
 * Tracking name: FUN_004059f0
 * Ghidra name: FUN_004059f0
 * Tracked span: 208 bytes
 */


int __fastcall FUN_004059f0(int param_1)

{
  float fVar1;
  float fVar2;
  float *in_EAX;
  int iVar3;
  
  if (*(int *)(param_1 + 0x28) == 0) {
    return 0;
  }
  iVar3 = 0;
  fVar1 = in_EAX[1] - *(float *)(param_1 + 0x34);
  fVar2 = *in_EAX - *(float *)(param_1 + 0x30);
  if (fVar1 * fVar1 + fVar2 * fVar2 < *(float *)(param_1 + 0x3c) * *(float *)(param_1 + 0x3c)) {
    if (*(int *)(param_1 + 0x44) == 0) {
      if ((*(byte *)(DAT_004776f4 + 0x378c) & 1) != 0) {
        return 3;
      }
    }
    else if ((*(byte *)(DAT_004776f4 + 0x378c) & 1) != 0) {
      return 0x26;
    }
    return (-(uint)(*(int *)(DAT_00477704 + 0x10) != 0) & 0x21) + 5;
  }
  if ((*(byte *)(DAT_004776f4 + 0x378c) & 1) == 0) {
    if ((*(int *)(DAT_00477704 + 0x10) != 0) && (*(int *)(param_1 + 0x44) == 0)) {
      iVar3 = (uint)(DAT_00474c68 == 0) * 4 + 0x10;
    }
  }
  else if (*(int *)(param_1 + 0x44) == 1) {
    return (-(uint)(DAT_00474c68 != 0) & 0xfffffffd) + 0x1a;
  }
  return iVar3;
}

