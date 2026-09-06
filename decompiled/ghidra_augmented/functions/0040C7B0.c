/* Raw Ghidra reference; not compilable reconstruction. Address: 0040C7B0 */

void * __thiscall FUN_0040c7b0(void *this,byte param_1)

{
  undefined4 *puVar1;
  undefined4 *_Memory;
  
  *(undefined ***)this = &PTR_FUN_0046d0d8;
  _Memory = *(undefined4 **)((int)this + 0x1034);
  while (_Memory != (undefined4 *)0x0) {
    puVar1 = (undefined4 *)_Memory[1];
    _free((void *)*_Memory);
    _free(_Memory);
    _Memory = puVar1;
  }
  if ((param_1 & 1) != 0) {
    _free(this);
  }
  return this;
}

