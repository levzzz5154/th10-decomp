/* Raw Ghidra reference; not compilable reconstruction. Address: 0046054E */

/* Library Function - Single Match
    __stricmp
   
   Library: Visual Studio 2003 Release */

int __cdecl __stricmp(char *_Str1,char *_Str2)

{
  _ptiddata p_Var1;
  pthreadlocinfo ptVar2;
  int iVar3;
  void *pvVar4;
  void *this;
  void *extraout_ECX;
  void *extraout_ECX_00;
  void *this_00;
  
  p_Var1 = __getptd();
  ptVar2 = (pthreadlocinfo)p_Var1->_tfpecode;
  this = extraout_ECX;
  if (ptVar2 != (pthreadlocinfo)PTR_DAT_0047320c) {
    ptVar2 = ___updatetlocinfo();
    this = extraout_ECX_00;
  }
  if (ptVar2->lc_category[0].wlocale == (wchar_t *)0x0) {
    iVar3 = ___ascii_stricmp(_Str1,_Str2);
  }
  else {
    do {
      pvVar4 = (void *)___tolower_mt(this,(int)ptVar2,(uint)(byte)*_Str1);
      _Str1 = _Str1 + 1;
      this = (void *)___tolower_mt(this_00,(int)ptVar2,(uint)(byte)*_Str2);
      _Str2 = _Str2 + 1;
      if (pvVar4 == (void *)0x0) break;
    } while (pvVar4 == this);
    iVar3 = (int)pvVar4 - (int)this;
  }
  return iVar3;
}

