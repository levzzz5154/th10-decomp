/* Raw Ghidra reference; not compilable reconstruction. Address: 00404530 */

void FUN_00404530(void)

{
  int unaff_ESI;
  
  FUN_0043c8b0(2,0x1e,0,0,0);
  if ((*(uint *)(unaff_ESI + 0x2a2c) & 1) == 0) {
    *(undefined4 *)(unaff_ESI + 0x2a20) = 0;
    *(undefined4 *)(unaff_ESI + 0x2a1c) = 0xfff0bdc1;
    *(undefined4 *)(unaff_ESI + 0x2a24) = 0;
    *(undefined4 **)(unaff_ESI + 0x2a28) = &DAT_00476f78;
    *(uint *)(unaff_ESI + 0x2a2c) = *(uint *)(unaff_ESI + 0x2a2c) | 1;
  }
  *(undefined4 *)(unaff_ESI + 0x2a20) = 0x1e;
  *(undefined4 *)(unaff_ESI + 0x2a24) = 0x41f00000;
  *(undefined4 *)(unaff_ESI + 0x2a1c) = 0x1d;
  *(uint *)(unaff_ESI + 0x2a18) = *(uint *)(unaff_ESI + 0x2a18) | 2;
  return;
}

