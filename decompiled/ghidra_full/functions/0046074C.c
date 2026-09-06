/* Raw Ghidra reference; not compilable reconstruction. Address: 0046074C */

/* Library Function - Single Match
    __i64toa
   
   Libraries: Visual Studio 2003 Release, Visual Studio 2005 Release */

char * __cdecl __i64toa(longlong _Val,char *_DstBuf,int _Radix)

{
  int iVar1;
  
  iVar1 = 0;
  if (((_Radix == 10) && (_Val < 0x100000000)) && (_Val < 0)) {
    iVar1 = 1;
  }
  FID_conflict__x64toa_20((int)_Val,_Val._4_4_,_Radix,iVar1);
  return _DstBuf;
}

