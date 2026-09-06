/* Raw Ghidra reference; not compilable reconstruction. Address: 0045650F */

/* Library Function - Single Match
    __freeptd
   
   Library: Visual Studio 2003 Release */

void __cdecl __freeptd(_ptiddata _Ptd)

{
  if (DAT_00473390 != -1) {
    if (_Ptd == (_ptiddata)0x0) {
      _Ptd = (_ptiddata)(*DAT_00477378)(DAT_00473390);
    }
    __freefls_4(_Ptd);
    (*DAT_0047737c)(DAT_00473390,0);
  }
  return;
}

