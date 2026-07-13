/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00414370
 * Tracking name: FUN_00414370
 * Ghidra name: FUN_00414370
 * Tracked span: 512 bytes
 */


void __thiscall FUN_00414370(void *this,int param_1)

{
  uint *puVar1;
  void *pvVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  void *extraout_ECX;
  void *extraout_ECX_00;
  void *extraout_ECX_01;
  void *extraout_ECX_02;
  undefined4 extraout_ECX_03;
  int *piVar6;
  undefined4 *puVar7;
  
  iVar4 = param_1;
  if (((byte)DAT_00474ca0 & 9) == 0) {
    puVar7 = (undefined4 *)((int)g_pGameStateManager + 0x3ad0dc);
    if (*(int *)((int)g_pGameStateManager + 0x3ad0dc) != 0) {
      FUN_00447810(this);
      _free((void *)*puVar7);
      *puVar7 = 0;
      this = extraout_ECX;
    }
  }
  else {
    FUN_004493e0(this,*(int *)(param_1 + 0x9e80));
    this = extraout_ECX_00;
  }
  pvVar2 = *(void **)(param_1 + 0x9eb8);
  *(undefined4 *)(param_1 + 0x9e80) = 0;
  if (pvVar2 != (void *)0x0) {
    FUN_004136c0(this);
    _free(pvVar2);
    *(undefined4 *)(param_1 + 0x9eb8) = 0;
    this = extraout_ECX_01;
  }
  if (((byte)DAT_00474ca0 & 9) == 0) {
    if (*(void **)(param_1 + 0x9ebc) != (void *)0x0) {
      _free(*(void **)(param_1 + 0x9ebc));
      *(undefined4 *)(param_1 + 0x9ebc) = 0;
      this = extraout_ECX_02;
    }
    *(undefined4 *)(param_1 + 0x9ebc) = 0;
    DAT_00491be8 = (void *)0x0;
  }
  else {
    this = *(void **)(param_1 + 0x9ebc);
    DAT_00491be8 = this;
  }
  if (*(int *)(param_1 + 8) != 0) {
    puVar1 = (uint *)(*(int *)(param_1 + 8) + 4);
    *puVar1 = *puVar1 & 0xfffffffd;
  }
  FUN_004492a0(this,(int)g_pGameStateManager,*(int *)(param_1 + 0x9e14));
  pvVar2 = g_pGameStateManager;
  *(undefined4 *)(param_1 + 0x9e14) = 0;
  FUN_004492a0(extraout_ECX_03,(int)pvVar2,*(int *)(param_1 + 0x9e18));
  *(undefined4 *)(param_1 + 0x9e18) = 0;
  FUN_004492a0(*(undefined4 *)(param_1 + 0x9e24),(int)pvVar2,*(undefined4 *)(param_1 + 0x9e24));
  *(undefined4 *)(param_1 + 0x9e24) = 0;
  *(undefined4 *)(param_1 + 0x9e28) = 0;
  *(undefined4 *)(param_1 + 0x9e2c) = 0;
  *(undefined4 *)(param_1 + 0x9e30) = 0;
  *(undefined4 *)(param_1 + 0x9e34) = 0;
  *(undefined4 *)(param_1 + 0x9e38) = 0;
  *(undefined4 *)(param_1 + 0x9e3c) = 0;
  *(undefined4 *)(param_1 + 0x9e40) = 0;
  *(undefined4 *)(param_1 + 0x9e44) = 0;
  *(undefined4 *)(param_1 + 0x9e48) = 0;
  *(undefined4 *)(param_1 + 0x9e4c) = 0;
  piVar6 = (int *)(param_1 + 0x9df4);
  param_1 = 8;
LAB_004144c0:
  iVar3 = *piVar6;
  if (iVar3 != 0) {
    for (piVar5 = *(int **)((int)pvVar2 + 0x72dad4); piVar5 != (int *)0x0; piVar5 = (int *)piVar5[1]
        ) {
      if (*(int *)*piVar5 == iVar3) goto LAB_004144f6;
    }
    for (piVar5 = *(int **)((int)pvVar2 + 0x72dadc); piVar5 != (int *)0x0; piVar5 = (int *)piVar5[1]
        ) {
      if (*(int *)*piVar5 == iVar3) goto LAB_004144f6;
    }
  }
  goto LAB_0041452f;
LAB_004144f6:
  iVar3 = *piVar5;
  if ((iVar3 != 0) &&
     (*(uint *)(iVar3 + 0x35c) = *(uint *)(iVar3 + 0x35c) | 0x4000000, *(int *)(iVar3 + 0x18) == 0))
  {
    for (piVar5 = *(int **)(iVar3 + 0x14); piVar5 != (int *)0x0; piVar5 = (int *)piVar5[1]) {
      *(uint *)(*piVar5 + 0x35c) = *(uint *)(*piVar5 + 0x35c) | 0x4000000;
    }
  }
LAB_0041452f:
  *piVar6 = 0;
  piVar6 = piVar6 + 1;
  param_1 = param_1 + -1;
  if (param_1 == 0) {
    *(undefined4 *)(iVar4 + 0x9e90) = 0;
    return;
  }
  goto LAB_004144c0;
}

