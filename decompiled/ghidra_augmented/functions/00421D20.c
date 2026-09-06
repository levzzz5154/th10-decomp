/* Raw Ghidra reference; not compilable reconstruction. Address: 00421D20 */

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

