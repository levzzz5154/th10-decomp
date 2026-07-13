/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0042CB60
 * Tracking name: FUN_0042cb60
 * Ghidra name: FUN_0042cb60
 * Tracked span: 496 bytes
 */


void FUN_0042cb60(undefined4 *param_1)

{
  void *pvVar1;
  int *piVar2;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  undefined4 extraout_ECX_02;
  undefined4 uVar3;
  undefined4 *puVar4;
  int iVar5;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_0046562e;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  *param_1 = &PTR_LAB_0046ecf0;
  local_4 = 0;
  FUN_0044c150();
  iVar5 = DAT_00491be4;
  pvVar1 = (void *)param_1[3];
  uVar3 = extraout_ECX;
  if (pvVar1 != (void *)0x0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_00492274);
    DAT_0049231c = DAT_0049231c + '\x01';
    FUN_00449f60(pvVar1,iVar5);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_00492274);
    DAT_0049231c = DAT_0049231c + -1;
    uVar3 = extraout_ECX_00;
  }
  iVar5 = DAT_00491be4;
  pvVar1 = (void *)param_1[4];
  if (pvVar1 != (void *)0x0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_00492274);
    DAT_0049231c = DAT_0049231c + '\x01';
    FUN_00449f60(pvVar1,iVar5);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_00492274);
    DAT_0049231c = DAT_0049231c + -1;
    uVar3 = extraout_ECX_01;
  }
  puVar4 = (undefined4 *)((int)g_pGameStateManager + 0x3ad0d0);
  if (*(int *)((int)g_pGameStateManager + 0x3ad0d0) != 0) {
    FUN_00447810(uVar3);
    _free((void *)*puVar4);
    *puVar4 = 0;
    uVar3 = extraout_ECX_02;
  }
  puVar4 = (undefined4 *)((int)g_pGameStateManager + 0x3ad0d4);
  if (*(int *)((int)g_pGameStateManager + 0x3ad0d4) != 0) {
    FUN_00447810(uVar3);
    _free((void *)*puVar4);
    *puVar4 = 0;
  }
  puVar4 = param_1 + 0x1679;
  iVar5 = 0x32;
  do {
    pvVar1 = (void *)*puVar4;
    if (pvVar1 != (void *)0x0) {
      FUN_004294a0((int)pvVar1);
      _free(pvVar1);
    }
    puVar4 = puVar4 + 1;
    iVar5 = iVar5 + -1;
  } while (iVar5 != 0);
  iVar5 = param_1[0x174];
  if (iVar5 != 0) {
    for (piVar2 = *(int **)((int)g_pGameStateManager + 0x72dad4); piVar2 != (int *)0x0;
        piVar2 = (int *)piVar2[1]) {
      if (*(int *)*piVar2 == iVar5) goto LAB_0042ccd6;
    }
    for (piVar2 = *(int **)((int)g_pGameStateManager + 0x72dadc); piVar2 != (int *)0x0;
        piVar2 = (int *)piVar2[1]) {
      if (*(int *)*piVar2 == iVar5) goto LAB_0042ccd6;
    }
  }
LAB_0042cd04:
  if ((void *)param_1[0x16ab] != (void *)0x0) {
    _free((void *)param_1[0x16ab]);
    param_1[0x16ab] = 0;
  }
  DAT_0047784c = 0;
  param_1[0x16ac] = &PTR_FUN_004703e4;
  FUN_0044c150();
  ExceptionList = local_c;
  return;
LAB_0042ccd6:
  iVar5 = *piVar2;
  if ((iVar5 != 0) && (*(undefined2 *)(iVar5 + 0x304) = 1, *(int *)(iVar5 + 0x18) == 0)) {
    for (piVar2 = *(int **)(iVar5 + 0x14); piVar2 != (int *)0x0; piVar2 = (int *)piVar2[1]) {
      *(undefined2 *)(*piVar2 + 0x304) = 1;
    }
  }
  goto LAB_0042cd04;
}

