/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x004297B0
 * Tracking name: FUN_004297b0
 * Ghidra name: FUN_004297b0
 * Tracked span: 32 bytes
 */


void FUN_004297b0(void)

{
  void *unaff_ESI;
  
  if (unaff_ESI != (void *)0x0) {
    FUN_004294a0((int)unaff_ESI);
    _free(unaff_ESI);
  }
  return;
}

