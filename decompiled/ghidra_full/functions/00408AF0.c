/* Raw Ghidra reference; not compilable reconstruction. Address: 00408AF0 */

void __thiscall FUN_00408af0(void *this,int param_1)

{
  void *pvVar1;
  int iVar2;
  undefined4 extraout_ECX;
  code *pcVar3;
  void *local_c;
  undefined1 *puStack_8;
  int local_4;
  
  pvVar1 = g_pGameStateManager;
  puStack_8 = &LAB_0046560f;
  local_c = ExceptionList;
  local_4 = 2;
  ExceptionList = &local_c;
  FUN_004492a0(this,(int)g_pGameStateManager,*(int *)(param_1 + 0x768));
  *(undefined4 *)(param_1 + 0x768) = 0;
  FUN_004492a0(*(undefined4 *)(param_1 + 0x76c),(int)pvVar1,*(undefined4 *)(param_1 + 0x76c));
  *(undefined4 *)(param_1 + 0x76c) = 0;
  FUN_004492a0(extraout_ECX,(int)pvVar1,*(int *)(param_1 + 0x770));
  iVar2 = DAT_00491be4;
  *(undefined4 *)(param_1 + 0x770) = 0;
  pvVar1 = *(void **)(param_1 + 8);
  pcVar3 = LeaveCriticalSection_exref;
  if (pvVar1 != (void *)0x0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_00492274);
    DAT_0049231c = DAT_0049231c + '\x01';
    FUN_00449f60(pvVar1,iVar2);
    pcVar3 = LeaveCriticalSection_exref;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_00492274);
    DAT_0049231c = DAT_0049231c + -1;
  }
  iVar2 = DAT_00491be4;
  pvVar1 = *(void **)(param_1 + 0xc);
  if (pvVar1 != (void *)0x0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_00492274);
    DAT_0049231c = DAT_0049231c + '\x01';
    FUN_00449f60(pvVar1,iVar2);
    (*pcVar3)(&DAT_00492274);
    DAT_0049231c = DAT_0049231c + -1;
  }
  iVar2 = DAT_00491be4;
  pvVar1 = *(void **)(param_1 + 0x37ac);
  if (pvVar1 != (void *)0x0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_00492274);
    DAT_0049231c = DAT_0049231c + '\x01';
    FUN_00449f60(pvVar1,iVar2);
    (*pcVar3)(&DAT_00492274);
    DAT_0049231c = DAT_0049231c + -1;
  }
  DAT_004776f4 = 0;
  local_4._0_1_ = 1;
  _eh_vector_destructor_iterator_((void *)(param_1 + 0x24d8),0x3ac,5,FUN_00401ff0);
  local_4 = (uint)local_4._1_3_ << 8;
  _eh_vector_destructor_iterator_((void *)(param_1 + 0x778),0x3ac,8,FUN_00401ff0);
  local_4 = 0xffffffff;
  _eh_vector_destructor_iterator_((void *)(param_1 + 0x10),0x3ac,2,FUN_00401ff0);
  ExceptionList = local_c;
  return;
}

