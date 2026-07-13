/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0043AEB0
 * Tracking name: FUN_0043aeb0
 * Ghidra name: FUN_0043aeb0
 * Tracked span: 128 bytes
 */


undefined4 __fastcall FUN_0043aeb0(undefined4 param_1,int param_2)

{
  int iVar1;
  int *piVar2;
  LPMIDIHDR unaff_ESI;
  
  iVar1 = 0;
  piVar2 = (int *)(param_2 + 0x14);
  do {
    if ((LPMIDIHDR)*piVar2 == unaff_ESI) {
      *(undefined4 *)(param_2 + 0x14 + iVar1 * 4) = 0;
      midiOutUnprepareHeader(*(HMIDIOUT *)(param_2 + 0x13c),unaff_ESI,0x40);
      if (unaff_ESI->lpData != (LPSTR)0x0) {
        _free(unaff_ESI->lpData);
        unaff_ESI->lpData = (LPSTR)0x0;
      }
      _free(unaff_ESI);
      return 0;
    }
    iVar1 = iVar1 + 1;
    piVar2 = piVar2 + 1;
  } while (iVar1 < 0x20);
  return 0xffffffff;
}

