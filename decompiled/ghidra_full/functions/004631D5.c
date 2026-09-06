/* Raw Ghidra reference; not compilable reconstruction. Address: 004631D5 */

/* WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog */
/* WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3 */
/* Library Function - Single Match
    void * __cdecl CallCatchBlock(struct EHExceptionRecord *,struct EHRegistrationNode *,struct
   _CONTEXT *,struct _s_FuncInfo const *,void *,int,unsigned long)
   
   Library: Visual Studio 2003 Release */

void * __cdecl
CallCatchBlock(EHExceptionRecord *param_1,EHRegistrationNode *param_2,_CONTEXT *param_3,
              _s_FuncInfo *param_4,void *param_5,int param_6,ulong param_7)

{
  _ptiddata p_Var1;
  void *in_ECX;
  FrameInfo local_54 [8];
  undefined4 local_4c;
  void *local_48;
  void *local_44;
  FrameInfo *local_40;
  undefined4 local_3c;
  void *local_24;
  undefined4 uStack_c;
  undefined *local_8;
  
  local_8 = &DAT_0046caf0;
  uStack_c = 0x4631e1;
  local_4c = 0;
  local_3c = *(undefined4 *)(param_2 + -4);
  local_40 = _CreateFrameInfo(local_54,*(void **)(param_1 + 0x18));
  p_Var1 = __getptd();
  local_44 = p_Var1->_unexpected;
  p_Var1 = __getptd();
  local_48 = p_Var1->_translator;
  p_Var1 = __getptd();
  p_Var1->_unexpected = param_1;
  p_Var1 = __getptd();
  p_Var1->_translator = param_3;
  local_8 = (undefined *)0x1;
  local_24 = _CallCatchBlock2(param_2,param_4,in_ECX,(int)param_5,param_6);
  local_8 = (undefined *)0xffffffff;
  FUN_0046332a();
  return local_24;
}

