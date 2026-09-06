/* Raw Ghidra reference; not compilable reconstruction. Address: 00408C90 */

uint * FUN_00408c90(void)

{
  uint *puVar1;
  int iVar2;
  void *this;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0046586b;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  puVar1 = operator_new(0x37b0);
  local_4 = 0;
  if (puVar1 == (uint *)0x0) {
    puVar1 = (uint *)0x0;
  }
  else {
    puVar1 = FUN_00408910(puVar1);
  }
  local_4 = 0xffffffff;
  iVar2 = FUN_004089c0();
  if (iVar2 != 0) {
    if (puVar1 != (uint *)0x0) {
      FUN_00408af0(this,(int)puVar1);
      _free(puVar1);
    }
    ExceptionList = local_c;
    return (uint *)0x0;
  }
  ExceptionList = local_c;
  return puVar1;
}

