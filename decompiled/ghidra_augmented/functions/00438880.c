/* Raw Ghidra reference; not compilable reconstruction. Address: 00438880 */

void FUN_00438880(int param_1)

{
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_00465363;
  local_c = ExceptionList;
  local_4 = 1;
  ExceptionList = &local_c;
  FUN_0044c150();
  FUN_00449e50(param_1);
  FUN_00449e50(param_1);
  *(undefined4 *)(param_1 + 0x2c) = 0;
  *(undefined4 *)(param_1 + 0x30) = 0;
  *(undefined4 *)(param_1 + 0x34) = 0;
  *(undefined4 *)(param_1 + 8) = 0;
  *(undefined4 *)(param_1 + 0xc) = 0;
  *(undefined4 *)(param_1 + 0x10) = 0;
  ExceptionList = local_c;
  return;
}

