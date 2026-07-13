/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00407A30
 * Tracking name: FUN_00407a30
 * Ghidra name: FUN_00407a30
 * Tracked span: 432 bytes
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00407a30(void)

{
  float *pfVar1;
  float fVar2;
  int iVar3;
  int unaff_ESI;
  float10 fVar4;
  float10 fVar5;
  ulonglong uVar6;
  float local_4;
  
  if (*(int *)(unaff_ESI + 0x6b4) < *(int *)(unaff_ESI + 0x6d8)) {
    local_4 = *(float *)(unaff_ESI + 0x3d8) -
              (*(float *)(unaff_ESI + 0x3d8) * *(float *)(unaff_ESI + 0x6b8)) /
              (float)*(int *)(unaff_ESI + 0x6d8);
  }
  else {
    if (-1 < *(int *)(unaff_ESI + 0x458)) {
      FUN_0043dc90(&DAT_00492590,0);
    }
    iVar3 = *(int *)(unaff_ESI + 0x6e0) + 1;
    *(int *)(unaff_ESI + 0x6e0) = iVar3;
    if (*(int *)(unaff_ESI + 0x6dc) <= iVar3) {
      *(uint *)(unaff_ESI + 0x43c) = *(uint *)(unaff_ESI + 0x43c) & 0xffffff7f;
    }
    fVar4 = (float10)*(float *)(DAT_00477834 + 0x3c0) - (float10)*(float *)(unaff_ESI + 0x3b4);
    fVar5 = (float10)*(float *)(DAT_00477834 + 0x3c4) - (float10)*(float *)(unaff_ESI + 0x3b8);
    if ((fVar5 == (float10)_DAT_00470b04) && (fVar4 == (float10)_DAT_00470b04)) {
      local_4 = 1.5707964;
    }
    else {
      fVar4 = (float10)fpatan(fVar5,fVar4);
      local_4 = (float)fVar4;
    }
    fVar4 = (float10)FUN_0044bc10(local_4,*(float *)(unaff_ESI + 0x6c8));
    *(float *)(unaff_ESI + 0x3e4) = (float)fVar4;
    local_4 = *(float *)(unaff_ESI + 0x6c4);
    *(float *)(unaff_ESI + 0x3d8) = local_4;
    if ((*(uint *)(unaff_ESI + 0x6c0) & 1) == 0) {
      *(undefined4 *)(unaff_ESI + 0x6b4) = 0;
      *(undefined4 *)(unaff_ESI + 0x6b0) = 0xfff0bdc1;
      *(undefined4 *)(unaff_ESI + 0x6b8) = 0;
      *(undefined4 **)(unaff_ESI + 0x6bc) = &DAT_00476f78;
      *(uint *)(unaff_ESI + 0x6c0) = *(uint *)(unaff_ESI + 0x6c0) | 1;
    }
    *(undefined4 *)(unaff_ESI + 0x6b4) = 0;
    *(undefined4 *)(unaff_ESI + 0x6b8) = 0;
    *(undefined4 *)(unaff_ESI + 0x6b0) = 0xffffffff;
  }
  FUN_00408750((void *)(unaff_ESI + 0x3c0),*(float *)(unaff_ESI + 0x3e4),local_4);
  pfVar1 = *(float **)(unaff_ESI + 0x6bc);
  *(int *)(unaff_ESI + 0x6b0) = *(int *)(unaff_ESI + 0x6b4);
  if ((_DAT_00470b68 < *pfVar1) && (*pfVar1 < _DAT_00470b64)) {
    fVar2 = *(float *)(unaff_ESI + 0x6b8) + _DAT_00470afc;
    *(int *)(unaff_ESI + 0x6b4) = *(int *)(unaff_ESI + 0x6b4) + 1;
    *(float *)(unaff_ESI + 0x6b8) = fVar2;
    return;
  }
  *(float *)(unaff_ESI + 0x6b8) = *(float *)(unaff_ESI + 0x6b8) + *pfVar1;
  uVar6 = FUN_00463b2c();
  *(int *)(unaff_ESI + 0x6b4) = (int)uVar6;
  return;
}

