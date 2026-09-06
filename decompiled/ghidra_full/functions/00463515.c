/* Raw Ghidra reference; not compilable reconstruction. Address: 00463515 */

/* Library Function - Single Match
    ___CxxExceptionFilter
   
   Library: Visual Studio 2003 Release */

int __cdecl ___CxxExceptionFilter(void *param_1,void *param_2,int param_3,void *param_4)

{
  _ptiddata p_Var1;
  int iVar2;
  _s_ThrowInfo *unaff_EBX;
  EHExceptionRecord *pEVar3;
  _s_HandlerType *unaff_ESI;
  uint local_18;
  void *local_14;
  int local_8;
  
  if (param_1 == (void *)0x0) {
    return 0;
  }
  pEVar3 = *(EHExceptionRecord **)param_1;
  if ((param_2 == (void *)0x0) || (*(char *)((int)param_2 + 8) == '\0')) {
    if ((((*(int *)pEVar3 != -0x1f928c9d) || (*(int *)(pEVar3 + 0x10) != 3)) ||
        (((*(int *)(pEVar3 + 0x14) != 0x19930520 && (*(int *)(pEVar3 + 0x14) != 0x19930521)) ||
         (*(int *)(pEVar3 + 0x1c) != 0)))) ||
       (p_Var1 = __getptd(), p_Var1->_unexpected != (void *)0x0)) {
      p_Var1 = __getptd();
      p_Var1->_purecall = (void *)((int)p_Var1->_purecall + 1);
      return 1;
    }
  }
  else if (((*(int *)pEVar3 == -0x1f928c9d) && (*(int *)(pEVar3 + 0x10) == 3)) &&
          ((*(int *)(pEVar3 + 0x14) == 0x19930520 || (*(int *)(pEVar3 + 0x14) == 0x19930521)))) {
    if (*(int *)(pEVar3 + 0x1c) == 0) {
      p_Var1 = __getptd();
      if (p_Var1->_unexpected == (void *)0x0) {
        return 0;
      }
      p_Var1 = __getptd();
      pEVar3 = p_Var1->_unexpected;
    }
    local_18 = param_3 | 0x80000000;
    local_14 = param_2;
    for (local_8 = **(int **)(*(int *)(pEVar3 + 0x1c) + 0xc); 0 < local_8; local_8 = local_8 + -1) {
      iVar2 = TypeMatch(*(_s_HandlerType **)(pEVar3 + 0x1c),(_s_CatchableType *)unaff_ESI,unaff_EBX)
      ;
      if (iVar2 != 0) {
        p_Var1 = __getptd();
        p_Var1->_purecall = (void *)((int)p_Var1->_purecall + 1);
        if (param_4 == (void *)0x0) {
          return 1;
        }
        BuildCatchObject(pEVar3,&local_18,unaff_ESI,(_s_CatchableType *)unaff_EBX);
        return 1;
      }
    }
  }
  return 0;
}

