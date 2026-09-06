/* Raw Ghidra reference; not compilable reconstruction. Address: 0045A16E */

/* Library Function - Single Match
    _wctomb
   
   Library: Visual Studio 2003 Release */

int __cdecl _wctomb(char *_MbCh,wchar_t _WCh)

{
  _ptiddata p_Var1;
  pthreadlocinfo ptVar2;
  int iVar3;
  
  p_Var1 = __getptd();
  ptVar2 = (pthreadlocinfo)p_Var1->_tfpecode;
  if (ptVar2 != (pthreadlocinfo)PTR_DAT_0047320c) {
    ptVar2 = ___updatetlocinfo();
  }
  iVar3 = ___wctomb_mt((int)ptVar2,_MbCh,_WCh);
  return iVar3;
}

