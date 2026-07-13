/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00409F90
 * Tracking name: FUN_00409f90
 * Ghidra name: FUN_00409f90
 * Tracked span: 2480 bytes
 */


void __thiscall FUN_00409f90(void *this,int param_1)

{
  uint *puVar1;
  int *piVar2;
  int *piVar3;
  void *extraout_ECX;
  int *piVar4;
  int iVar5;
  
  piVar4 = (int *)((int)g_pGameStateManager + 0x3ad090);
  iVar5 = 4;
  do {
    FUN_004493e0(this,*piVar4);
    piVar4 = piVar4 + 1;
    iVar5 = iVar5 + -1;
    this = extraout_ECX;
  } while (iVar5 != 0);
  piVar4 = *(int **)(param_1 + 0x58);
  while (piVar4 != (int *)0x0) {
    piVar2 = (int *)piVar4[1];
    piVar3 = (int *)*piVar4;
    piVar4 = piVar2;
    if (piVar3 != (int *)0x0) {
      (**(code **)(*piVar3 + 0x14))(1);
    }
  }
  *(undefined4 *)(param_1 + 100) = 0;
  *(undefined4 *)(param_1 + 0x10) = 0;
  if (*(int *)(param_1 + 8) != 0) {
    puVar1 = (uint *)(*(int *)(param_1 + 8) + 4);
    *puVar1 = *puVar1 & 0xfffffffd;
  }
  if (*(int *)(param_1 + 0xc) != 0) {
    puVar1 = (uint *)(*(int *)(param_1 + 0xc) + 4);
    *puVar1 = *puVar1 & 0xfffffffd;
  }
  return;
}

