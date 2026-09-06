/* Raw Ghidra reference; not compilable reconstruction. Address: 004091C0 */

undefined4 FUN_004091c0(void)

{
  int unaff_EBX;
  int iVar1;
  
  if ((*(byte *)(unaff_EBX + 0x378c) & 1) != 0) {
    iVar1 = 8;
    do {
      FUN_004451c0(g_pGameStateManager);
      iVar1 = iVar1 + -1;
    } while (iVar1 != 0);
    iVar1 = 5;
    do {
      FUN_004451c0(g_pGameStateManager);
      iVar1 = iVar1 + -1;
    } while (iVar1 != 0);
  }
  return 1;
}

