/* Raw Ghidra reference; not compilable reconstruction. Address: 00407EF0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00407ef0(void)

{
  float *pfVar1;
  int unaff_ESI;
  float10 fVar2;
  float10 fVar3;
  ulonglong uVar4;
  float fVar5;
  undefined4 local_4;
  
  if (*(int *)(unaff_ESI + 0x7b8) < *(int *)(unaff_ESI + 0x7dc)) {
    fVar2 = (float10)*(float *)(DAT_00477834 + 0x3c0) - (float10)*(float *)(unaff_ESI + 0x3b4);
    fVar3 = (float10)*(float *)(DAT_00477834 + 0x3c4) - (float10)*(float *)(unaff_ESI + 0x3b8);
    if ((fVar3 == (float10)_DAT_00470b04) && (fVar2 == (float10)_DAT_00470b04)) {
      local_4 = 1.5707964;
    }
    else {
      fVar2 = (float10)fpatan(fVar3,fVar2);
      local_4 = (float)fVar2;
    }
    fVar5 = *(float *)(unaff_ESI + 0x3e4);
    fVar2 = (float10)FUN_0044bc10(*(float *)(unaff_ESI + 0x7cc),local_4);
    fVar2 = FUN_00408660((float)fVar2,fVar5);
    fVar2 = (float10)FUN_0044bc10(*(float *)(unaff_ESI + 0x3e4),
                                  (float)(fVar2 * (float10)*(float *)(unaff_ESI + 0x7c8) *
                                         (float10)DAT_00476f78));
    *(float *)(unaff_ESI + 0x3e4) = (float)fVar2;
    FUN_00408750((void *)(unaff_ESI + 0x3c0),(float)fVar2,*(float *)(unaff_ESI + 0x3d8));
  }
  else {
    *(uint *)(unaff_ESI + 0x43c) = *(uint *)(unaff_ESI + 0x43c) & 0xfbffffff;
  }
  pfVar1 = *(float **)(unaff_ESI + 0x7c0);
  *(int *)(unaff_ESI + 0x7b4) = *(int *)(unaff_ESI + 0x7b8);
  if ((_DAT_00470b68 < *pfVar1) && (*pfVar1 < _DAT_00470b64)) {
    fVar5 = *(float *)(unaff_ESI + 0x7bc) + _DAT_00470afc;
    *(int *)(unaff_ESI + 0x7b8) = *(int *)(unaff_ESI + 0x7b8) + 1;
    *(float *)(unaff_ESI + 0x7bc) = fVar5;
    return;
  }
  *(float *)(unaff_ESI + 0x7bc) = *pfVar1 + *(float *)(unaff_ESI + 0x7bc);
  uVar4 = FUN_00463b2c();
  *(int *)(unaff_ESI + 0x7b8) = (int)uVar4;
  return;
}

