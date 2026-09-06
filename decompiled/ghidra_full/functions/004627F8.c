/* Raw Ghidra reference; not compilable reconstruction. Address: 004627F8 */

/* Library Function - Single Match
    int __cdecl _CallSETranslator(struct EHExceptionRecord *,struct EHRegistrationNode *,void *,void
   *,struct _s_FuncInfo const *,int,struct EHRegistrationNode *)
   
   Library: Visual Studio 2003 Release */

int __cdecl
_CallSETranslator(EHExceptionRecord *param_1,EHRegistrationNode *param_2,void *param_3,void *param_4
                 ,_s_FuncInfo *param_5,int param_6,EHRegistrationNode *param_7)

{
  _ptiddata p_Var1;
  undefined4 uVar2;
  EHExceptionRecord **ppEVar3;
  int local_38;
  EHExceptionRecord *local_34;
  void *local_30;
  undefined4 *local_2c;
  code *local_28;
  undefined4 local_24;
  _s_FuncInfo *local_20;
  EHRegistrationNode *local_1c;
  int local_18;
  EHRegistrationNode *local_14;
  undefined1 *local_10;
  undefined1 *local_c;
  int local_8;
  
  local_c = &stack0xfffffffc;
  local_10 = &stack0xffffffc4;
  if (param_1 == (EHExceptionRecord *)0x123) {
    *(undefined4 *)param_2 = 0x462893;
    local_38 = 1;
  }
  else {
    local_28 = TranslatorGuardHandler;
    local_24 = DAT_00473660;
    local_20 = param_5;
    local_1c = param_2;
    local_18 = param_6;
    local_14 = param_7;
    local_8 = 0;
    local_2c = ExceptionList;
    ExceptionList = &local_2c;
    local_34 = param_1;
    local_30 = param_3;
    ppEVar3 = &local_34;
    uVar2 = *(undefined4 *)param_1;
    p_Var1 = __getptd();
    (*(code *)p_Var1->_NLG_dwCode)(uVar2,ppEVar3);
    local_38 = 0;
    if (local_8 != 0) {
      *local_2c = *(undefined4 *)ExceptionList;
    }
    ExceptionList = local_2c;
  }
  return local_38;
}

