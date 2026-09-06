/* Raw Ghidra reference; not compilable reconstruction. Address: 00448740 */

void FUN_00448740(void)

{
  void *pvVar1;
  
  pvVar1 = g_pGameStateManager;
  DAT_00491e64 = 0;
  DAT_00491e68 = 0;
  *(undefined4 *)((int)g_pGameStateManager + 0x5c) = 0;
  *(undefined4 *)((int)pvVar1 + 0x60) = 0;
  FUN_00448980();
  return;
}

