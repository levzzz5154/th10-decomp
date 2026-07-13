/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00408910
 * Tracking name: FUN_00408910
 * Ghidra name: FUN_00408910
 * Tracked span: 176 bytes
 */


uint * FUN_00408910(uint *param_1)

{
  int iVar1;
  uint *puVar2;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_00465514;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  _eh_vector_constructor_iterator_(param_1 + 4,0x3ac,2,FUN_00402050,FUN_00401ff0);
  local_4 = 0;
  _eh_vector_constructor_iterator_(param_1 + 0x1de,0x3ac,8,FUN_00402050,FUN_00401ff0);
  local_4 = CONCAT31(local_4._1_3_,1);
  _eh_vector_constructor_iterator_(param_1 + 0x936,0x3ac,5,FUN_00402050,FUN_00401ff0);
  param_1[0xdd1] = param_1[0xdd1] & 0xfffffffe;
  puVar2 = param_1;
  for (iVar1 = 0xdec; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  *param_1 = *param_1 | 2;
  DAT_004776f4 = param_1;
  ExceptionList = local_c;
  return param_1;
}

