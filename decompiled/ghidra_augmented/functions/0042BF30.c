/* Raw Ghidra reference; not compilable reconstruction. Address: 0042BF30 */

uint * FUN_0042bf30(void)

{
  uint *puVar1;
  int iVar2;
  undefined4 extraout_ECX;
  
  puVar1 = operator_new(0x2e4);
  if (puVar1 == (uint *)0x0) {
    puVar1 = (uint *)0x0;
  }
  else {
    puVar1 = FUN_0042bb30(extraout_ECX,puVar1);
  }
  iVar2 = FUN_0042bbd0();
  if (iVar2 != 0) {
    if (puVar1 != (uint *)0x0) {
      FUN_0042bc30((int)puVar1);
      _free(puVar1);
    }
    return (uint *)0x0;
  }
  return puVar1;
}

