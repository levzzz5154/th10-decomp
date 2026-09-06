/* Raw Ghidra reference; not compilable reconstruction. Address: 0045E375 */

/* Library Function - Single Match
    _mbtowc
   
   Library: Visual Studio 2003 Release */

int __cdecl _mbtowc(wchar_t *_DstCh,char *_SrcCh,size_t _SrcSizeInBytes)

{
  _ptiddata p_Var1;
  pthreadlocinfo ptVar2;
  int iVar3;
  
  p_Var1 = __getptd();
  ptVar2 = (pthreadlocinfo)p_Var1->_tfpecode;
  if (ptVar2 != (pthreadlocinfo)PTR_DAT_0047320c) {
    ptVar2 = ___updatetlocinfo();
  }
  iVar3 = ___mbtowc_mt((int)ptVar2,_DstCh,(byte *)_SrcCh,_SrcSizeInBytes);
  return iVar3;
}

