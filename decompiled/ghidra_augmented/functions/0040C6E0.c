/* Raw Ghidra reference; not compilable reconstruction. Address: 0040C6E0 */

void FUN_0040c6e0(void)

{
  undefined4 *puVar1;
  undefined4 *_Memory;
  int in_EAX;
  
  _Memory = *(undefined4 **)(in_EAX + 0x1034);
  while (_Memory != (undefined4 *)0x0) {
    puVar1 = (undefined4 *)_Memory[1];
    _free((void *)*_Memory);
    _free(_Memory);
    _Memory = puVar1;
  }
  return;
}

