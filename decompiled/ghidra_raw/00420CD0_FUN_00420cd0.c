/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00420CD0
 * Tracking name: FUN_00420cd0
 * Ghidra name: FUN_00420cd0
 * Tracked span: 256 bytes
 */


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

