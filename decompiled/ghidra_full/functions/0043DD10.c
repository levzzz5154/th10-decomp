/* Raw Ghidra reference; not compilable reconstruction. Address: 0043DD10 */

void FUN_0043dd10(void)

{
  short sVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int unaff_EBX;
  int unaff_ESI;
  ulonglong uVar5;
  
  sVar1 = *(short *)(&DAT_004749ce + unaff_EBX * 8);
  uVar5 = FUN_00463b2c();
  iVar3 = 0;
  piVar4 = (int *)(unaff_ESI + 0x620);
  while( true ) {
    if (*piVar4 < 0) {
      if (iVar3 < 0xc) {
        *(int *)(unaff_ESI + 0x620 + iVar3 * 4) = unaff_EBX;
        *(int *)(unaff_ESI + 0x408 + unaff_EBX * 4) = (int)sVar1;
        *(int *)(iVar3 * 0x200 + 0x680 + unaff_ESI) = (int)uVar5;
        piVar4 = (int *)(unaff_ESI + 0x650 + iVar3 * 4);
        *piVar4 = *piVar4 + 1;
      }
      return;
    }
    if (*piVar4 == unaff_EBX) break;
    iVar3 = iVar3 + 1;
    piVar4 = piVar4 + 1;
    if (0xb < iVar3) {
      return;
    }
  }
  iVar2 = *(int *)(unaff_ESI + 0x650 + iVar3 * 4);
  if (0x7f < iVar2) {
    return;
  }
  *(int *)(unaff_ESI + 0x680 + (iVar3 * 0x80 + iVar2) * 4) = (int)uVar5;
  *(int *)(unaff_ESI + 0x650 + iVar3 * 4) = *(int *)(unaff_ESI + 0x650 + iVar3 * 4) + 1;
  return;
}

