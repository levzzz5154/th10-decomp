/* Raw Ghidra reference; not compilable reconstruction. Address: 00435320 */

undefined4 * __thiscall FUN_00435320(void *this,byte param_1)

{
  FUN_00435340(this);
  if ((param_1 & 1) != 0) {
    _free(this);
  }
  return this;
}

