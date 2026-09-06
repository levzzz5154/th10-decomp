/* Raw Ghidra reference; not compilable reconstruction. Address: 00462DBD */

exception * __thiscall FUN_00462dbd(void *this,byte param_1)

{
  FUN_00462d00(this);
  if ((param_1 & 1) != 0) {
    _free(this);
  }
  return this;
}

