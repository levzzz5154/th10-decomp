/* Raw Ghidra reference; not compilable reconstruction. Address: 0041C480 */

undefined4 FUN_0041c480(void)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  uVar3 = DAT_00476f78;
  uVar1 = *(uint *)(DAT_00477810 + 0x58);
  if ((((uVar1 >> 2 | uVar1) & 1) == 0) && ((uVar1 & 0x400) == 0)) {
    if ((uVar1 & 2) != 0) {
      DAT_00476f78 = 0;
      uVar2 = FUN_0041c330();
      DAT_00476f78 = uVar3;
      return uVar2;
    }
    uVar3 = FUN_0041c330();
    return uVar3;
  }
  return 1;
}

