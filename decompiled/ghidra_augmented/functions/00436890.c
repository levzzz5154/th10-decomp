/* Raw Ghidra reference; not compilable reconstruction. Address: 00436890 */

undefined4 * FUN_00436890(undefined4 *param_1)

{
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_0046558b;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  param_1[9] = 0xf;
  param_1[8] = 0;
  *(undefined1 *)(param_1 + 4) = 0;
  local_4 = 0;
  *param_1 = 0;
  param_1[10] = 600;
  param_1[2] = 0x10;
  param_1[1] = 0;
  FUN_00438420(param_1 + 3,(undefined4 *)&DAT_0046f36c,0xd);
  ExceptionList = local_c;
  return param_1;
}

