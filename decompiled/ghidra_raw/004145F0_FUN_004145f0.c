/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x004145F0
 * Tracking name: FUN_004145f0
 * Ghidra name: FUN_004145f0
 * Tracked span: 576 bytes
 */


void __thiscall FUN_004145f0(void *this,int param_1)

{
  void *pvVar1;
  int iVar2;
  undefined4 *puVar3;
  int *piVar4;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  undefined4 uVar5;
  int *extraout_ECX_02;
  int *piVar6;
  int *piVar7;
  int local_10;
  void *local_c;
  undefined1 *puStack_8;
  int local_4;
  
  puStack_8 = &LAB_0046574e;
  local_c = ExceptionList;
  local_4 = 6;
  ExceptionList = &local_c;
  FUN_00414370(this,param_1);
  iVar2 = DAT_00491be4;
  pvVar1 = *(void **)(param_1 + 8);
  uVar5 = extraout_ECX;
  if (pvVar1 != (void *)0x0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_00492274);
    DAT_0049231c = DAT_0049231c + '\x01';
    FUN_00449f60(pvVar1,iVar2);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_00492274);
    DAT_0049231c = DAT_0049231c + -1;
    uVar5 = extraout_ECX_00;
  }
  iVar2 = DAT_00491be4;
  pvVar1 = *(void **)(param_1 + 0xc);
  if (pvVar1 != (void *)0x0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_00492274);
    DAT_0049231c = DAT_0049231c + '\x01';
    FUN_00449f60(pvVar1,iVar2);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_00492274);
    DAT_0049231c = DAT_0049231c + -1;
    uVar5 = extraout_ECX_01;
  }
  pvVar1 = g_pGameStateManager;
  *(undefined4 *)(param_1 + 8) = 0;
  FUN_004492a0(uVar5,(int)pvVar1,*(int *)(param_1 + 0x9e50));
  *(undefined4 *)(param_1 + 0x9e50) = 0;
  piVar7 = (int *)(param_1 + 0x9df4);
  local_10 = 8;
  piVar6 = extraout_ECX_02;
LAB_004146c0:
  iVar2 = *piVar7;
  if (iVar2 != 0) {
    for (piVar4 = *(int **)((int)pvVar1 + 0x72dad4); piVar4 != (int *)0x0; piVar4 = (int *)piVar4[1]
        ) {
      piVar6 = (int *)*piVar4;
      if (*piVar6 == iVar2) goto LAB_004146f6;
    }
    for (piVar4 = *(int **)((int)pvVar1 + 0x72dadc); piVar4 != (int *)0x0; piVar4 = (int *)piVar4[1]
        ) {
      piVar6 = (int *)*piVar4;
      if (*piVar6 == iVar2) goto LAB_004146f6;
    }
  }
  goto LAB_0041472f;
LAB_004146f6:
  iVar2 = *piVar4;
  if (iVar2 != 0) {
    piVar6 = (int *)(*(uint *)(iVar2 + 0x35c) | 0x4000000);
    *(int **)(iVar2 + 0x35c) = piVar6;
    if (*(int *)(iVar2 + 0x18) == 0) {
      for (puVar3 = *(undefined4 **)(iVar2 + 0x14); puVar3 != (undefined4 *)0x0;
          puVar3 = (undefined4 *)puVar3[1]) {
        piVar6 = (int *)*puVar3;
        piVar6[0xd7] = piVar6[0xd7] | 0x4000000;
      }
    }
  }
LAB_0041472f:
  *piVar7 = 0;
  piVar7 = piVar7 + 1;
  local_10 = local_10 + -1;
  if (local_10 == 0) {
    FUN_004493e0(piVar6,*(int *)(param_1 + 0x9ec8));
    DAT_0047770c = 0;
    if (*(void **)(param_1 + 0x9da0) != (void *)0x0) {
      _free(*(void **)(param_1 + 0x9da0));
    }
    *(undefined4 *)(param_1 + 0x9da0) = 0;
    local_4._0_1_ = 4;
    _eh_vector_destructor_iterator_((void *)(param_1 + 0x8094),0x3ac,7,FUN_00401ff0);
    local_4._0_1_ = 3;
    _eh_vector_destructor_iterator_((void *)(param_1 + 0x793c),0x3ac,2,FUN_00401ff0);
    local_4._0_1_ = 2;
    _eh_vector_destructor_iterator_((void *)(param_1 + 0x6a8c),0x3ac,4,FUN_00401ff0);
    local_4._0_1_ = 1;
    _eh_vector_destructor_iterator_((void *)(param_1 + 0x4980),0x3ac,9,FUN_00401ff0);
    local_4 = (uint)local_4._1_3_ << 8;
    _eh_vector_destructor_iterator_((void *)(param_1 + 0x24c8),0x3ac,10,FUN_00401ff0);
    local_4 = 0xffffffff;
    _eh_vector_destructor_iterator_((void *)(param_1 + 0x10),0x3ac,10,FUN_00401ff0);
    ExceptionList = local_c;
    return;
  }
  goto LAB_004146c0;
}

