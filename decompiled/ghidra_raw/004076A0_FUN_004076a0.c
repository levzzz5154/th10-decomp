/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x004076A0
 * Tracking name: FUN_004076a0
 * Ghidra name: FUN_004076a0
 * Tracked span: 224 bytes
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004076a0(void)

{
  float *pfVar1;
  float fVar2;
  int unaff_ESI;
  float10 fVar3;
  ulonglong uVar4;
  
  if (*(int *)(unaff_ESI + 0x680) < *(int *)(unaff_ESI + 0x6a4)) {
    fVar3 = (float10)FUN_0044bc10(*(float *)(unaff_ESI + 0x3e4),
                                  DAT_00476f78 * *(float *)(unaff_ESI + 0x694));
    *(float *)(unaff_ESI + 0x3e4) = (float)fVar3;
    fVar2 = DAT_00476f78 * *(float *)(unaff_ESI + 0x690) + *(float *)(unaff_ESI + 0x3d8);
    *(float *)(unaff_ESI + 0x3d8) = fVar2;
    FUN_00408750((void *)(unaff_ESI + 0x3c0),*(float *)(unaff_ESI + 0x3e4),fVar2);
  }
  else {
    *(uint *)(unaff_ESI + 0x43c) = *(uint *)(unaff_ESI + 0x43c) & 0xffffffdf;
  }
  pfVar1 = *(float **)(unaff_ESI + 0x688);
  *(int *)(unaff_ESI + 0x67c) = *(int *)(unaff_ESI + 0x680);
  if ((_DAT_00470b68 < *pfVar1) && (*pfVar1 < _DAT_00470b64)) {
    fVar2 = *(float *)(unaff_ESI + 0x684) + _DAT_00470afc;
    *(int *)(unaff_ESI + 0x680) = *(int *)(unaff_ESI + 0x680) + 1;
    *(float *)(unaff_ESI + 0x684) = fVar2;
    return;
  }
  *(float *)(unaff_ESI + 0x684) = *pfVar1 + *(float *)(unaff_ESI + 0x684);
  uVar4 = FUN_00463b2c();
  *(int *)(unaff_ESI + 0x680) = (int)uVar4;
  return;
}

