/* Raw Ghidra reference; not compilable reconstruction. Address: 00436210 */

void __fastcall FUN_00436210(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = (&DAT_00477858)[param_1 * 3];
  if (iVar1 != 0) {
    iVar2 = (&DAT_00477860)[param_1 * 3];
    if (iVar2 == 0) {
      iVar2 = (&DAT_0047785c)[param_1 * 3];
    }
    else {
      iVar1 = 0;
      if ((&DAT_0047785c)[param_1 * 3] != 0) {
        iVar1 = FUN_00436330();
        FUN_00436210(iVar1);
        FUN_004362b0(iVar1);
        return;
      }
    }
    FUN_00436260(iVar1,iVar2);
  }
  return;
}

