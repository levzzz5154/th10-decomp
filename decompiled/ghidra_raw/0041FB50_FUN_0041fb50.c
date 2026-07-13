/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0041FB50
 * Tracking name: FUN_0041fb50
 * Ghidra name: FUN_0041fb50
 * Tracked span: 432 bytes
 */


void FUN_0041fb50(int param_1)

{
  void *pvVar1;
  int iVar2;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  undefined4 extraout_ECX_02;
  undefined4 extraout_ECX_03;
  undefined4 extraout_ECX_04;
  undefined4 uVar3;
  undefined4 *puVar4;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_00465696;
  local_c = ExceptionList;
  local_4 = 1;
  ExceptionList = &local_c;
  FUN_0044c150();
  iVar2 = DAT_00491be4;
  pvVar1 = *(void **)(param_1 + 8);
  uVar3 = extraout_ECX;
  if (pvVar1 != (void *)0x0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_00492274);
    DAT_0049231c = DAT_0049231c + '\x01';
    FUN_00449f60(pvVar1,iVar2);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_00492274);
    DAT_0049231c = DAT_0049231c + -1;
    uVar3 = extraout_ECX_00;
  }
  iVar2 = DAT_00491be4;
  pvVar1 = *(void **)(param_1 + 0xc);
  if (pvVar1 != (void *)0x0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_00492274);
    DAT_0049231c = DAT_0049231c + '\x01';
    FUN_00449f60(pvVar1,iVar2);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_00492274);
    DAT_0049231c = DAT_0049231c + -1;
    uVar3 = extraout_ECX_01;
  }
  FUN_0041f930(uVar3);
  puVar4 = (undefined4 *)((int)g_pGameStateManager + 0x3ad070);
  uVar3 = extraout_ECX_02;
  if (*(int *)((int)g_pGameStateManager + 0x3ad070) != 0) {
    FUN_00447810(extraout_ECX_02);
    _free((void *)*puVar4);
    *puVar4 = 0;
    uVar3 = extraout_ECX_03;
  }
  pvVar1 = g_pGameThread;
  DAT_00477820 = 0;
  if (g_pGameThread != (void *)0x0) {
    FUN_00401260(g_pGameThread);
    _free(pvVar1);
    uVar3 = extraout_ECX_04;
  }
  puVar4 = (undefined4 *)((int)g_pGameStateManager + 0x3ad06c);
  if (*(int *)((int)g_pGameStateManager + 0x3ad06c) != 0) {
    FUN_00447810(uVar3);
    _free((void *)*puVar4);
    *puVar4 = 0;
  }
  FUN_0042b1e0();
  puVar4 = DAT_0047783c;
  if (DAT_0047783c != (undefined4 *)0x0) {
    if ((void *)*DAT_0047783c != (void *)0x0) {
      _free((void *)*DAT_0047783c);
      *puVar4 = 0;
    }
    if ((void *)puVar4[1] != (void *)0x0) {
      _free((void *)puVar4[1]);
      puVar4[1] = 0;
    }
    _free(puVar4);
  }
  DAT_0047783c = (undefined4 *)0x0;
  if (*(void **)(param_1 + 0x388) != (void *)0x0) {
    _free(*(void **)(param_1 + 0x388));
  }
  *(undefined4 *)(param_1 + 0x388) = 0;
  *(undefined ***)(param_1 + 0x10) = &PTR_FUN_004703e4;
  FUN_0044c150();
  ExceptionList = local_c;
  return;
}

