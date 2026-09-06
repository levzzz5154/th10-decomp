/* Raw Ghidra reference; not compilable reconstruction. Address: 0045AFE0 */

/* Library Function - Single Match
    __Strftime
   
   Library: Visual Studio 2003 Release */

size_t __cdecl __Strftime(char *param_1,size_t _Maxsize,char *param_3,tm *param_4,void *param_5)

{
  _ptiddata p_Var1;
  pthreadlocinfo ptVar2;
  size_t sVar3;
  
  p_Var1 = __getptd();
  ptVar2 = (pthreadlocinfo)p_Var1->_tfpecode;
  if (ptVar2 != (pthreadlocinfo)PTR_DAT_0047320c) {
    ptVar2 = ___updatetlocinfo();
  }
  sVar3 = FUN_0045af1d((int)ptVar2,(byte *)param_1,_Maxsize,(byte *)param_3,(undefined2 *)param_4,
                       (uint)param_5);
  return sVar3;
}

