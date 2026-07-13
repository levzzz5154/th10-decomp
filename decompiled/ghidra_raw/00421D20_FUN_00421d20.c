/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00421D20
 * Tracking name: FUN_00421d20
 * Ghidra name: FUN_00421d20
 * Tracked span: 224 bytes
 */


void FUN_00421d20(void)

{
  int *piVar1;
  int unaff_ESI;
  
  piVar1 = *(int **)(unaff_ESI + 0xc);
  if (piVar1 != (int *)0x0) {
    (**(code **)(*piVar1 + 8))(piVar1);
    *(undefined4 *)(unaff_ESI + 0xc) = 0;
  }
  return;
}

