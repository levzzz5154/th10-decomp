/* Raw Ghidra reference; not compilable reconstruction. Address: 0044CF00 */

undefined4 * __thiscall DestroyPlatformCollection(void *this,byte param_1)

{
  ReleasePlatformOwnedArray(this);
  if ((param_1 & 1) != 0) {
    _free(this);
  }
  return this;
}

