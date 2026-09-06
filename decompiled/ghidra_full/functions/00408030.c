/* Raw Ghidra reference; not compilable reconstruction. Address: 00408030 */

undefined4 FUN_00408030(void)

{
  int iVar1;
  uint *unaff_ESI;
  
  if ((*(short *)((int)unaff_ESI + 0x446) != 2) && (*(short *)((int)unaff_ESI + 0x446) != 1)) {
    return 0;
  }
  iVar1 = FUN_004086b0(unaff_ESI + 0xed,8.0,8.0);
  *(undefined2 *)(unaff_ESI + 0xc3) = 1;
  *(undefined2 *)((int)unaff_ESI + 0x446) = 3;
  if (iVar1 == 0) {
    if (-1 < (int)unaff_ESI[0x10e]) {
      FUN_00448db0(*(undefined2 **)(DAT_004776f0 + 0x3e0b50));
    }
    if ((unaff_ESI[0x102] & 1) == 0) {
      unaff_ESI[0xff] = 0;
      unaff_ESI[0xfe] = 0xfff0bdc1;
      unaff_ESI[0x100] = 0;
      unaff_ESI[0x101] = (uint)&DAT_00476f78;
      unaff_ESI[0x102] = unaff_ESI[0x102] | 1;
    }
    unaff_ESI[0xff] = 0;
    unaff_ESI[0x100] = 0;
    unaff_ESI[0xfe] = 0xffffffff;
    return 1;
  }
  *unaff_ESI = *unaff_ESI | 8;
  return 1;
}

