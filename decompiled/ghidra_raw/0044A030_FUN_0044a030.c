/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0044A030
 * Tracking name: FUN_0044a030
 * Ghidra name: FUN_0044a030
 * Tracked span: 144 bytes
 */


int FUN_0044a030(undefined4 param_1)

{
  int iVar1;
  undefined4 in_EAX;
  int iVar2;
  
  iVar2 = FUN_00449ed0(in_EAX);
  iVar1 = DAT_00491be4;
  *(undefined4 *)(iVar2 + 0x20) = param_1;
  *(uint *)(iVar2 + 4) = *(uint *)(iVar2 + 4) | 2;
  FUN_00449b70(iVar1);
  return iVar2;
}

