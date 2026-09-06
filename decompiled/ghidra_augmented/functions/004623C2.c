/* Raw Ghidra reference; not compilable reconstruction. Address: 004623C2 */

void * __thiscall FUN_004623c2(void *this,byte param_1)

{
  FUN_004623de(this);
  if ((param_1 & 1) != 0) {
    _free(this);
  }
  return this;
}

