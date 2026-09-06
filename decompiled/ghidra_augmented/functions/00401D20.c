/* Raw Ghidra reference; not compilable reconstruction. Address: 00401D20 */

void FUN_00401d20(void)

{
  int unaff_EBX;
  int unaff_ESI;
  
  *(int *)(unaff_ESI + 900) = unaff_EBX * 0x118 + 0x154 + unaff_ESI;
  FUN_004215a0();
  (**(code **)(**(int **)(unaff_ESI + 8) + 0xbc))
            (*(int **)(unaff_ESI + 8),*(int *)(unaff_ESI + 900) + 0xcc);
  *(int *)(unaff_ESI + 0x388) = unaff_EBX;
  return;
}

