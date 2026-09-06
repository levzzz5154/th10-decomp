/* Raw Ghidra reference; not compilable reconstruction. Address: 00418EE0 */

void FUN_00418ee0(int param_1)

{
  void *pvVar1;
  int iVar2;
  int *piVar3;
  int *piVar4;
  int local_4;
  
  iVar2 = DAT_00491be4;
  pvVar1 = *(void **)(param_1 + 8);
  if (pvVar1 != (void *)0x0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_00492274);
    DAT_0049231c = DAT_0049231c + '\x01';
    FUN_00449f60(pvVar1,iVar2);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_00492274);
    DAT_0049231c = DAT_0049231c + -1;
  }
  iVar2 = DAT_00491be4;
  pvVar1 = *(void **)(param_1 + 0xc);
  if (pvVar1 != (void *)0x0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_00492274);
    DAT_0049231c = DAT_0049231c + '\x01';
    FUN_00449f60(pvVar1,iVar2);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_00492274);
    DAT_0049231c = DAT_0049231c + -1;
  }
  pvVar1 = g_pGameStateManager;
  piVar4 = (int *)(param_1 + 0xdc);
  local_4 = 10;
LAB_00418f82:
  iVar2 = *piVar4;
  if (iVar2 != 0) {
    for (piVar3 = *(int **)((int)pvVar1 + 0x72dad4); piVar3 != (int *)0x0; piVar3 = (int *)piVar3[1]
        ) {
      if (*(int *)*piVar3 == iVar2) goto LAB_00418fc0;
    }
    for (piVar3 = *(int **)((int)pvVar1 + 0x72dadc); piVar3 != (int *)0x0; piVar3 = (int *)piVar3[1]
        ) {
      if (*(int *)*piVar3 == iVar2) goto LAB_00418fc0;
    }
  }
  goto LAB_00418ff1;
LAB_00418fc0:
  iVar2 = *piVar3;
  if ((iVar2 != 0) &&
     (*(uint *)(iVar2 + 0x35c) = *(uint *)(iVar2 + 0x35c) | 0x4000000, *(int *)(iVar2 + 0x18) == 0))
  {
    for (piVar3 = *(int **)(iVar2 + 0x14); piVar3 != (int *)0x0; piVar3 = (int *)piVar3[1]) {
      *(uint *)(*piVar3 + 0x35c) = *(uint *)(*piVar3 + 0x35c) | 0x4000000;
    }
  }
LAB_00418ff1:
  *piVar4 = 0;
  piVar4 = piVar4 + 1;
  local_4 = local_4 + -1;
  if (local_4 == 0) {
    if (DAT_00491d6a == '\x02') {
      FUN_0041a200(param_1,"hint/hint_auto.txt");
    }
    ClearEightResourceBuckets();
    DAT_00477814 = 0;
    return;
  }
  goto LAB_00418f82;
}

