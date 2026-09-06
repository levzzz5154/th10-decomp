/* Raw Ghidra reference; not compilable reconstruction. Address: 004636A1 */

/* Library Function - Single Match
    void __cdecl FindHandlerForForeignException(struct EHExceptionRecord *,struct EHRegistrationNode
   *,struct _CONTEXT *,void *,struct _s_FuncInfo const *,int,int,struct EHRegistrationNode *)
   
   Library: Visual Studio 2003 Release */

void __cdecl
FindHandlerForForeignException
          (EHExceptionRecord *param_1,EHRegistrationNode *param_2,_CONTEXT *param_3,void *param_4,
          _s_FuncInfo *param_5,int param_6,int param_7,EHRegistrationNode *param_8)

{
  TypeDescriptor *pTVar1;
  _ptiddata p_Var2;
  int iVar3;
  _s_TryBlockMapEntry *p_Var4;
  _s_CatchableType *unaff_EBX;
  int unaff_ESI;
  _s_TryBlockMapEntry *unaff_EDI;
  EHRegistrationNode *extraout_var;
  EHRegistrationNode *pEVar5;
  EHRegistrationNode *extraout_var_00;
  EHRegistrationNode *pEVar6;
  
  if ((*(int *)param_1 != -0x7ffffffd) &&
     (((p_Var2 = __getptd(), pEVar5 = extraout_var, pEVar6 = extraout_var_00,
       p_Var2->_NLG_dwCode == 0 ||
       (iVar3 = _CallSETranslator(param_1,param_2,param_3,param_4,param_5,param_7,param_8),
       iVar3 == 0)) &&
      (p_Var4 = _GetRangeOfTrysToCheck
                          (param_5,param_7,param_6,(uint *)&stack0xfffffff8,(uint *)&stack0xfffffff4
                          ), pEVar6 < pEVar5)))) {
    do {
      if (((p_Var4->tryLow <= param_6) && (param_6 <= p_Var4->tryHigh)) &&
         ((pTVar1 = p_Var4->pHandlerArray[p_Var4->nCatches + -1].pType,
          pTVar1 == (TypeDescriptor *)0x0 || (*(char *)&pTVar1[1].pVFTable == '\0')))) {
        CatchIt(param_1,(EHRegistrationNode *)param_3,param_4,param_5,(_s_FuncInfo *)param_7,
                (_s_HandlerType *)param_8,unaff_EBX,unaff_EDI,unaff_ESI,pEVar5,(uchar)pEVar6);
      }
      pEVar6 = pEVar6 + 1;
      p_Var4 = p_Var4 + 1;
    } while (pEVar6 < pEVar5);
  }
  return;
}

