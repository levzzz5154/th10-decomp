/* Raw Ghidra reference; not compilable reconstruction. Address: 0042B570 */

void FUN_0042b570(int param_1)

{
  void *pvVar1;
  int iVar2;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  iVar2 = DAT_00491be4;
  puStack_8 = &LAB_0046523b;
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
  DAT_00477840 = 0;
  if (*(void **)(param_1 + 0x370) != (void *)0x0) {
    _free(*(void **)(param_1 + 0x370));
    *(undefined4 *)(param_1 + 0x370) = 0;
    ExceptionList = local_c;
    return;
  }
  *(undefined4 *)(param_1 + 0x370) = 0;
  ExceptionList = local_c;
  return;
}

