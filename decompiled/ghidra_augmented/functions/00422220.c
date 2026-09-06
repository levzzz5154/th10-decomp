/* Raw Ghidra reference; not compilable reconstruction. Address: 00422220 */

void FUN_00422220(int param_1)

{
  void *pvVar1;
  int *piVar2;
  int iVar3;
  undefined4 *puVar4;
  
  iVar3 = DAT_00491be4;
  pvVar1 = *(void **)(param_1 + 8);
  if (pvVar1 != (void *)0x0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_00492274);
    DAT_0049231c = DAT_0049231c + '\x01';
    FUN_00449f60(pvVar1,iVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_00492274);
    DAT_0049231c = DAT_0049231c + -1;
  }
  iVar3 = DAT_00491be4;
  pvVar1 = *(void **)(param_1 + 0xc);
  if (pvVar1 != (void *)0x0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_00492274);
    DAT_0049231c = DAT_0049231c + '\x01';
    FUN_00449f60(pvVar1,iVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_00492274);
    DAT_0049231c = DAT_0049231c + -1;
  }
  puVar4 = (undefined4 *)(param_1 + 0x1ec);
  iVar3 = 0x19;
  do {
    pvVar1 = (void *)*puVar4;
    if (pvVar1 != (void *)0x0) {
      FUN_004294a0((int)pvVar1);
      _free(pvVar1);
    }
    puVar4 = puVar4 + 1;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  iVar3 = *(int *)(param_1 + 0x1dc);
  if (iVar3 != 0) {
    for (piVar2 = *(int **)((int)g_pGameStateManager + 0x72dad4); piVar2 != (int *)0x0;
        piVar2 = (int *)piVar2[1]) {
      if (*(int *)*piVar2 == iVar3) goto LAB_00422306;
    }
    for (piVar2 = *(int **)((int)g_pGameStateManager + 0x72dadc); piVar2 != (int *)0x0;
        piVar2 = (int *)piVar2[1]) {
      if (*(int *)*piVar2 == iVar3) goto LAB_00422306;
    }
  }
LAB_0042233f:
  *(undefined4 *)(param_1 + 0x1dc) = 0;
  DAT_00477830 = 0;
  return;
LAB_00422306:
  iVar3 = *piVar2;
  if ((iVar3 != 0) &&
     (*(uint *)(iVar3 + 0x35c) = *(uint *)(iVar3 + 0x35c) | 0x4000000, *(int *)(iVar3 + 0x18) == 0))
  {
    for (piVar2 = *(int **)(iVar3 + 0x14); piVar2 != (int *)0x0; piVar2 = (int *)piVar2[1]) {
      *(uint *)(*piVar2 + 0x35c) = *(uint *)(*piVar2 + 0x35c) | 0x4000000;
    }
  }
  goto LAB_0042233f;
}

