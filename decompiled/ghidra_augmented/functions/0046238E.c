/* Raw Ghidra reference; not compilable reconstruction. Address: 0046238E */

void * __thiscall FUN_0046238e(void *this,byte param_1)

{
  FUN_00462371(this);
  if ((param_1 & 1) != 0) {
    _free(this);
  }
  return this;
}

