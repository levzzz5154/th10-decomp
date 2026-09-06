/* Raw Ghidra reference; not compilable reconstruction. Address: 00406770 */

undefined4 FUN_00406770(void)

{
  undefined4 uVar1;
  float *in_ECX;
  float in_EDX;
  
  if ((DAT_00477810 != 0) &&
     (in_EDX = (float)(*(uint *)(DAT_00477810 + 0x58) >> 2 | *(uint *)(DAT_00477810 + 0x58)),
     ((uint)in_EDX & 1) != 0)) {
    return 1;
  }
  uVar1 = FUN_004065c0(in_ECX,in_EDX);
  return uVar1;
}

