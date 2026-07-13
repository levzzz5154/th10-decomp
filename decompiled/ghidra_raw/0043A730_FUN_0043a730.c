/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0043A730
 * Tracking name: FUN_0043a730
 * Ghidra name: FUN_0043a730
 * Tracked span: 480 bytes
 */


int FUN_0043a730(void)

{
  byte bVar1;
  int iVar2;
  undefined4 *unaff_ESI;
  
  iVar2 = 0;
  do {
    bVar1 = *(byte *)*unaff_ESI;
    *unaff_ESI = (byte *)*unaff_ESI + 1;
    iVar2 = iVar2 * 0x80 + (bVar1 & 0x7f);
  } while ((char)bVar1 < '\0');
  return iVar2;
}

