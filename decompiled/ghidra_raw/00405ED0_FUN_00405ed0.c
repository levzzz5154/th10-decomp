/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00405ED0
 * Tracking name: FUN_00405ed0
 * Ghidra name: FUN_00405ed0
 * Tracked span: 160 bytes
 */


void __fastcall FUN_00405ed0(undefined4 param_1)

{
  int iVar1;
  int unaff_ESI;
  undefined4 *puVar2;
  
  FUN_004493e0(param_1,*(int *)(unaff_ESI + 0x3e0b50));
  puVar2 = (undefined4 *)(unaff_ESI + 0x60);
  for (iVar1 = 0xf82bc; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  *(undefined4 **)(unaff_ESI + 0x10) = (undefined4 *)(unaff_ESI + 0x60);
  *(undefined2 *)(unaff_ESI + 0x3e07a6) = 5;
  return;
}

