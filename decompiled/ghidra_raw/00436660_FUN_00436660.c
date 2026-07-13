/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00436660
 * Tracking name: FUN_00436660
 * Ghidra name: FUN_00436660
 * Tracked span: 32 bytes
 */


undefined4 * __thiscall FUN_00436660(void *this,byte param_1)

{
  FUN_00436680(this);
  if ((param_1 & 1) != 0) {
    _free(this);
  }
  return this;
}

