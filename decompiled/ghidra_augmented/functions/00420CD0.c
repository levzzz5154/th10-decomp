/* Raw Ghidra reference; not compilable reconstruction. Address: 00420CD0 */

undefined4 FUN_00420cd0(void)

{
  undefined4 uVar1;
  int unaff_EDI;
  
  if (*(int *)(unaff_EDI + 0x750) != 0) {
    FUN_00442f50();
    *(undefined4 *)(unaff_EDI + 0x750) = 0;
    uVar1 = (**(code **)(**(int **)(unaff_EDI + 8) + 0xe4))(*(int **)(unaff_EDI + 8),0x1c,0);
    return uVar1;
  }
  return 0;
}

