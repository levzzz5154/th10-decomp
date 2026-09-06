/* Raw Ghidra reference; not compilable reconstruction. Address: 00407E40 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00407e40(void)

{
  float fVar1;
  int iVar2;
  int extraout_EDX;
  int unaff_EBX;
  
  iVar2 = FUN_004061d0((void *)(unaff_EBX + 0x3b4),*(float *)(*(int *)(unaff_EBX + 0x39c) + 0x34),
                       *(float *)(*(int *)(unaff_EBX + 0x39c) + 0x30));
  if (iVar2 == 0) {
    return;
  }
  if ((float)_DAT_00470b70 <= *(float *)(unaff_EBX + 0x3b8)) {
    if (*(float *)(unaff_EBX + 0x3b8) <= _DAT_00470b38) goto LAB_00407ed5;
    fVar1 = *(float *)(unaff_EBX + 0x3b8) - (*(float *)(extraout_EDX + 0x30) + _DAT_00470b38);
  }
  else {
    fVar1 = *(float *)(extraout_EDX + 0x30) + *(float *)(unaff_EBX + 0x3b8) + _DAT_00470b38;
  }
  *(float *)(unaff_EBX + 0x3b8) = fVar1;
  FUN_0044bf40(-1.0);
  if (-1 < *(int *)(unaff_EBX + 0x458)) {
    FUN_0043dc90(&DAT_00492590,0);
  }
LAB_00407ed5:
  if (*(int *)(unaff_EBX + 0x784) < 1) {
    *(uint *)(unaff_EBX + 0x43c) = *(uint *)(unaff_EBX + 0x43c) ^ 0x200000;
  }
  return;
}

