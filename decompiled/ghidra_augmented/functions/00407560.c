/* Raw Ghidra reference; not compilable reconstruction. Address: 00407560 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00407560(void)

{
  float *pfVar1;
  float fVar2;
  float fVar3;
  int unaff_ESI;
  float10 fVar4;
  ulonglong uVar5;
  
  if (*(int *)(unaff_ESI + 0x64c) < *(int *)(unaff_ESI + 0x670)) {
    *(float *)(unaff_ESI + 0x3d8) =
         DAT_00476f78 * *(float *)(unaff_ESI + 0x65c) + *(float *)(unaff_ESI + 0x3d8);
    fVar2 = DAT_00476f78 * *(float *)(unaff_ESI + 0x668);
    fVar3 = DAT_00476f78 * *(float *)(unaff_ESI + 0x66c);
    *(float *)(unaff_ESI + 0x3c0) =
         DAT_00476f78 * *(float *)(unaff_ESI + 0x664) + *(float *)(unaff_ESI + 0x3c0);
    *(float *)(unaff_ESI + 0x3c4) = fVar2 + *(float *)(unaff_ESI + 0x3c4);
    *(float *)(unaff_ESI + 0x3c8) = fVar3 + *(float *)(unaff_ESI + 0x3c8);
    if ((_DAT_00470c58 < ABS(*(float *)(unaff_ESI + 0x3c0))) ||
       (_DAT_00470c58 < ABS(*(float *)(unaff_ESI + 0x3c4)))) {
      fVar4 = (float10)fpatan((float10)*(float *)(unaff_ESI + 0x3c4),
                              (float10)*(float *)(unaff_ESI + 0x3c0));
      *(float *)(unaff_ESI + 0x3e4) = (float)fVar4;
    }
  }
  else {
    *(uint *)(unaff_ESI + 0x43c) = *(uint *)(unaff_ESI + 0x43c) & 0xffffffef;
  }
  pfVar1 = *(float **)(unaff_ESI + 0x654);
  *(int *)(unaff_ESI + 0x648) = *(int *)(unaff_ESI + 0x64c);
  if ((_DAT_00470b68 < *pfVar1) && (*pfVar1 < _DAT_00470b64)) {
    fVar2 = *(float *)(unaff_ESI + 0x650) + _DAT_00470afc;
    *(int *)(unaff_ESI + 0x64c) = *(int *)(unaff_ESI + 0x64c) + 1;
    *(float *)(unaff_ESI + 0x650) = fVar2;
    return;
  }
  *(float *)(unaff_ESI + 0x650) = *(float *)(unaff_ESI + 0x650) + *pfVar1;
  uVar5 = FUN_00463b2c();
  *(int *)(unaff_ESI + 0x64c) = (int)uVar5;
  return;
}

