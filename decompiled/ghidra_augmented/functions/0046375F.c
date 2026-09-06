/* Raw Ghidra reference; not compilable reconstruction. Address: 0046375F */

/* Library Function - Single Match
    void __cdecl FindHandler(struct EHExceptionRecord *,struct EHRegistrationNode *,struct _CONTEXT
   *,void *,struct _s_FuncInfo const *,unsigned char,int,struct EHRegistrationNode *)
   
   Library: Visual Studio 2003 Release */

void __cdecl
FindHandler(EHExceptionRecord *param_1,EHRegistrationNode *param_2,_CONTEXT *param_3,void *param_4,
           _s_FuncInfo *param_5,uchar param_6,int param_7,EHRegistrationNode *param_8)

{
  int iVar1;
  int iVar2;
  _ptiddata p_Var3;
  int iVar4;
  _s_TryBlockMapEntry *p_Var5;
  int iVar6;
  int unaff_EBX;
  _s_TryBlockMapEntry *unaff_ESI;
  _s_CatchableType *unaff_EDI;
  EHRegistrationNode *pEVar7;
  uint in_stack_ffffffdc;
  int *local_14;
  uint local_10;
  _s_TryBlockMapEntry *local_c;
  undefined1 local_5;
  
  iVar1 = *(int *)(param_2 + 8);
  local_5 = 0;
  if ((iVar1 < -1) || (param_5->maxState <= iVar1)) {
    _inconsistency();
  }
  if (*(int *)param_1 == -0x1f928c9d) {
    if ((*(int *)(param_1 + 0x10) == 3) &&
       (((*(int *)(param_1 + 0x14) == 0x19930520 || (*(int *)(param_1 + 0x14) == 0x19930521)) &&
        (*(int *)(param_1 + 0x1c) == 0)))) {
      p_Var3 = __getptd();
      if (p_Var3->_unexpected == (void *)0x0) {
        return;
      }
      p_Var3 = __getptd();
      param_1 = p_Var3->_unexpected;
      p_Var3 = __getptd();
      param_3 = p_Var3->_translator;
      local_5 = 1;
      iVar4 = _ValidateRead(param_1,1);
      if (iVar4 == 0) {
        _inconsistency();
      }
      if (*(int *)param_1 != -0x1f928c9d) goto LAB_00463938;
      if (((*(int *)(param_1 + 0x10) == 3) &&
          ((*(int *)(param_1 + 0x14) == 0x19930520 || (*(int *)(param_1 + 0x14) == 0x19930521)))) &&
         (*(int *)(param_1 + 0x1c) == 0)) {
        _inconsistency();
      }
    }
    if (((*(int *)param_1 == -0x1f928c9d) && (*(int *)(param_1 + 0x10) == 3)) &&
       ((*(int *)(param_1 + 0x14) == 0x19930520 || (*(int *)(param_1 + 0x14) == 0x19930521)))) {
      p_Var5 = _GetRangeOfTrysToCheck(param_5,param_7,iVar1,&local_10,(uint *)&stack0xffffffdc);
      local_c = p_Var5;
      if (local_10 < in_stack_ffffffdc) {
        do {
          if ((p_Var5->tryLow <= iVar1) && (iVar1 <= p_Var5->tryHigh)) {
            local_c = p_Var5;
            for (iVar4 = p_Var5->nCatches; 0 < iVar4; iVar4 = iVar4 + -1) {
              local_14 = *(int **)(*(int *)(param_1 + 0x1c) + 0xc);
              for (iVar2 = *local_14; 0 < iVar2; iVar2 = iVar2 + -1) {
                local_14 = local_14 + 1;
                pEVar7 = (EHRegistrationNode *)*local_14;
                iVar6 = TypeMatch(*(_s_HandlerType **)(param_1 + 0x1c),unaff_EDI,
                                  (_s_ThrowInfo *)unaff_ESI);
                p_Var5 = local_c;
                if (iVar6 != 0) {
                  CatchIt(param_1,(EHRegistrationNode *)param_3,param_4,param_5,
                          (_s_FuncInfo *)param_7,(_s_HandlerType *)param_8,unaff_EDI,unaff_ESI,
                          unaff_EBX,pEVar7,(uchar)in_stack_ffffffdc);
                  goto LAB_0046390b;
                }
              }
            }
          }
LAB_0046390b:
          local_10 = local_10 + 1;
          p_Var5 = p_Var5 + 1;
          local_c = p_Var5;
        } while (local_10 < in_stack_ffffffdc);
      }
      if (param_6 == '\0') {
        return;
      }
      ___DestructExceptionObject((int)param_1);
      return;
    }
  }
LAB_00463938:
  if (param_6 == '\0') {
    FindHandlerForForeignException(param_1,param_2,param_3,param_4,param_5,iVar1,param_7,param_8);
    return;
  }
                    /* WARNING: Subroutine does not return */
  terminate();
}

