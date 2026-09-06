/* Raw Ghidra reference; not compilable reconstruction. Address: 004136C0 */

void __fastcall FUN_004136c0(undefined4 param_1)

{
  void *pvVar1;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  int unaff_ESI;
  
  pvVar1 = g_pGameStateManager;
  FUN_004492a0(param_1,(int)g_pGameStateManager,*(int *)(unaff_ESI + 0x40));
  *(undefined4 *)(unaff_ESI + 0x40) = 0;
  FUN_004492a0(*(undefined4 *)(unaff_ESI + 0x44),(int)pvVar1,*(undefined4 *)(unaff_ESI + 0x44));
  *(undefined4 *)(unaff_ESI + 0x44) = 0;
  FUN_004492a0(extraout_ECX,(int)pvVar1,*(int *)(unaff_ESI + 0x48));
  *(undefined4 *)(unaff_ESI + 0x48) = 0;
  FUN_004492a0(extraout_ECX_00,(int)pvVar1,*(int *)(unaff_ESI + 0x4c));
  *(undefined4 *)(unaff_ESI + 0x4c) = 0;
  FUN_004492a0(*(undefined4 *)(unaff_ESI + 0x50),(int)pvVar1,*(undefined4 *)(unaff_ESI + 0x50));
  *(undefined4 *)(unaff_ESI + 0x50) = 0;
  FUN_004492a0(extraout_ECX_01,(int)pvVar1,*(int *)(unaff_ESI + 0x54));
  *(undefined4 *)(unaff_ESI + 0x54) = 0;
  return;
}

