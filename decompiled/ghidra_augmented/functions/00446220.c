/* Raw Ghidra reference; not compilable reconstruction. Address: 00446220 */

void FUN_00446220(int param_1)

{
  int iVar1;
  uint uVar2;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_00465225;
  local_4 = 2;
  iVar1 = *(int *)(param_1 + 0x72dad4);
  local_c = ExceptionList;
  ExceptionList = &local_c;
  while (iVar1 != 0) {
    iVar1 = *(int *)(iVar1 + 4);
    FUN_00448bb0();
  }
  iVar1 = *(int *)(param_1 + 0x72dadc);
  while (iVar1 != 0) {
    iVar1 = *(int *)(iVar1 + 4);
    FUN_00448bb0();
  }
  uVar2 = (uint)local_4 >> 8;
  local_4 = CONCAT31((int3)uVar2,1);
  _eh_vector_destructor_iterator_((void *)(param_1 + 0x72dae4),0x3ac,0x14,FUN_00401ff0);
  if (*(void **)(param_1 + 0x3ad488) != (void *)0x0) {
    _free(*(void **)(param_1 + 0x3ad488));
  }
  *(undefined4 *)(param_1 + 0x3ad488) = 0;
  local_4 = 0xffffffff;
  _eh_vector_destructor_iterator_((void *)(param_1 + 0x68),0x3ac,0x1000,FUN_00401ff0);
  ExceptionList = local_c;
  return;
}

