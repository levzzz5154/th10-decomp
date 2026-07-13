/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00407BE0
 * Tracking name: FUN_00407be0
 * Ghidra name: FUN_00407be0
 * Tracked span: 448 bytes
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00407be0(void)

{
  float fVar1;
  bool bVar2;
  int unaff_ESI;
  float10 fVar3;
  
  if ((((*(float *)(unaff_ESI + 0x3b4) < _DAT_00470b40 !=
         (*(float *)(unaff_ESI + 0x3b4) == _DAT_00470b40)) ||
       (_DAT_00470b3c <= *(float *)(unaff_ESI + 0x3b4))) ||
      (*(float *)(unaff_ESI + 0x3b8) < _DAT_00470b04 !=
       (*(float *)(unaff_ESI + 0x3b8) == _DAT_00470b04))) ||
     (_DAT_00470b38 <= *(float *)(unaff_ESI + 0x3b8))) {
    bVar2 = false;
    if (-1 < *(int *)(unaff_ESI + 0x458)) {
      FUN_0043dc90(&DAT_00492590,0);
    }
    if ((*(float *)(unaff_ESI + 0x3b4) < _DAT_00470b40) ||
       (_DAT_00470b3c <= *(float *)(unaff_ESI + 0x3b4))) {
      fVar3 = (float10)FUN_0044bc10(-*(float *)(unaff_ESI + 0x3e4) - _DAT_00470b18,0.0);
      *(float *)(unaff_ESI + 0x3e4) = (float)fVar3;
      bVar2 = true;
      fVar1 = _DAT_00470b54;
      if (*(float *)(unaff_ESI + 0x3b4) < _DAT_00470b40) {
        fVar1 = _DAT_00470b58;
      }
      *(float *)(unaff_ESI + 0x3b4) = fVar1 - *(float *)(unaff_ESI + 0x3b4);
    }
    if (((*(uint *)(unaff_ESI + 0x43c) & 0x8000000) == 0) &&
       ((*(float *)(unaff_ESI + 0x3b8) < _DAT_00470b04 ||
        ((_DAT_00470b38 <= *(float *)(unaff_ESI + 0x3b8) &&
         ((*(uint *)(unaff_ESI + 0x43c) & 0x400) != 0)))))) {
      bVar2 = true;
      *(float *)(unaff_ESI + 0x3e4) = -*(float *)(unaff_ESI + 0x3e4);
      if (_DAT_00470b04 <= *(float *)(unaff_ESI + 0x3b8)) {
        fVar1 = (_DAT_00470b38 - *(float *)(unaff_ESI + 0x3b8)) + _DAT_00470b38;
      }
      else {
        fVar1 = -*(float *)(unaff_ESI + 0x3b8);
      }
      *(float *)(unaff_ESI + 0x3b8) = fVar1;
    }
    if (_DAT_00470b50 < *(float *)(unaff_ESI + 0x6f8)) {
      *(undefined4 *)(unaff_ESI + 0x3d8) = *(undefined4 *)(unaff_ESI + 0x6f8);
    }
    FUN_00408750((void *)(unaff_ESI + 0x3c0),*(float *)(unaff_ESI + 0x3e4),
                 *(float *)(unaff_ESI + 0x3d8));
    if (bVar2) {
      *(int *)(unaff_ESI + 0x70c) = *(int *)(unaff_ESI + 0x70c) + 1;
    }
    if (*(int *)(unaff_ESI + 0x710) <= *(int *)(unaff_ESI + 0x70c)) {
      *(uint *)(unaff_ESI + 0x43c) = *(uint *)(unaff_ESI + 0x43c) & 0xf7fff3ff;
    }
  }
  return;
}

