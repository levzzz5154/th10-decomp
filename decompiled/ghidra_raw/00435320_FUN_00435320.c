/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00435320
 * Tracking name: FUN_00435320
 * Ghidra name: FUN_00435320
 * Tracked span: 32 bytes
 */


undefined4 * __thiscall FUN_00435320(void *this,byte param_1)

{
  FUN_00435340(this);
  if ((param_1 & 1) != 0) {
    _free(this);
  }
  return this;
}

