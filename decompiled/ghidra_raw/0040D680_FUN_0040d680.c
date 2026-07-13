/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0040D680
 * Tracking name: FUN_0040d680
 * Ghidra name: FUN_0040d680
 * Tracked span: 48 bytes
 */


void FUN_0040d680(void)

{
  undefined4 *unaff_ESI;
  
  *unaff_ESI = &PTR_FUN_0046d0f0;
  if ((void *)unaff_ESI[0x23] != (void *)0x0) {
    _free((void *)unaff_ESI[0x23]);
    unaff_ESI[0x23] = 0;
  }
  return;
}

