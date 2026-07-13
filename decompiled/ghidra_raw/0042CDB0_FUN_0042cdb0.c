/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0042CDB0
 * Tracking name: FUN_0042cdb0
 * Ghidra name: FUN_0042cdb0
 * Tracked span: 64 bytes
 */


void FUN_0042cdb0(void)

{
  undefined4 *unaff_ESI;
  
  if (unaff_ESI != (undefined4 *)0x0) {
    FUN_0042cb60(unaff_ESI);
    _free(unaff_ESI);
  }
  return;
}

