/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0044C100
 * Tracking name: FUN_0044c100
 * Ghidra name: FUN_0044c100
 * Tracked span: 48 bytes
 */


undefined4 * __thiscall FUN_0044c100(void *this,byte param_1)

{
  *(undefined ***)this = &PTR_FUN_004703e4;
  FUN_0044c150();
  if ((param_1 & 1) != 0) {
    _free(this);
  }
  return this;
}

