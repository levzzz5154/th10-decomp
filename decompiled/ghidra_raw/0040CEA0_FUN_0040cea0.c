/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0040CEA0
 * Tracking name: FUN_0040cea0
 * Ghidra name: FUN_0040cea0
 * Tracked span: 160 bytes
 */


void __fastcall FUN_0040cea0(undefined4 param_1)

{
  int unaff_ESI;
  
  *(uint *)(unaff_ESI + 0x378c) = *(uint *)(unaff_ESI + 0x378c) | 0x10;
  FUN_004492a0(param_1,(int)g_pGameStateManager,*(int *)(unaff_ESI + 0x774));
  *(undefined4 *)(unaff_ESI + 0x774) = 0;
  return;
}

