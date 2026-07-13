/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0044D550
 * Tracking name: FUN_0044d550
 * Ghidra name: FUN_0044d550
 * Tracked span: 96 bytes
 */


uint FUN_0044d550(void)

{
  int *piVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  int unaff_EDI;
  
  if (*(int *)(unaff_EDI + 4) != 0) {
    uVar4 = 0;
    uVar5 = 0;
    *(undefined4 *)(unaff_EDI + 0x30) = 0;
    if (*(int *)(unaff_EDI + 0x10) != 0) {
      do {
        piVar1 = *(int **)(*(int *)(unaff_EDI + 4) + uVar5 * 4);
        uVar2 = (**(code **)(*piVar1 + 0x48))(piVar1);
        piVar1 = *(int **)(*(int *)(unaff_EDI + 4) + uVar5 * 4);
        uVar3 = (**(code **)(*piVar1 + 0x34))(piVar1,0);
        uVar4 = uVar4 | uVar2 | uVar3;
        uVar5 = uVar5 + 1;
      } while (uVar5 < *(uint *)(unaff_EDI + 0x10));
    }
    *(undefined4 *)(unaff_EDI + 0x1c) = 0;
    return uVar4;
  }
  return 0x800401f0;
}

