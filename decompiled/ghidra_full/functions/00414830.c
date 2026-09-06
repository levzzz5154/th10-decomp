/* Raw Ghidra reference; not compilable reconstruction. Address: 00414830 */

uint * FUN_00414830(void)

{
  uint *puVar1;
  int iVar2;
  void *this;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0046584b;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  puVar1 = operator_new(0x9ed0);
  local_4 = 0;
  if (puVar1 == (uint *)0x0) {
    puVar1 = (uint *)0x0;
  }
  else {
    puVar1 = FUN_00413810(puVar1);
  }
  local_4 = 0xffffffff;
  iVar2 = FUN_00413980();
  if (iVar2 != 0) {
    if (puVar1 != (uint *)0x0) {
      FUN_004145f0(this,(int)puVar1);
      _free(puVar1);
    }
    ExceptionList = local_c;
    return (uint *)0x0;
  }
  ExceptionList = local_c;
  return puVar1;
}

