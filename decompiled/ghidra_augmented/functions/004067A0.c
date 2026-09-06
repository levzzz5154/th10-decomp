/* Raw Ghidra reference; not compilable reconstruction. Address: 004067A0 */

undefined4 FUN_004067a0(void)

{
  int iVar1;
  
  if ((DAT_00477810 == 0) || ((*(byte *)(DAT_00477810 + 0x58) & 4) == 0)) {
    iVar1 = 0;
    do {
      FUN_004066e0(iVar1);
      iVar1 = iVar1 + 1;
    } while (iVar1 < 6);
  }
  return 1;
}

