/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00402160
 * Tracking name: FUN_00402160
 * Ghidra name: FUN_00402160
 * Tracked span: 208 bytes
 */


uint * FUN_00402160(uint *param_1)

{
  int iVar1;
  uint *puVar2;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0046556b;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  param_1[0xd] = param_1[0xd] & 0xfffffffe;
  param_1[0x12] = param_1[0x12] & 0xfffffffe;
  param_1[0x24] = param_1[0x24] & 0xfffffffe;
  param_1[0x37] = param_1[0x37] & 0xfffffffe;
  param_1[0x5a] = param_1[0x5a] & 0xfffffffe;
  _eh_vector_constructor_iterator_(param_1 + 0x60,0x3ac,8,FUN_00402050,FUN_00401ff0);
  local_4 = 0;
  _eh_vector_constructor_iterator_(param_1 + 0x7c2,0x3ac,3,FUN_00402050,FUN_00401ff0);
  param_1[0xa8b] = param_1[0xa8b] & 0xfffffffe;
  puVar2 = param_1;
  for (iVar1 = 0xad9; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  *param_1 = *param_1 | 2;
  ExceptionList = local_c;
  return param_1;
}

