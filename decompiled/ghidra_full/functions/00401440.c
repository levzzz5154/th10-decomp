/* Raw Ghidra reference; not compilable reconstruction. Address: 00401440 */

undefined4 * CreateGameThread(void)

{
  void *pvVar1;
  undefined4 *_Memory;
  int iVar2;
  
  pvVar1 = operator_new(0x89ac);
  if (pvVar1 == (void *)0x0) {
    _Memory = (undefined4 *)0x0;
  }
  else {
    _Memory = (undefined4 *)ConstructGameThread();
  }
  iVar2 = LoadGameThreadResources();
  if (iVar2 != 0) {
    if (_Memory != (undefined4 *)0x0) {
      DestroyGameThread(_Memory);
      _free(_Memory);
    }
    return (undefined4 *)0x0;
  }
  return _Memory;
}

