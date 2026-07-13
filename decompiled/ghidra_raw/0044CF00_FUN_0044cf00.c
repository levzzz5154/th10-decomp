/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0044CF00
 * Tracking name: FUN_0044cf00
 * Ghidra name: FUN_0044cf00
 * Tracked span: 32 bytes
 */


undefined4 * __thiscall FUN_0044cf00(void *this,byte param_1)

{
  FUN_0044d080(this);
  if ((param_1 & 1) != 0) {
    _free(this);
  }
  return this;
}

