/* Raw Ghidra reference; not compilable reconstruction. Address: 00424ED0 */

void __thiscall FUN_00424ed0(void *this,int param_1)

{
  void *pvVar1;
  int iVar2;
  void *extraout_ECX;
  void *extraout_ECX_00;
  undefined4 *puVar3;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  iVar2 = DAT_00491be4;
  puStack_8 = &LAB_0046528b;
  local_c = ExceptionList;
  local_4 = 0;
  pvVar1 = *(void **)(param_1 + 8);
  ExceptionList = &local_c;
  if (pvVar1 != (void *)0x0) {
    ExceptionList = &local_c;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_00492274);
    DAT_0049231c = DAT_0049231c + '\x01';
    FUN_00449f60(pvVar1,iVar2);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_00492274);
    DAT_0049231c = DAT_0049231c + -1;
    this = extraout_ECX;
  }
  iVar2 = DAT_00491be4;
  pvVar1 = *(void **)(param_1 + 0xc);
  if (pvVar1 != (void *)0x0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_00492274);
    DAT_0049231c = DAT_0049231c + '\x01';
    FUN_00449f60(pvVar1,iVar2);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_00492274);
    DAT_0049231c = DAT_0049231c + -1;
    this = extraout_ECX_00;
  }
  DAT_00477834 = 0;
  if ((DAT_00474ca0 & 1) == 0) {
    puVar3 = (undefined4 *)((int)g_pGameStateManager + 0x3ad08c);
    if (*(int *)((int)g_pGameStateManager + 0x3ad08c) != 0) {
      FUN_00447810(this);
      _free((void *)*puVar3);
      *puVar3 = 0;
    }
    if (*(void **)(param_1 + 0x45c) != (void *)0x0) {
      _free(*(void **)(param_1 + 0x45c));
      *(undefined4 *)(param_1 + 0x45c) = 0;
    }
    DAT_00491bf0 = 0;
  }
  else {
    FUN_004493e0(this,*(int *)(param_1 + 0x10));
    DAT_00491bf0 = *(undefined4 *)(param_1 + 0x45c);
  }
  if (*(void **)(param_1 + 0x36c) != (void *)0x0) {
    _free(*(void **)(param_1 + 0x36c));
  }
  *(undefined4 *)(param_1 + 0x36c) = 0;
  ExceptionList = local_c;
  return;
}

