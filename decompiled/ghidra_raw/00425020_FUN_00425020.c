/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00425020
 * Tracking name: FUN_00425020
 * Ghidra name: FUN_00425020
 * Tracked span: 144 bytes
 */


void * FUN_00425020(void)

{
  void *pvVar1;
  int iVar2;
  void *this;
  
  pvVar1 = operator_new(0x4478);
  if (pvVar1 == (void *)0x0) {
    pvVar1 = (void *)0x0;
  }
  else {
    pvVar1 = (void *)FUN_004246c0();
  }
  iVar2 = FUN_004247f0();
  if (iVar2 != 0) {
    if (pvVar1 != (void *)0x0) {
      FUN_00424ed0(this,(int)pvVar1);
      _free(pvVar1);
    }
    return (void *)0x0;
  }
  return pvVar1;
}

