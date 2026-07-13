/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00421F60
 * Tracking name: FUN_00421f60
 * Ghidra name: FUN_00421f60
 * Tracked span: 64 bytes
 */


void FUN_00421f60(void)

{
  int iVar1;
  int in_EAX;
  
  iVar1 = DAT_00474c44;
  *(int *)(in_EAX + 0x9e78) = DAT_00474c44;
  if (DAT_00474c40 < iVar1) {
    DAT_00474c40 = iVar1;
  }
  return;
}

