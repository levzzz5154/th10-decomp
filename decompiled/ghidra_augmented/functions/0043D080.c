/* Raw Ghidra reference; not compilable reconstruction. Address: 0043D080 */

void FUN_0043d080(void)

{
  byte *pbVar1;
  int iVar2;
  
  iVar2 = 0;
  while( true ) {
    if (DAT_004977b4 == 2) {
      return;
    }
    pbVar1 = FUN_0044b360((size_t *)0x0,0);
    (&DAT_004977c0)[iVar2] = pbVar1;
    if (pbVar1 == (byte *)0x0) break;
    iVar2 = iVar2 + 1;
    if (0x24 < iVar2) {
      while (DAT_004977b4 == 0) {
        Sleep(1);
      }
      return;
    }
  }
  FUN_0044b810(&DAT_00474f70,&DAT_0046fdd4);
  return;
}

