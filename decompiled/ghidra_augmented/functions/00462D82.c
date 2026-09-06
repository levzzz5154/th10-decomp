/* Raw Ghidra reference; not compilable reconstruction. Address: 00462D82 */

void * __thiscall FUN_00462d82(void *this,byte param_1)

{
  exception::~exception(this);
  if ((param_1 & 1) != 0) {
    _free(this);
  }
  return this;
}

