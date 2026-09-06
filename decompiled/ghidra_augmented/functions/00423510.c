/* Raw Ghidra reference; not compilable reconstruction. Address: 00423510 */

void FUN_00423510(void)

{
  undefined4 extraout_ECX;
  int unaff_ESI;
  
  *(undefined4 *)(unaff_ESI + 4) = 0xd;
  if ((*(uint *)(unaff_ESI + 0x20) & 1) == 0) {
    *(undefined4 *)(unaff_ESI + 0x14) = 0;
    *(undefined4 *)(unaff_ESI + 0x10) = 0xfff0bdc1;
    *(undefined4 *)(unaff_ESI + 0x18) = 0;
    *(undefined4 **)(unaff_ESI + 0x1c) = &DAT_00476f78;
    *(uint *)(unaff_ESI + 0x20) = *(uint *)(unaff_ESI + 0x20) | 1;
  }
  *(undefined4 *)(unaff_ESI + 0x14) = 0;
  *(undefined4 *)(unaff_ESI + 0x18) = 0;
  *(undefined4 *)(unaff_ESI + 0x10) = 0xffffffff;
  FUN_00409e50(0);
  FUN_00409e50(extraout_ECX);
  DAT_00476f78 = *(undefined4 *)(unaff_ESI + 0x2c0);
  return;
}

