/* Raw Ghidra reference; not compilable reconstruction. Address: 00456898 */

/* Library Function - Single Match
    _isxdigit
   
   Library: Visual Studio 2003 Release */

int __cdecl _isxdigit(int _C)

{
  _ptiddata p_Var1;
  pthreadlocinfo ptVar2;
  uint uVar3;
  void *extraout_ECX;
  void *extraout_ECX_00;
  void *this;
  
  p_Var1 = __getptd();
  ptVar2 = (pthreadlocinfo)p_Var1->_tfpecode;
  this = extraout_ECX;
  if (ptVar2 != (pthreadlocinfo)PTR_DAT_0047320c) {
    ptVar2 = ___updatetlocinfo();
    this = extraout_ECX_00;
  }
  if (1 < (int)ptVar2->lc_category[1].refcount) {
    uVar3 = ___isctype_mt(this,(int)ptVar2,_C,0x80);
    return uVar3;
  }
  return *(byte *)((int)ptVar2->lc_category[3].refcount + _C * 2) & 0x80;
}

