/* Raw Ghidra reference; not compilable reconstruction. Address: 0044D600 */

uint QueryPlatformInterfaces(void)

{
  int *piVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  int unaff_EDI;
  
  if (*(int *)(unaff_EDI + 4) == 0) {
    return 0x800401f0;
  }
  uVar3 = 0;
  uVar4 = 0;
  if (*(int *)(unaff_EDI + 0x10) != 0) {
    uVar3 = 0;
    do {
      piVar1 = *(int **)(*(int *)(unaff_EDI + 4) + uVar4 * 4);
      uVar2 = (**(code **)(*piVar1 + 0x34))(piVar1,0);
      uVar3 = uVar3 | uVar2;
      uVar4 = uVar4 + 1;
    } while (uVar4 < *(uint *)(unaff_EDI + 0x10));
  }
  return uVar3;
}

