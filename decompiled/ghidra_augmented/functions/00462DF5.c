/* Raw Ghidra reference; not compilable reconstruction. Address: 00462DF5 */

void * __thiscall FUN_00462df5(void *this,byte param_1)

{
  FUN_00462d77(this);
  if ((param_1 & 1) != 0) {
    _free(this);
  }
  return this;
}

