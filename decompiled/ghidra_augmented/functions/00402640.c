/* Raw Ghidra reference; not compilable reconstruction. Address: 00402640 */

uint * CreateGameState(void *param_1,int param_2)

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
    puVar1 = ConstructGameState(puVar1);
  }
  local_4 = 0xffffffff;
  iVar2 = InitializeGameState(param_1,param_2);
  if (iVar2 != 0) {
    if (puVar1 != (uint *)0x0) {
      DestroyGameState((int)puVar1);
      _free(puVar1);
    }
    ExceptionList = local_c;
    return (uint *)0x0;
  }
  ExceptionList = local_c;
  return puVar1;
}

