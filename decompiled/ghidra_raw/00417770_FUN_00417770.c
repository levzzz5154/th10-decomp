/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00417770
 * Tracking name: FUN_00417770
 * Ghidra name: FUN_00417770
 * Tracked span: 144 bytes
 */


void FUN_00417770(void)

{
  int *piVar1;
  int *_Memory;
  int in_EAX;
  
  _Memory = *(int **)(in_EAX + 0x18);
  while (_Memory != (int *)0x0) {
    piVar1 = (int *)_Memory[2];
    (**(code **)(*_Memory + 0x10))();
    *(int *)(_Memory[1] + 8) = _Memory[2];
    if (_Memory[2] != 0) {
      *(int *)(_Memory[2] + 4) = _Memory[1];
    }
    _free(_Memory);
    _Memory = piVar1;
  }
  return;
}

