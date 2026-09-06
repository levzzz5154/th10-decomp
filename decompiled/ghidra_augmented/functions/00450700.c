/* Raw Ghidra reference; not compilable reconstruction. Address: 00450700 */

undefined4 __fastcall FUN_00450700(byte *param_1)

{
  int iVar1;
  int unaff_ESI;
  
  iVar1 = FUN_00450470(param_1);
  *(int *)(*(int *)(unaff_ESI + 4) + 4) = iVar1;
  **(undefined4 **)(unaff_ESI + 4) = 0;
  return 0;
}

