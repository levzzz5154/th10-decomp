/* Raw Ghidra reference; not compilable reconstruction. Address: 0040CC50 */

void * __thiscall DestroyBullet(void *this,byte param_1)

{
  FUN_0040dae0(this);
  if ((param_1 & 1) != 0) {
    _free(this);
  }
  return this;
}

