/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0040CC50
 * Tracking name: FUN_0040cc50
 * Ghidra name: FUN_0040cc50
 * Tracked span: 32 bytes
 */


undefined4 * __thiscall FUN_0040cc50(void *this,byte param_1)

{
  FUN_0040dae0(this);
  if ((param_1 & 1) != 0) {
    _free(this);
  }
  return this;
}

