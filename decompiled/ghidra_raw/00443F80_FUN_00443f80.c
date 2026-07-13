/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00443F80
 * Tracking name: FUN_00443f80
 * Ghidra name: FUN_00443f80
 * Tracked span: 48 bytes
 */


undefined4 FUN_00443f80(void *param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_00443b60();
  if (iVar1 != 0) {
    return 0xffffffff;
  }
  uVar2 = FUN_00442670(param_1,0);
  return uVar2;
}

