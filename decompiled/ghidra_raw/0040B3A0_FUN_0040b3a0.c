/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0040B3A0
 * Tracking name: FUN_0040b3a0
 * Ghidra name: FUN_0040b3a0
 * Tracked span: 224 bytes
 */


void FUN_0040b3a0(void)

{
  int iVar1;
  void *pvVar2;
  int in_EAX;
  int *piVar3;
  int *piVar4;
  int iVar5;
  
  FUN_0044c150();
  pvVar2 = g_pGameStateManager;
  piVar4 = (int *)(in_EAX + 0x40);
  iVar5 = 5;
LAB_0040b3d0:
  iVar1 = *piVar4;
  if (iVar1 != 0) {
    for (piVar3 = *(int **)((int)pvVar2 + 0x72dad4); piVar3 != (int *)0x0; piVar3 = (int *)piVar3[1]
        ) {
      if (*(int *)*piVar3 == iVar1) goto LAB_0040b406;
    }
    for (piVar3 = *(int **)((int)pvVar2 + 0x72dadc); piVar3 != (int *)0x0; piVar3 = (int *)piVar3[1]
        ) {
      if (*(int *)*piVar3 == iVar1) goto LAB_0040b406;
    }
  }
  goto LAB_0040b43f;
LAB_0040b406:
  iVar1 = *piVar3;
  if ((iVar1 != 0) &&
     (*(uint *)(iVar1 + 0x35c) = *(uint *)(iVar1 + 0x35c) | 0x4000000, *(int *)(iVar1 + 0x18) == 0))
  {
    for (piVar3 = *(int **)(iVar1 + 0x14); piVar3 != (int *)0x0; piVar3 = (int *)piVar3[1]) {
      *(uint *)(*piVar3 + 0x35c) = *(uint *)(*piVar3 + 0x35c) | 0x4000000;
    }
  }
LAB_0040b43f:
  *piVar4 = 0;
  piVar4 = piVar4 + 1;
  iVar5 = iVar5 + -1;
  if (iVar5 == 0) {
    *(undefined ***)(in_EAX + 0xd0) = &PTR_FUN_004703e4;
    FUN_0044c150();
    return;
  }
  goto LAB_0040b3d0;
}

