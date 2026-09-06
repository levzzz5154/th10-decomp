/* Raw Ghidra reference; not compilable reconstruction. Address: 004362B0 */

void __fastcall FUN_004362b0(int param_1)

{
  int *piVar1;
  int iVar2;
  int in_EAX;
  
  piVar1 = &DAT_00477858 + in_EAX * 3;
  iVar2 = *piVar1;
  if ((&DAT_0047785c)[iVar2 * 3] == in_EAX) {
    (&DAT_0047785c)[iVar2 * 3] = param_1;
  }
  else {
    (&DAT_00477860)[iVar2 * 3] = param_1;
  }
  (&DAT_00477858)[param_1 * 3] = *piVar1;
  (&DAT_0047785c)[param_1 * 3] = (&DAT_0047785c)[in_EAX * 3];
  (&DAT_00477860)[param_1 * 3] = (&DAT_00477860)[in_EAX * 3];
  (&DAT_00477858)[(&DAT_0047785c)[param_1 * 3] * 3] = param_1;
  (&DAT_00477858)[(&DAT_00477860)[param_1 * 3] * 3] = param_1;
  *piVar1 = 0;
  return;
}

