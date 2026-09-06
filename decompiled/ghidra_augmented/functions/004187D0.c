/* Raw Ghidra reference; not compilable reconstruction. Address: 004187D0 */

undefined4 __fastcall FUN_004187d0(int param_1)

{
  void *pvVar1;
  
  pvVar1 = g_pGameStateManager;
  if ((*(byte *)(param_1 + 0x58) & 4) == 0) {
    *(undefined4 *)((int)g_pGameStateManager + 0x50) = 0;
    *(undefined4 *)((int)pvVar1 + 0x54) = 0;
    *(undefined4 *)((int)pvVar1 + 0x4c) = 0;
    *(undefined4 *)((int)pvVar1 + 0x58) = 0;
  }
  return 1;
}

