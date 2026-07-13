/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0041FD00
 * Tracking name: FUN_0041fd00
 * Ghidra name: FUN_0041fd00
 * Tracked span: 208 bytes
 */


void * FUN_0041fd00(void)

{
  void *pvVar1;
  int iVar2;
  
  pvVar1 = operator_new(0x3f0);
  if (pvVar1 == (void *)0x0) {
    pvVar1 = (void *)0x0;
  }
  else {
    pvVar1 = (void *)FUN_0041f850();
  }
  iVar2 = FUN_0041fac0();
  if (iVar2 != 0) {
    if (pvVar1 != (void *)0x0) {
      FUN_0041fb50((int)pvVar1);
      _free(pvVar1);
    }
    return (void *)0x0;
  }
  return pvVar1;
}

