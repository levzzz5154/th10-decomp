/* Raw Ghidra reference; not compilable reconstruction. Address: 00417770 */

void CleanupLinkedResources(void)

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

