/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00418810
 * Tracking name: FUN_00418810
 * Ghidra name: FUN_00418810
 * Tracked span: 144 bytes
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined * FUN_00418810(void)

{
  float *in_EAX;
  
  if ((_DAT_00497d8c & 1) == 0) {
    _DAT_00497d8c = _DAT_00497d8c | 1;
  }
  _DAT_00497d80 = *in_EAX + _DAT_00470b4c;
  _DAT_00497d84 = in_EAX[1] + _DAT_00470b48;
  _DAT_00497d88 = in_EAX[2];
  return &DAT_00497d80;
}

