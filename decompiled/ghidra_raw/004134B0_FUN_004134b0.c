/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x004134B0
 * Tracking name: FUN_004134b0
 * Ghidra name: FUN_004134b0
 * Tracked span: 288 bytes
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_004134b0(void)

{
  double dVar1;
  int iVar2;
  int unaff_ESI;
  float10 fVar3;
  float10 fVar4;
  
  fVar3 = FUN_00439540();
  if (fVar3 < (float10)*(double *)(unaff_ESI + 0x14)) {
    *(double *)(unaff_ESI + 0x14) = (double)fVar3;
  }
  fVar3 = fVar3 - (float10)*(double *)(unaff_ESI + 0x14);
  if (fVar3 < (float10)_DAT_00470bc0) {
    return 1;
  }
  *(double *)(unaff_ESI + 0x14) = (double)(fVar3 + (float10)*(double *)(unaff_ESI + 0x14));
  fVar4 = (float10)*(int *)(unaff_ESI + 0x20);
  if (*(int *)(unaff_ESI + 0x20) < 0) {
    fVar4 = fVar4 + (float10)_DAT_00470b30;
  }
  *(float *)(unaff_ESI + 0x34) = (float)(fVar4 / fVar3);
  if ((float10)_DAT_00470bb8 < fVar4 / fVar3) {
    iVar2 = *(int *)(unaff_ESI + 0x1c) + 1;
    *(int *)(unaff_ESI + 0x1c) = iVar2;
    if (iVar2 == 2) {
      fVar3 = FUN_00439540();
      _DAT_00492540 = (double)fVar3;
      _DAT_00492538 = (double)fVar3;
      _DAT_00492528 = (double)fVar3;
      _DAT_00492530 = (double)fVar3;
      goto LAB_00413568;
    }
    if (iVar2 != 4) goto LAB_00413568;
    DAT_00492508 = 0;
    DAT_0049250c = 0;
    fVar3 = FUN_00439540();
    _DAT_00492540 = (double)fVar3;
    _DAT_00492538 = (double)fVar3;
    _DAT_00492528 = (double)fVar3;
    _DAT_00492530 = (double)fVar3;
  }
  *(undefined4 *)(unaff_ESI + 0x1c) = 0;
LAB_00413568:
  iVar2 = DAT_00477810;
  if (DAT_00477810 != 0) {
    if ((*(byte *)(DAT_00477810 + 0x58) & 0x14) == 0) {
      *(double *)(unaff_ESI + 0x2c) = *(double *)(unaff_ESI + 0x2c) + _DAT_00470bb0;
      if (*(float *)(unaff_ESI + 0x34) <= _DAT_00470ba8) {
        dVar1 = (double)*(float *)(unaff_ESI + 0x34) + *(double *)(unaff_ESI + 0x24);
      }
      else {
        dVar1 = *(double *)(unaff_ESI + 0x24) + _DAT_00470bb0;
      }
      *(double *)(unaff_ESI + 0x24) = dVar1;
    }
    *(uint *)(iVar2 + 0x58) = *(uint *)(iVar2 + 0x58) & 0xffffff7f;
  }
  *(undefined4 *)(unaff_ESI + 0x20) = 0;
  return 1;
}

