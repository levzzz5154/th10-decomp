/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00401440
 * Tracking name: FUN_00401440
 * Ghidra name: FUN_00401440
 * Tracked span: 224 bytes
 */


undefined4 * FUN_00401440(void)

{
  void *pvVar1;
  undefined4 *_Memory;
  int iVar2;
  
  pvVar1 = operator_new(0x89ac);
  if (pvVar1 == (void *)0x0) {
    _Memory = (undefined4 *)0x0;
  }
  else {
    _Memory = (undefined4 *)FUN_00401000();
  }
  iVar2 = FUN_00401110();
  if (iVar2 != 0) {
    if (_Memory != (undefined4 *)0x0) {
      FUN_00401260(_Memory);
      _free(_Memory);
    }
    return (undefined4 *)0x0;
  }
  return _Memory;
}

