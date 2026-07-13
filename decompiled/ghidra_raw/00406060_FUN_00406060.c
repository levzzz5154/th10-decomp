/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00406060
 * Tracking name: FUN_00406060
 * Ghidra name: FUN_00406060
 * Tracked span: 256 bytes
 */


undefined4 * FUN_00406060(void)

{
  undefined4 *_Memory;
  int iVar1;
  undefined4 *puVar2;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_004658ab;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  _Memory = operator_new(0x3e0b54);
  local_4 = 0;
  if (_Memory == (undefined4 *)0x0) {
    _Memory = (undefined4 *)0x0;
  }
  else {
    _eh_vector_constructor_iterator_(_Memory + 0x18,0x7f0,0x7d1,FUN_00405d00,FUN_00405de0);
    puVar2 = _Memory;
    for (iVar1 = 0xf82d5; DAT_004776f0 = _Memory, iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar2 = 0;
      puVar2 = puVar2 + 1;
    }
  }
  local_4 = 0xffffffff;
  iVar1 = FUN_00405e20();
  if (iVar1 == 0) {
    ExceptionList = local_c;
    return _Memory;
  }
  if (_Memory != (undefined4 *)0x0) {
    FUN_00405f70((int)_Memory);
    _free(_Memory);
  }
  ExceptionList = local_c;
  return (undefined4 *)0x0;
}

