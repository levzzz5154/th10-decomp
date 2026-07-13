/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0044D710
 * Tracking name: FUN_0044d710
 * Ghidra name: FUN_0044d710
 * Tracked span: 32 bytes
 */


undefined4 * __thiscall FUN_0044d710(void *this,byte param_1)

{
  FUN_0044d730(this);
  if ((param_1 & 1) != 0) {
    _free(this);
  }
  return this;
}

