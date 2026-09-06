/* Raw Ghidra reference; not compilable reconstruction. Address: 00419090 */

uint * FUN_00419090(void)

{
  uint *puVar1;
  int iVar2;
  undefined4 extraout_ECX;
  
  puVar1 = operator_new(0x1a8);
  if (puVar1 == (uint *)0x0) {
    puVar1 = (uint *)0x0;
  }
  else {
    puVar1 = FUN_00418d40(extraout_ECX,puVar1);
  }
  iVar2 = FUN_00418e30();
  if (iVar2 != 0) {
    if (puVar1 != (uint *)0x0) {
      FUN_00418ee0((int)puVar1);
      _free(puVar1);
    }
    return (uint *)0x0;
  }
  return puVar1;
}

