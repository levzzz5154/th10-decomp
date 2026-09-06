/* Raw Ghidra reference; not compilable reconstruction. Address: 0040A3C0 */

uint * FUN_0040a3c0(void)

{
  uint *puVar1;
  int iVar2;
  undefined4 extraout_ECX;
  
  puVar1 = operator_new(0x688);
  if (puVar1 == (uint *)0x0) {
    puVar1 = (uint *)0x0;
  }
  else {
    puVar1 = FUN_0040a040(extraout_ECX,puVar1);
  }
  iVar2 = FUN_0040a130();
  if (iVar2 != 0) {
    if (puVar1 != (uint *)0x0) {
      FUN_0040a1a0((int)puVar1);
      _free(puVar1);
    }
    return (uint *)0x0;
  }
  return puVar1;
}

