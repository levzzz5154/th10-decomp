/* Raw Ghidra reference; not compilable reconstruction. Address: 00429610 */

undefined4 * FUN_00429610(undefined4 param_1,char *param_2)

{
  undefined4 *_Memory;
  int iVar1;
  undefined4 *puVar2;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0046566b;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  _Memory = operator_new(0x2d4);
  local_4 = 0;
  if (_Memory == (undefined4 *)0x0) {
    _Memory = (undefined4 *)0x0;
  }
  else {
    _eh_vector_constructor_iterator_(_Memory + 0x28,0x24,8,FUN_0042ac20,FUN_0042ac60);
    puVar2 = _Memory;
    for (iVar1 = 0xb5; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar2 = 0;
      puVar2 = puVar2 + 1;
    }
  }
  local_4 = 0xffffffff;
  iVar1 = FUN_00428f60(param_2);
  if (iVar1 == 0) {
    ExceptionList = local_c;
    return _Memory;
  }
  if (_Memory != (undefined4 *)0x0) {
    FUN_004294a0((int)_Memory);
    _free(_Memory);
  }
  ExceptionList = local_c;
  return (undefined4 *)0x0;
}

