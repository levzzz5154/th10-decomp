/* Raw Ghidra reference; not compilable reconstruction. Address: 00462401 */

void * __thiscall FUN_00462401(void *this,byte param_1)

{
  FUN_0046241d(this);
  if ((param_1 & 1) != 0) {
    _free(this);
  }
  return this;
}

