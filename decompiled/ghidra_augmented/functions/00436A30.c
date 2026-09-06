/* Raw Ghidra reference; not compilable reconstruction. Address: 00436A30 */

undefined4 FUN_00436a30(void)

{
  BOOL BVar1;
  int unaff_ESI;
  
  if (*(HDC *)(unaff_ESI + 0x114) != (HDC)0x0) {
    SelectObject(*(HDC *)(unaff_ESI + 0x114),*(HGDIOBJ *)(unaff_ESI + 0x118));
    DeleteDC(*(HDC *)(unaff_ESI + 0x114));
    BVar1 = DeleteObject(*(HGDIOBJ *)(unaff_ESI + 0x11c));
    *(undefined4 *)(unaff_ESI + 0x104) = 0;
    *(undefined4 *)(unaff_ESI + 0x108) = 0;
    *(undefined4 *)(unaff_ESI + 0x114) = 0;
    *(undefined4 *)(unaff_ESI + 0x11c) = 0;
    *(undefined4 *)(unaff_ESI + 0x118) = 0;
    *(undefined4 *)(unaff_ESI + 0x120) = 0;
    *(undefined4 *)(unaff_ESI + 0x100) = 0xffffffff;
    return CONCAT31((int3)((uint)BVar1 >> 8),1);
  }
  return 0;
}

