/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00417010
 * Tracking name: FUN_00417010
 * Ghidra name: FUN_00417010
 * Tracked span: 48 bytes
 */


undefined1 * FUN_00417010(void)

{
  byte bVar1;
  byte *in_EAX;
  byte bVar2;
  char cVar3;
  byte *pbVar4;
  
  cVar3 = '\a';
  pbVar4 = &DAT_00497d40;
  bVar2 = 0x77;
  do {
    bVar1 = *in_EAX ^ bVar2;
    *pbVar4 = bVar1;
    pbVar4 = pbVar4 + 1;
    bVar2 = bVar2 + cVar3;
    in_EAX = in_EAX + 1;
    cVar3 = cVar3 + '\x10';
  } while (bVar1 != 0);
  return &DAT_00497d40;
}

