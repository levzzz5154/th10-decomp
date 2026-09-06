/* Raw Ghidra reference; not compilable reconstruction. Address: 00436660 */

void * __thiscall FUN_00436660(void *this,byte param_1)

{
  FUN_00436680(this);
  if ((param_1 & 1) != 0) {
    _free(this);
  }
  return this;
}

