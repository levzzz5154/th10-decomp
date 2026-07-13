/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00402640
 * Tracking name: FUN_00402640
 * Ghidra name: FUN_00402640
 * Tracked span: 224 bytes
 */


uint * FUN_00402640(void *param_1,int param_2)

{
  uint *puVar1;
  int iVar2;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0046588b;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  puVar1 = operator_new(0x2b64);
  local_4 = 0;
  if (puVar1 == (uint *)0x0) {
    puVar1 = (uint *)0x0;
  }
  else {
    puVar1 = FUN_00402160(puVar1);
  }
  local_4 = 0xffffffff;
  iVar2 = FUN_00402230(param_1,param_2);
  if (iVar2 != 0) {
    if (puVar1 != (uint *)0x0) {
      FUN_00402440((int)puVar1);
      _free(puVar1);
    }
    ExceptionList = local_c;
    return (uint *)0x0;
  }
  ExceptionList = local_c;
  return puVar1;
}

