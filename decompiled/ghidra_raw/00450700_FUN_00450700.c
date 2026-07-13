/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00450700
 * Tracking name: FUN_00450700
 * Ghidra name: FUN_00450700
 * Tracked span: 7424 bytes
 */


undefined4 __fastcall FUN_00450700(byte *param_1)

{
  int iVar1;
  int unaff_ESI;
  
  iVar1 = FUN_00450470(param_1);
  *(int *)(*(int *)(unaff_ESI + 4) + 4) = iVar1;
  **(undefined4 **)(unaff_ESI + 4) = 0;
  return 0;
}

