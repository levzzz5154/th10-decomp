/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00418150
 * Tracking name: FUN_00418150
 * Ghidra name: FUN_00418150
 * Tracked span: 64 bytes
 */


void FUN_00418150(void)

{
  void *unaff_ESI;
  
  if (unaff_ESI != (void *)0x0) {
    FUN_00417c80((int)unaff_ESI);
    _free(unaff_ESI);
  }
  return;
}

