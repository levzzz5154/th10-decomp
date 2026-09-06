/* Raw Ghidra reference; not compilable reconstruction. Address: 00462DD9 */

exception * __thiscall FUN_00462dd9(void *this,byte param_1)

{
  FUN_00462d3c(this);
  if ((param_1 & 1) != 0) {
    _free(this);
  }
  return this;
}

