/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00422360
 * Tracking name: FUN_00422360
 * Ghidra name: FUN_00422360
 * Tracked span: 144 bytes
 */


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
    puVar1 = FUN_004220e0(extraout_ECX,puVar1);
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

