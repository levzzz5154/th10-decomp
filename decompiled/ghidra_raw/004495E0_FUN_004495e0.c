/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x004495E0
 * Tracking name: FUN_004495e0
 * Ghidra name: FUN_004495e0
 * Tracked span: 80 bytes
 */


void FUN_004495e0(void)

{
  int *piVar1;
  undefined4 *in_EAX;
  int iVar2;
  
  iVar2 = FUN_004491c0(*in_EAX,(int)g_pGameStateManager,*in_EAX);
  if ((iVar2 != 0) &&
     (*(uint *)(iVar2 + 0x35c) = *(uint *)(iVar2 + 0x35c) & 0xfffffffd, *(int *)(iVar2 + 0x18) == 0)
     ) {
    for (piVar1 = *(int **)(iVar2 + 0x14); piVar1 != (int *)0x0; piVar1 = (int *)piVar1[1]) {
      *(uint *)(*piVar1 + 0x35c) = *(uint *)(*piVar1 + 0x35c) & 0xfffffffd;
    }
  }
  return;
}

