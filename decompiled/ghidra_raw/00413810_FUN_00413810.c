/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00413810
 * Tracking name: FUN_00413810
 * Ghidra name: FUN_00413810
 * Tracked span: 368 bytes
 */


uint * FUN_00413810(uint *param_1)

{
  int iVar1;
  uint *puVar2;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_004654b5;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  _eh_vector_constructor_iterator_(param_1 + 4,0x3ac,10,FUN_00402050,FUN_00401ff0);
  local_4 = 0;
  _eh_vector_constructor_iterator_(param_1 + 0x932,0x3ac,10,FUN_00402050,FUN_00401ff0);
  local_4._0_1_ = 1;
  _eh_vector_constructor_iterator_(param_1 + 0x1260,0x3ac,9,FUN_00402050,FUN_00401ff0);
  local_4._0_1_ = 2;
  _eh_vector_constructor_iterator_(param_1 + 0x1aa3,0x3ac,4,FUN_00402050,FUN_00401ff0);
  local_4._0_1_ = 3;
  _eh_vector_constructor_iterator_(param_1 + 0x1e4f,0x3ac,2,FUN_00402050,FUN_00401ff0);
  local_4 = CONCAT31(local_4._1_3_,4);
  _eh_vector_constructor_iterator_(param_1 + 0x2025,0x3ac,7,FUN_00402050,FUN_00401ff0);
  param_1[0x26ad] = param_1[0x26ad] & 0xfffffffe;
  param_1[0x26be] = param_1[0x26be] & 0xfffffffe;
  param_1[0x26d1] = param_1[0x26d1] & 0xfffffffe;
  param_1[0x26dc] = param_1[0x26dc] & 0xfffffffe;
  param_1[0x26ef] = param_1[0x26ef] & 0xfffffffe;
  param_1[0x26fe] = param_1[0x26fe] & 0xfffffffe;
  param_1[0x2711] = param_1[0x2711] & 0xfffffffe;
  param_1[0x271c] = param_1[0x271c] & 0xfffffffe;
  param_1[0x2770] = param_1[0x2770] & 0xfffffffe;
  puVar2 = param_1 + 0x2692;
  for (iVar1 = 0xeb; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  *(undefined2 *)(param_1 + 0x2773) = 0xffff;
  param_1[0x279c] = param_1[0x279c] & 0xfffffffe;
  puVar2 = param_1;
  for (iVar1 = 0x27b4; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  *param_1 = *param_1 | 2;
  DAT_0047770c = param_1;
  ExceptionList = local_c;
  return param_1;
}

