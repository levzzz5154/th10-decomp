/* Raw Ghidra reference; not compilable reconstruction. Address: 0043A730 */

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

