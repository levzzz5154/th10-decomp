/* Raw Ghidra reference; not compilable reconstruction. Address: 004363A0 */

undefined4 * __thiscall FUN_004363a0(void *this,byte param_1)

{
  FUN_004363c0(this);
  if ((param_1 & 1) != 0) {
    _free(this);
  }
  return this;
}

