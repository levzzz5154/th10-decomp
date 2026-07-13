/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0041AED0
 * Tracking name: FUN_0041aed0
 * Ghidra name: FUN_0041aed0
 * Tracked span: 256 bytes
 */


uint * FUN_0041aed0(void)

{
  uint *_Memory;
  int iVar1;
  uint *puVar2;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0046580b;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  _Memory = operator_new(0x21cec0);
  local_4 = 0;
  if (_Memory == (uint *)0x0) {
    _Memory = (uint *)0x0;
  }
  else {
    _eh_vector_constructor_iterator_
              (_Memory + 5,0x3f0,0x896,(_func_void_void_ptr *)&LAB_0041acf0,FUN_0041ad60);
    puVar2 = _Memory;
    for (iVar1 = 0x873b0; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar2 = 0;
      puVar2 = puVar2 + 1;
    }
    *_Memory = *_Memory | 2;
    DAT_00477818 = _Memory;
  }
  local_4 = 0xffffffff;
  iVar1 = FUN_0041ad90();
  if (iVar1 != 0) {
    if (_Memory != (uint *)0x0) {
      FUN_0041adf0((int)_Memory);
      _free(_Memory);
    }
    ExceptionList = local_c;
    return (uint *)0x0;
  }
  ExceptionList = local_c;
  return _Memory;
}

