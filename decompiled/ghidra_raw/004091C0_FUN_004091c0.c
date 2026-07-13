/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x004091C0
 * Tracking name: FUN_004091c0
 * Ghidra name: FUN_004091c0
 * Tracked span: 112 bytes
 */


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

