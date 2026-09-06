/* Raw Ghidra reference; not compilable reconstruction. Address: 0043B7A0 */

void FUN_0043b7a0(DWORD param_1)

{
  DWORD DVar1;
  int iVar2;
  int iVar3;
  int unaff_EDI;
  ulonglong uVar4;
  
  DVar1 = param_1;
  if (*(int *)(unaff_EDI + 0x2d4) == 0) {
    iVar3 = 0;
    do {
      uVar4 = FUN_00463b2c();
      iVar2 = (int)uVar4 + DVar1;
      if (iVar2 < 0) {
        iVar2 = 0;
      }
      else if (0x7f < iVar2) {
        iVar2 = 0x7f;
      }
      if (*(HMIDIOUT *)(unaff_EDI + 0x13c) != (HMIDIOUT)0x0) {
        param_1 = CONCAT22(CONCAT11(param_1._3_1_,(char)iVar2),CONCAT11(7,(char)iVar3 + -0x50));
        midiOutShortMsg(*(HMIDIOUT *)(unaff_EDI + 0x13c),param_1);
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 < 0x10);
  }
  return;
}

