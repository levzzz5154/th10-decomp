/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0040C6E0
 * Tracking name: FUN_0040c6e0
 * Ghidra name: FUN_0040c6e0
 * Tracked span: 80 bytes
 */


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

