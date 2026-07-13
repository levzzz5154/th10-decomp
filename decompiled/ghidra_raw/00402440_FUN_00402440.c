/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00402440
 * Tracking name: FUN_00402440
 * Ghidra name: FUN_00402440
 * Tracked span: 512 bytes
 */


void FUN_00402440(int param_1)

{
  undefined4 *puVar1;
  void *pvVar2;
  int iVar3;
  uint uVar4;
  void *local_c;
  undefined1 *puStack_8;
  uint local_4;
  
  iVar3 = DAT_00491be4;
  puStack_8 = &LAB_004652d6;
  local_c = ExceptionList;
  local_4 = 1;
  pvVar2 = *(void **)(param_1 + 8);
  ExceptionList = &local_c;
  if (pvVar2 != (void *)0x0) {
    ExceptionList = &local_c;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_00492274);
    DAT_0049231c = DAT_0049231c + '\x01';
    FUN_00449f60(pvVar2,iVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_00492274);
    DAT_0049231c = DAT_0049231c + -1;
  }
  iVar3 = DAT_00491be4;
  pvVar2 = *(void **)(param_1 + 0xc);
  if (pvVar2 != (void *)0x0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_00492274);
    DAT_0049231c = DAT_0049231c + '\x01';
    FUN_00449f60(pvVar2,iVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_00492274);
    DAT_0049231c = DAT_0049231c + -1;
  }
  iVar3 = DAT_00491be4;
  pvVar2 = *(void **)(param_1 + 0x2a40);
  if (pvVar2 != (void *)0x0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_00492274);
    DAT_0049231c = DAT_0049231c + '\x01';
    FUN_00449f60(pvVar2,iVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_00492274);
    DAT_0049231c = DAT_0049231c + -1;
  }
  if (*(void **)(param_1 + 0x10) != (void *)0x0) {
    _free(*(void **)(param_1 + 0x10));
    *(undefined4 *)(param_1 + 0x10) = 0;
  }
  if (*(void **)(param_1 + 0x2a44) != (void *)0x0) {
    _free(*(void **)(param_1 + 0x2a44));
    *(undefined4 *)(param_1 + 0x2a44) = 0;
  }
  *(undefined4 *)(param_1 + 0x2a44) = 0;
  if (*(void **)(param_1 + 0x17c) != (void *)0x0) {
    _free(*(void **)(param_1 + 0x17c));
    *(undefined4 *)(param_1 + 0x17c) = 0;
  }
  if (((((byte)DAT_00474ca0 & 1) == 0) &&
      (uVar4 = (*(uint *)(param_1 + 0x2a30) & 1) + 4, uVar4 < 0x21)) &&
     (puVar1 = (undefined4 *)((int)g_pGameStateManager + uVar4 * 4 + 0x3ad06c),
     *(int *)((int)g_pGameStateManager + uVar4 * 4 + 0x3ad06c) != 0)) {
    FUN_00447810(g_pGameStateManager);
    _free((void *)*puVar1);
    *puVar1 = 0;
  }
  if (DAT_004776e8 == param_1) {
    DAT_004776e8 = 0;
  }
  if (DAT_004776e4 == param_1) {
    DAT_004776e4 = 0;
  }
  local_4 = local_4 & 0xffffff00;
  _eh_vector_destructor_iterator_((void *)(param_1 + 0x1f08),0x3ac,3,FUN_00401ff0);
  local_4 = 0xffffffff;
  _eh_vector_destructor_iterator_((void *)(param_1 + 0x180),0x3ac,8,FUN_00401ff0);
  ExceptionList = local_c;
  return;
}

