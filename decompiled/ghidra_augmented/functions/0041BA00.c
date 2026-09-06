/* Raw Ghidra reference; not compilable reconstruction. Address: 0041BA00 */

undefined4 __fastcall FUN_0041ba00(int param_1)

{
  uint uVar1;
  undefined4 uVar2;
  
  if ((DAT_00477810 != 0) &&
     ((uVar1 = *(uint *)(DAT_00477810 + 0x58), ((uVar1 >> 2 | uVar1) & 1) != 0 ||
      ((uVar1 & 0x400) != 0)))) {
    return 1;
  }
  uVar2 = FUN_0041afd0(param_1);
  return uVar2;
}

