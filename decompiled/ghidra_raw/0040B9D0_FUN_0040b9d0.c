/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0040B9D0
 * Tracking name: FUN_0040b9d0
 * Ghidra name: FUN_0040b9d0
 * Tracked span: 32 bytes
 */


void FUN_0040b9d0(void)

{
  void *unaff_ESI;
  
  if (unaff_ESI != (void *)0x0) {
    FUN_0040b7b0((int)unaff_ESI);
    _free(unaff_ESI);
  }
  return;
}

