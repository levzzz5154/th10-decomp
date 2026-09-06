/* Raw Ghidra reference; not compilable reconstruction. Address: 00412720 */

void __fastcall SetEclResourceSlot(int param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  int unaff_ESI;
  undefined4 unaff_EDI;
  
  iVar1 = param_2 * 0x10 + unaff_ESI;
  *(int *)(iVar1 + 0x2494) = param_1;
  if (-1 < param_1) {
    *(undefined4 *)(iVar1 + 0x2498) = param_3;
    *(undefined4 *)(iVar1 + 0x249c) = unaff_EDI;
    *(undefined4 *)((param_2 + 0x24a) * 0x10 + unaff_ESI) = unaff_EDI;
  }
  return;
}

