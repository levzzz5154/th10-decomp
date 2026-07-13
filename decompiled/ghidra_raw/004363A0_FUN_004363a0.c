/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x004363A0
 * Tracking name: FUN_004363a0
 * Ghidra name: FUN_004363a0
 * Tracked span: 32 bytes
 */


undefined4 * __thiscall FUN_004363a0(void *this,byte param_1)

{
  FUN_004363c0(this);
  if ((param_1 & 1) != 0) {
    _free(this);
  }
  return this;
}

