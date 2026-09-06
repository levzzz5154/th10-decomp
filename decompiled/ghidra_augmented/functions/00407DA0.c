/* Raw Ghidra reference; not compilable reconstruction. Address: 00407DA0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00407da0(void)

{
  float fVar1;
  int iVar2;
  float *extraout_ECX;
  int extraout_EDX;
  int unaff_EBX;
  
  iVar2 = FUN_004061d0((void *)(unaff_EBX + 0x3b4),*(float *)(*(int *)(unaff_EBX + 0x39c) + 0x34),
                       *(float *)(*(int *)(unaff_EBX + 0x39c) + 0x30));
  if (iVar2 == 0) {
    return;
  }
  if (_DAT_00470b40 <= *extraout_ECX) {
    if (*extraout_ECX <= _DAT_00470b3c) goto LAB_00407e1d;
    fVar1 = *extraout_ECX - (*(float *)(extraout_EDX + 0x34) + _DAT_00470b54);
  }
  else {
    fVar1 = *(float *)(extraout_EDX + 0x34) + *extraout_ECX + _DAT_00470b54;
  }
  *extraout_ECX = fVar1;
  FUN_0044bf40(-1.0);
  if (-1 < *(int *)(unaff_EBX + 0x458)) {
    FUN_0043dc90(&DAT_00492590,0);
  }
LAB_00407e1d:
  if (*(int *)(unaff_EBX + 0x750) < 1) {
    *(uint *)(unaff_EBX + 0x43c) = *(uint *)(unaff_EBX + 0x43c) ^ 0x100000;
  }
  return;
}

