/* Raw Ghidra reference; not compilable reconstruction. Address: 004269D0 */

void FUN_004269d0(int param_1)

{
  void *pvVar1;
  int *piVar2;
  int iVar3;
  int *piVar4;
  int local_4;
  
  iVar3 = (int)((ulonglong)((longlong)(DAT_00474c4c + -5000) * 0x55555555) >> 0x20) -
          (DAT_00474c4c + -5000);
  DAT_00474c4c = DAT_00474c4c + (((iVar3 >> 1) - (iVar3 >> 0x1f)) * 10) / 10;
  DAT_00474c70 = DAT_00474c70 + -1;
  if (DAT_00474c4c < 5000) {
    DAT_00474c4c = 5000;
  }
  if (-1 < DAT_00474c70) {
    SetAnimationActiveCount(DAT_00474c70);
  }
  *(undefined4 *)(param_1 + 0x458) = 2;
  if ((*(uint *)(param_1 + 0x484) & 1) == 0) {
    *(undefined4 *)(param_1 + 0x478) = 0;
    *(undefined4 *)(param_1 + 0x474) = 0xfff0bdc1;
    *(undefined4 *)(param_1 + 0x47c) = 0;
    *(undefined4 **)(param_1 + 0x480) = &DAT_00476f78;
    *(uint *)(param_1 + 0x484) = *(uint *)(param_1 + 0x484) | 1;
  }
  *(undefined4 *)(param_1 + 0x478) = 0;
  *(undefined4 *)(param_1 + 0x47c) = 0;
  *(undefined4 *)(param_1 + 0x474) = 0xffffffff;
  if ((*(uint *)(param_1 + 0x431c) & 1) == 0) {
    *(undefined4 *)(param_1 + 0x4310) = 0;
    *(undefined4 *)(param_1 + 0x430c) = 0xfff0bdc1;
    *(undefined4 *)(param_1 + 0x4314) = 0;
    *(undefined4 **)(param_1 + 0x4318) = &DAT_00476f78;
    *(uint *)(param_1 + 0x431c) = *(uint *)(param_1 + 0x431c) | 1;
  }
  *(undefined4 *)(param_1 + 0x4310) = 0xb4;
  *(undefined4 *)(param_1 + 0x4314) = 0x43340000;
  *(undefined4 *)(param_1 + 0x430c) = 0xb3;
  FUN_0043e710(*(undefined2 **)(param_1 + 0x10));
  pvVar1 = g_pGameStateManager;
  piVar4 = (int *)(param_1 + 0x3308);
  local_4 = 4;
LAB_00426b07:
  iVar3 = *piVar4;
  piVar4[-0x1a] = 0;
  if (iVar3 != 0) {
    for (piVar2 = *(int **)((int)pvVar1 + 0x72dad4); piVar2 != (int *)0x0; piVar2 = (int *)piVar2[1]
        ) {
      if (*(int *)*piVar2 == iVar3) goto LAB_00426b86;
    }
    for (piVar2 = *(int **)((int)pvVar1 + 0x72dadc); piVar2 != (int *)0x0; piVar2 = (int *)piVar2[1]
        ) {
      if (*(int *)*piVar2 == iVar3) goto LAB_00426b86;
    }
  }
  goto LAB_00426b49;
LAB_00426b86:
  iVar3 = *piVar2;
  if ((iVar3 != 0) && (*(undefined2 *)(iVar3 + 0x304) = 1, *(int *)(iVar3 + 0x18) == 0)) {
    for (piVar2 = *(int **)(iVar3 + 0x14); piVar2 != (int *)0x0; piVar2 = (int *)piVar2[1]) {
      *(undefined2 *)(*piVar2 + 0x304) = 1;
    }
  }
LAB_00426b49:
  iVar3 = piVar4[1];
  if (iVar3 != 0) {
    for (piVar2 = *(int **)((int)pvVar1 + 0x72dad4); piVar2 != (int *)0x0; piVar2 = (int *)piVar2[1]
        ) {
      if (*(int *)*piVar2 == iVar3) goto LAB_00426bb6;
    }
    for (piVar2 = *(int **)((int)pvVar1 + 0x72dadc); piVar2 != (int *)0x0; piVar2 = (int *)piVar2[1]
        ) {
      if (*(int *)*piVar2 == iVar3) goto LAB_00426bb6;
    }
  }
LAB_00426be0:
  iVar3 = DAT_00477838;
  piVar4 = piVar4 + 0x26;
  local_4 = local_4 + -1;
  if (local_4 == 0) {
    *(undefined4 *)(param_1 + 0x3500) = 0;
    if (*(int *)(iVar3 + 0x10) != 1) {
      FUN_00424650("Caution!");
    }
    iVar3 = DAT_004776f4;
    if (0x3b < *(int *)(DAT_004776f4 + 0x3738)) {
      *(undefined4 *)(DAT_004776f4 + 0x3790) = 0;
      *(uint *)(iVar3 + 0x378c) = *(uint *)(iVar3 + 0x378c) & 0xfffffffd;
      *(uint *)(iVar3 + 0xad4) = *(uint *)(iVar3 + 0xad4) & 0xfffffffd;
      *(uint *)(iVar3 + 0xe80) = *(uint *)(iVar3 + 0xe80) & 0xfffffffd;
      *(uint *)(iVar3 + 0x15d8) = *(uint *)(iVar3 + 0x15d8) & 0xfffffffd;
      *(uint *)(iVar3 + 0x1984) = *(uint *)(iVar3 + 0x1984) & 0xfffffffd;
      *(uint *)(iVar3 + 0x1d30) = *(uint *)(iVar3 + 0x1d30) & 0xfffffffd;
      *(uint *)(iVar3 + 0x20dc) = *(uint *)(iVar3 + 0x20dc) & 0xfffffffd;
      *(uint *)(iVar3 + 0x2488) = *(uint *)(iVar3 + 0x2488) & 0xfffffffd;
    }
    DAT_00474c98 = DAT_00474c98 + -0x400;
    if (DAT_00474c98 < 0x401) {
      if (DAT_00474c98 < -0x400) {
        DAT_00474c98 = -0x400;
      }
      return;
    }
    DAT_00474c98 = 0x400;
    return;
  }
  goto LAB_00426b07;
LAB_00426bb6:
  iVar3 = *piVar2;
  if ((iVar3 != 0) && (*(undefined2 *)(iVar3 + 0x304) = 1, *(int *)(iVar3 + 0x18) == 0)) {
    for (piVar2 = *(int **)(iVar3 + 0x14); piVar2 != (int *)0x0; piVar2 = (int *)piVar2[1]) {
      *(undefined2 *)(*piVar2 + 0x304) = 1;
    }
  }
  goto LAB_00426be0;
}

