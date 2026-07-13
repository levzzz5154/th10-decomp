/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x004074B0
 * Tracking name: FUN_004074b0
 * Ghidra name: FUN_004074b0
 * Tracked span: 176 bytes
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004074b0(void)

{
  float *pfVar1;
  float fVar2;
  int unaff_ESI;
  ulonglong uVar3;
  
  if (*(int *)(unaff_ESI + 0x618) < 0x11) {
    FUN_00408750((void *)(unaff_ESI + 0x3c0),*(float *)(unaff_ESI + 0x3e4),
                 (_DAT_00470c68 - *(float *)(unaff_ESI + 0x61c) * _DAT_00470c6c) +
                 *(float *)(unaff_ESI + 0x3d8));
  }
  else {
    *(uint *)(unaff_ESI + 0x43c) = *(uint *)(unaff_ESI + 0x43c) ^ 1;
  }
  pfVar1 = *(float **)(unaff_ESI + 0x620);
  *(int *)(unaff_ESI + 0x614) = *(int *)(unaff_ESI + 0x618);
  if ((_DAT_00470b68 < *pfVar1) && (*pfVar1 < _DAT_00470b64)) {
    fVar2 = *(float *)(unaff_ESI + 0x61c) + _DAT_00470afc;
    *(int *)(unaff_ESI + 0x618) = *(int *)(unaff_ESI + 0x618) + 1;
    *(float *)(unaff_ESI + 0x61c) = fVar2;
    return;
  }
  *(float *)(unaff_ESI + 0x61c) = *pfVar1 + *(float *)(unaff_ESI + 0x61c);
  uVar3 = FUN_00463b2c();
  *(int *)(unaff_ESI + 0x618) = (int)uVar3;
  return;
}

