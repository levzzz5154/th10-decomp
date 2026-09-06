/* Raw Ghidra reference; not compilable reconstruction. Address: 004629EB */

/* Library Function - Single Match
    struct FrameInfo * __cdecl _CreateFrameInfo(struct FrameInfo *,void *)
   
   Library: Visual Studio 2003 Release */

FrameInfo * __cdecl _CreateFrameInfo(FrameInfo *param_1,void *param_2)

{
  _ptiddata p_Var1;
  
  *(void **)param_1 = param_2;
  p_Var1 = __getptd();
  *(void **)(param_1 + 4) = p_Var1->_curexception;
  p_Var1 = __getptd();
  p_Var1->_curexception = param_1;
  return param_1;
}

