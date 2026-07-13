/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00436260
 * Tracking name: FUN_00436260
 * Ghidra name: FUN_00436260
 * Tracked span: 80 bytes
 */


void __fastcall FUN_00436260(undefined4 param_1,int param_2)

{
  int iVar1;
  int unaff_ESI;
  
  (&DAT_00477858)[param_2 * 3] = (&DAT_00477858)[unaff_ESI * 3];
  iVar1 = (&DAT_00477858)[unaff_ESI * 3];
  if ((&DAT_00477860)[iVar1 * 3] == unaff_ESI) {
    (&DAT_00477860)[iVar1 * 3] = param_2;
    (&DAT_00477858)[unaff_ESI * 3] = 0;
    return;
  }
  (&DAT_0047785c)[iVar1 * 3] = param_2;
  (&DAT_00477858)[unaff_ESI * 3] = 0;
  return;
}

