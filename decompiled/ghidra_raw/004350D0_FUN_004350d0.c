/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x004350D0
 * Tracking name: FUN_004350d0
 * Ghidra name: FUN_004350d0
 * Tracked span: 336 bytes
 */


int * FUN_004350d0(int *param_1,int param_2,int param_3)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  int *piVar4;
  void *pvVar5;
  uint uVar6;
  uint uVar7;
  int *piVar8;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  piVar8 = param_1;
  local_4 = 0xffffffff;
  puStack_8 = &LAB_004653cb;
  local_c = ExceptionList;
  iVar1 = param_2 + 1;
  ExceptionList = &local_c;
  piVar3 = operator_new(iVar1 * 0x10 + 4);
  local_4 = 0;
  if (piVar3 != (int *)0x0) {
    piVar2 = piVar3 + 1;
    *piVar3 = iVar1;
    _eh_vector_constructor_iterator_
              (piVar2,0x10,iVar1,(_func_void_void_ptr *)&LAB_004352c0,FUN_00435250);
    if (piVar2 != (int *)0x0) {
      if (0 < param_2) {
        piVar3 = piVar3 + 3;
        param_1 = (int *)param_2;
        do {
          piVar4 = piVar8;
          do {
            iVar1 = *piVar4;
            piVar4 = (int *)((int)piVar4 + 1);
          } while ((char)iVar1 != '\0');
          pvVar5 = _malloc((int)piVar4 + (1 - ((int)piVar8 + 1)));
          if (pvVar5 != (void *)0x0) {
            piVar4 = piVar8;
            do {
              iVar1 = *piVar4;
              *(char *)(((int)pvVar5 - (int)piVar8) + (int)piVar4) = (char)iVar1;
              piVar4 = (int *)((int)piVar4 + 1);
            } while ((char)iVar1 != '\0');
          }
          piVar3[-2] = (int)pvVar5;
          piVar4 = piVar8;
          do {
            iVar1 = *piVar4;
            piVar4 = (int *)((int)piVar4 + 1);
          } while ((char)iVar1 != '\0');
          uVar6 = (int)piVar4 + (1 - ((int)piVar8 + 1));
          uVar7 = uVar6 & 0x80000003;
          if ((int)uVar7 < 0) {
            uVar7 = (uVar7 - 1 | 0xfffffffc) + 1;
          }
          if (uVar7 != 0) {
            uVar6 = uVar6 + (4 - uVar7);
          }
          piVar8 = (int *)((int)piVar8 + uVar6);
          piVar3[-1] = *piVar8;
          *piVar3 = piVar8[1];
          piVar3[1] = piVar8[2];
          piVar8 = piVar8 + 3;
          piVar3 = piVar3 + 4;
          param_1 = (int *)((int)param_1 + -1);
        } while (param_1 != (int *)0x0);
      }
      piVar2[param_2 * 4 + 1] = param_3;
      piVar2[param_2 * 4 + 2] = 0;
      ExceptionList = local_c;
      return piVar2;
    }
  }
  ExceptionList = local_c;
  return (int *)0x0;
}

