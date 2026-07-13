/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0040DAE0
 * Tracking name: FUN_0040dae0
 * Ghidra name: FUN_0040dae0
 * Tracked span: 416 bytes
 */


void FUN_0040dae0(undefined4 *param_1)

{
  undefined4 *puVar1;
  undefined4 *_Memory;
  void *pvVar2;
  int *piVar3;
  int *piVar4;
  int iVar5;
  int local_4;
  
  iVar5 = DAT_00477704;
  *param_1 = &PTR_LAB_0046d0c0;
  if (*(undefined4 **)(iVar5 + 0x58) == param_1 + 0x45b) {
    *(undefined4 *)(iVar5 + 0x58) = param_1[0x45c];
  }
  if (*(undefined4 **)(iVar5 + 0x5c) == param_1 + 0x45b) {
    *(undefined4 *)(iVar5 + 0x5c) = param_1[0x45d];
  }
  if (param_1[0x45c] != 0) {
    *(undefined4 *)(param_1[0x45c] + 8) = param_1[0x45d];
  }
  if (param_1[0x45d] != 0) {
    *(undefined4 *)(param_1[0x45d] + 4) = param_1[0x45c];
  }
  param_1[0x45c] = 0;
  param_1[0x45d] = 0;
  *(int *)(iVar5 + 0x60) = *(int *)(iVar5 + 0x60) + -1;
  if ((char)((uint)param_1[0x920] >> 8) < '\0') {
    *(undefined4 *)(iVar5 + 0x10 + param_1[0x923] * 4) = 0;
  }
  pvVar2 = g_pGameStateManager;
  piVar4 = param_1 + 0x43f;
  local_4 = 10;
LAB_0040db70:
  iVar5 = *piVar4;
  if (iVar5 != 0) {
    for (piVar3 = *(int **)((int)pvVar2 + 0x72dad4); piVar3 != (int *)0x0; piVar3 = (int *)piVar3[1]
        ) {
      if (*(int *)*piVar3 == iVar5) goto LAB_0040dbb0;
    }
    for (piVar3 = *(int **)((int)pvVar2 + 0x72dadc); piVar3 != (int *)0x0; piVar3 = (int *)piVar3[1]
        ) {
      if (*(int *)*piVar3 == iVar5) goto LAB_0040dbb0;
    }
  }
  goto LAB_0040dbe5;
LAB_0040dbb0:
  iVar5 = *piVar3;
  if ((iVar5 != 0) &&
     (*(uint *)(iVar5 + 0x35c) = *(uint *)(iVar5 + 0x35c) | 0x4000000, *(int *)(iVar5 + 0x18) == 0))
  {
    for (piVar3 = *(int **)(iVar5 + 0x14); piVar3 != (int *)0x0; piVar3 = (int *)piVar3[1]) {
      *(uint *)(*piVar3 + 0x35c) = *(uint *)(*piVar3 + 0x35c) | 0x4000000;
    }
  }
LAB_0040dbe5:
  *piVar4 = 0;
  iVar5 = DAT_00477834;
  piVar4 = piVar4 + 1;
  local_4 = local_4 + -1;
  if (local_4 == 0) {
    if (DAT_00477834 != 0) {
      if (*(undefined4 **)(DAT_00477834 + 0x3504) == param_1) {
        *(undefined4 *)(DAT_00477834 + 0x3504) = 0;
        *(undefined1 *)(iVar5 + 0x3508) = 0;
      }
      piVar4 = (int *)(iVar5 + 0x4e8);
      iVar5 = 0x80;
      do {
        if ((undefined4 *)*piVar4 == param_1) {
          *piVar4 = 0;
        }
        piVar4 = piVar4 + 0x17;
        iVar5 = iVar5 + -1;
      } while (iVar5 != 0);
    }
    *param_1 = &PTR_LAB_0046d0d8;
    _Memory = (undefined4 *)param_1[0x40d];
    while (_Memory != (undefined4 *)0x0) {
      puVar1 = (undefined4 *)_Memory[1];
      _free((void *)*_Memory);
      _free(_Memory);
      _Memory = puVar1;
    }
    return;
  }
  goto LAB_0040db70;
}

