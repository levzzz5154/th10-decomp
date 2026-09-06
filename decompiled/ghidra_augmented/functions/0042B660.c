/* Raw Ghidra reference; not compilable reconstruction. Address: 0042B660 */

void * FUN_0042b660(void)

{
  void *pvVar1;
  int iVar2;
  
  pvVar1 = operator_new(0xb884);
  if (pvVar1 == (void *)0x0) {
    pvVar1 = (void *)0x0;
  }
  else {
    pvVar1 = (void *)FUN_0042b430();
  }
  iVar2 = FUN_0042b4d0();
  if (iVar2 != 0) {
    if (pvVar1 != (void *)0x0) {
      FUN_0042b570((int)pvVar1);
      _free(pvVar1);
    }
    return (void *)0x0;
  }
  return pvVar1;
}

