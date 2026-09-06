/* Raw Ghidra reference; not compilable reconstruction. Address: 0043AE20 */

undefined4 __fastcall FUN_0043ae20(undefined4 param_1)

{
  undefined4 extraout_ECX;
  int *piVar1;
  int iVar2;
  int unaff_EDI;
  
  if (*(int *)(unaff_EDI + 0x138) == 0) {
    return 0xffffffff;
  }
  piVar1 = (int *)(unaff_EDI + 0x14);
  iVar2 = 0x20;
  do {
    if (*piVar1 != 0) {
      FUN_0043aeb0(param_1,unaff_EDI);
      param_1 = extraout_ECX;
    }
    piVar1 = piVar1 + 1;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  if (*(UINT *)(unaff_EDI + 4) != 0) {
    timeKillEvent(*(UINT *)(unaff_EDI + 4));
  }
  timeEndPeriod(*(UINT *)(unaff_EDI + 8));
  *(undefined4 *)(unaff_EDI + 4) = 0;
  if (*(HMIDIOUT *)(unaff_EDI + 0x13c) != (HMIDIOUT)0x0) {
    midiOutReset(*(HMIDIOUT *)(unaff_EDI + 0x13c));
    midiOutClose(*(HMIDIOUT *)(unaff_EDI + 0x13c));
    *(undefined4 *)(unaff_EDI + 0x13c) = 0;
  }
  *(undefined4 *)(unaff_EDI + 0x10) = 0xffffffff;
  return 0;
}

