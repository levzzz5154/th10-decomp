/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00401260
 * Tracking name: FUN_00401260
 * Ghidra name: FUN_00401260
 * Tracked span: 480 bytes
 */


void FUN_00401260(undefined4 *param_1)

{
  void *pvVar1;
  int iVar2;
  int extraout_ECX;
  int extraout_ECX_00;
  int extraout_ECX_01;
  int extraout_ECX_02;
  int iVar3;
  undefined4 *puVar4;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_004652f9;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  *param_1 = &PTR_LAB_0046cb14;
  iVar3 = DAT_00491be4;
  local_4 = 1;
  pvVar1 = (void *)param_1[3];
  if (pvVar1 != (void *)0x0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_00492274);
    DAT_0049231c = DAT_0049231c + '\x01';
    FUN_00449f60(pvVar1,iVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_00492274);
    DAT_0049231c = DAT_0049231c + -1;
  }
  iVar3 = DAT_00491be4;
  pvVar1 = (void *)param_1[4];
  if (pvVar1 != (void *)0x0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_00492274);
    DAT_0049231c = DAT_0049231c + '\x01';
    FUN_00449f60(pvVar1,iVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_00492274);
    DAT_0049231c = DAT_0049231c + -1;
    iVar3 = extraout_ECX;
  }
  iVar2 = DAT_00491be4;
  pvVar1 = (void *)param_1[0x226a];
  if (pvVar1 != (void *)0x0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_00492274);
    DAT_0049231c = DAT_0049231c + '\x01';
    FUN_00449f60(pvVar1,iVar2);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_00492274);
    DAT_0049231c = DAT_0049231c + -1;
    iVar3 = extraout_ECX_00;
  }
  puVar4 = (undefined4 *)((int)g_pGameStateManager + 0x3ad074);
  if (*(int *)((int)g_pGameStateManager + 0x3ad074) != 0) {
    FUN_00447810(iVar3);
    _free((void *)*puVar4);
    *puVar4 = 0;
    iVar3 = extraout_ECX_01;
  }
  puVar4 = (undefined4 *)((int)g_pGameStateManager + 0x3ad06c);
  if (*(int *)((int)g_pGameStateManager + 0x3ad06c) != 0) {
    FUN_00447810(iVar3);
    _free((void *)*puVar4);
    *puVar4 = 0;
    iVar3 = extraout_ECX_02;
  }
  puVar4 = (undefined4 *)((int)g_pGameStateManager + 0x3ad078);
  if (*(int *)((int)g_pGameStateManager + 0x3ad078) != 0) {
    FUN_00447810(iVar3);
    _free((void *)*puVar4);
    *puVar4 = 0;
  }
  g_pGameThread = (void *)0x0;
  if ((void *)param_1[0x1c6] != (void *)0x0) {
    _free((void *)param_1[0x1c6]);
  }
  param_1[0x1c6] = 0;
  if ((void *)param_1[0xdb] != (void *)0x0) {
    _free((void *)param_1[0xdb]);
    param_1[0xdb] = 0;
    ExceptionList = local_c;
    return;
  }
  param_1[0xdb] = 0;
  ExceptionList = local_c;
  return;
}

