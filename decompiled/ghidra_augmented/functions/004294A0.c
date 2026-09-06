/* Raw Ghidra reference; not compilable reconstruction. Address: 004294A0 */

void FUN_004294a0(int param_1)

{
  void *pvVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_00465268;
  local_c = ExceptionList;
  local_4 = 0;
  ExceptionList = &local_c;
  _free(*(void **)(param_1 + 0x14));
  iVar3 = 0;
  do {
    FUN_0042ab20(param_1);
    iVar3 = iVar3 + 1;
  } while (iVar3 < 8);
  _free(*(void **)(param_1 + 0x18));
  *(undefined4 *)(param_1 + 0x18) = 0;
  puVar4 = (undefined4 *)(param_1 + 0x1c);
  iVar3 = 8;
  do {
    _free((void *)*puVar4);
    *puVar4 = 0;
    iVar2 = DAT_00491be4;
    puVar4 = puVar4 + 1;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  pvVar1 = *(void **)(param_1 + 8);
  if (pvVar1 != (void *)0x0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_00492274);
    DAT_0049231c = DAT_0049231c + '\x01';
    FUN_00449f60(pvVar1,iVar2);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_00492274);
    DAT_0049231c = DAT_0049231c + -1;
  }
  iVar3 = DAT_00491be4;
  pvVar1 = *(void **)(param_1 + 0x1cc);
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
  if (param_1 == DAT_00477838) {
    DAT_00477838 = 0;
  }
  local_4 = 0xffffffff;
  _eh_vector_destructor_iterator_((void *)(param_1 + 0xa0),0x24,8,FUN_0042ac60);
  ExceptionList = local_c;
  return;
}

