/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0040B7B0
 * Tracking name: FUN_0040b7b0
 * Ghidra name: FUN_0040b7b0
 * Tracked span: 400 bytes
 */


void FUN_0040b7b0(int param_1)

{
  void *pvVar1;
  int iVar2;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  undefined4 extraout_ECX_02;
  undefined4 extraout_ECX_03;
  undefined4 uVar3;
  int *piVar4;
  undefined4 *puVar5;
  
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
  FUN_00447f70();
  pvVar1 = *(void **)(param_1 + 0x18);
  uVar3 = extraout_ECX;
  if (pvVar1 != (void *)0x0) {
    FUN_0040b3a0();
    _free(pvVar1);
    uVar3 = extraout_ECX_00;
  }
  piVar4 = (int *)((int)g_pGameStateManager + 0x3ad0e0);
  *(undefined4 *)(param_1 + 0x18) = 0;
  if (*piVar4 != 0) {
    FUN_00447810(uVar3);
    _free((void *)*piVar4);
    *piVar4 = 0;
    uVar3 = extraout_ECX_01;
  }
  puVar5 = (undefined4 *)((int)g_pGameStateManager + 0x3ad0e4);
  if (*(int *)((int)g_pGameStateManager + 0x3ad0e4) != 0) {
    FUN_00447810(uVar3);
    _free((void *)*puVar5);
    *puVar5 = 0;
    uVar3 = extraout_ECX_02;
  }
  puVar5 = (undefined4 *)((int)g_pGameStateManager + 0x3ad0e8);
  if (*(int *)((int)g_pGameStateManager + 0x3ad0e8) != 0) {
    FUN_00447810(uVar3);
    _free((void *)*puVar5);
    *puVar5 = 0;
    uVar3 = extraout_ECX_03;
  }
  puVar5 = (undefined4 *)((int)g_pGameStateManager + 0x3ad0ec);
  if (*(int *)((int)g_pGameStateManager + 0x3ad0ec) != 0) {
    FUN_00447810(uVar3);
    _free((void *)*puVar5);
    *puVar5 = 0;
  }
  if (*(void **)(param_1 + 0x14) != (void *)0x0) {
    _free(*(void **)(param_1 + 0x14));
    *(undefined4 *)(param_1 + 0x14) = 0;
  }
  *(undefined4 *)(param_1 + 0x14) = 0;
  DAT_00477700 = 0;
  DAT_004918a4 = 0;
  return;
}

