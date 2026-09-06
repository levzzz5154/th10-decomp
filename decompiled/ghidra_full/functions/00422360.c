/* Raw Ghidra reference; not compilable reconstruction. Address: 00422360 */

uint * FUN_00422360(void)

{
  uint *puVar1;
  int iVar2;
  undefined4 extraout_ECX;
  
  puVar1 = operator_new(0x2c8);
  if (puVar1 == (uint *)0x0) {
    puVar1 = (uint *)0x0;
  }
  else {
    puVar1 = InitializeTimerState(extraout_ECX,puVar1);
  }
  iVar2 = FUN_00422150();
  if (iVar2 != 0) {
    if (puVar1 != (uint *)0x0) {
      FUN_00422220((int)puVar1);
      _free(puVar1);
    }
    return (uint *)0x0;
  }
  return puVar1;
}

