/* Raw Ghidra reference; not compilable reconstruction. Address: 0044D710 */

void * __thiscall DestroyPlatformVtable(void *this,byte param_1)

{
  FUN_0044d730(this);
  if ((param_1 & 1) != 0) {
    _free(this);
  }
  return this;
}

