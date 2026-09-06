/* Raw Ghidra reference; not compilable reconstruction. Address: 0042BC30 */

void FUN_0042bc30(int param_1)

{
  void *pvVar1;
  int iVar2;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 uVar3;
  undefined4 *puVar4;
  void *pvStack_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_004653eb;
  pvStack_c = ExceptionList;
  local_4 = 0;
  ExceptionList = &pvStack_c;
  FUN_0042bad0();
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
  if (*(void **)(param_1 + 0x2e0) != (void *)0x0) {
    _free(*(void **)(param_1 + 0x2e0));
    *(undefined4 *)(param_1 + 0x2e0) = 0;
  }
  puVar4 = *(undefined4 **)(param_1 + 0x2d8);
  if (puVar4 != (undefined4 *)0x0) {
    *puVar4 = &PTR_FUN_0046d0f0;
    if ((void *)puVar4[0x23] != (void *)0x0) {
      _free((void *)puVar4[0x23]);
      puVar4[0x23] = 0;
    }
    _free(puVar4);
    *(undefined4 *)(param_1 + 0x2d8) = 0;
  }
  uVar3 = 0;
  if (*(int **)(param_1 + 0x2dc) != (int *)0x0) {
    (**(code **)(**(int **)(param_1 + 0x2dc) + 0x14))(1);
    *(undefined4 *)(param_1 + 0x2dc) = 0;
    uVar3 = extraout_ECX;
  }
  puVar4 = (undefined4 *)((int)g_pGameStateManager + 0x3ad088);
  if (*(int *)((int)g_pGameStateManager + 0x3ad088) != 0) {
    FUN_00447810(uVar3);
    _free((void *)*puVar4);
    *puVar4 = 0;
    uVar3 = extraout_ECX_00;
  }
  puVar4 = (undefined4 *)((int)g_pGameStateManager + 0x3ad084);
  if (*(int *)((int)g_pGameStateManager + 0x3ad084) != 0) {
    FUN_00447810(uVar3);
    _free((void *)*puVar4);
    *puVar4 = 0;
  }
  DAT_00477844 = 0;
  *(undefined ***)(param_1 + 0x10) = &PTR_FUN_004703e4;
  FUN_0044c150();
  ExceptionList = pvStack_c;
  return;
}

