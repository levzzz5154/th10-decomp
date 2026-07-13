/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x004492A0
 * Tracking name: FUN_004492a0
 * Ghidra name: FUN_004492a0
 * Tracked span: 80 bytes
 */


void __fastcall FUN_004492a0(undefined4 param_1,int param_2,int param_3)

{
  int *piVar1;
  int iVar2;
  
  iVar2 = FUN_004491c0(param_1,param_2,param_3);
  if ((iVar2 != 0) &&
     (*(uint *)(iVar2 + 0x35c) = *(uint *)(iVar2 + 0x35c) | 0x4000000, *(int *)(iVar2 + 0x18) == 0))
  {
    for (piVar1 = *(int **)(iVar2 + 0x14); piVar1 != (int *)0x0; piVar1 = (int *)piVar1[1]) {
      *(uint *)(*piVar1 + 0x35c) = *(uint *)(*piVar1 + 0x35c) | 0x4000000;
    }
  }
  return;
}

