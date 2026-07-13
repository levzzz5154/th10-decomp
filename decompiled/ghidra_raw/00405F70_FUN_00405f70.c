/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00405F70
 * Tracking name: FUN_00405f70
 * Ghidra name: FUN_00405f70
 * Tracked span: 240 bytes
 */


void FUN_00405f70(int param_1)

{
  void *pvVar1;
  int iVar2;
  int extraout_ECX;
  int iVar3;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  iVar2 = DAT_00491be4;
  puStack_8 = &LAB_0046553c;
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
  iVar3 = param_1;
  if (pvVar1 != (void *)0x0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_00492274);
    DAT_0049231c = DAT_0049231c + '\x01';
    FUN_00449f60(pvVar1,iVar2);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_00492274);
    DAT_0049231c = DAT_0049231c + -1;
    iVar3 = extraout_ECX;
  }
  FUN_004493e0(iVar3,*(int *)(param_1 + 0x3e0b50));
  local_4 = 0xffffffff;
  DAT_004776f0 = 0;
  _eh_vector_destructor_iterator_((void *)(param_1 + 0x60),0x7f0,0x7d1,FUN_00405de0);
  ExceptionList = local_c;
  return;
}

