/* Raw Ghidra reference; not compilable reconstruction. Address: 0040CEA0 */

void __fastcall FUN_0040cea0(undefined4 param_1)

{
  int unaff_ESI;
  
  *(uint *)(unaff_ESI + 0x378c) = *(uint *)(unaff_ESI + 0x378c) | 0x10;
  FUN_004492a0(param_1,(int)g_pGameStateManager,*(int *)(unaff_ESI + 0x774));
  *(undefined4 *)(unaff_ESI + 0x774) = 0;
  return;
}

