/* Raw Ghidra reference; not compilable reconstruction. Address: 0046276D */

/* Library Function - Single Match
    ___CxxFrameHandler
   
   Library: Visual Studio 2003 Release */

undefined4 __cdecl
___CxxFrameHandler(EHExceptionRecord *param_1,EHRegistrationNode *param_2,_CONTEXT *param_3,
                  void *param_4)

{
  _s_FuncInfo *in_EAX;
  undefined4 uVar1;
  
  uVar1 = ___InternalCxxFrameHandler
                    (param_1,param_2,param_3,param_4,in_EAX,0,(EHRegistrationNode *)0x0,'\0');
  return uVar1;
}

