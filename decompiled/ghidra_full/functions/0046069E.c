/* Raw Ghidra reference; not compilable reconstruction. Address: 0046069E */

/* Library Function - Single Match
    __ltoa
   
   Library: Visual Studio 2003 Release */

char * __cdecl __ltoa(long _Value,char *_Dest,int _Radix)

{
  int iVar1;
  
  iVar1 = 0;
  if ((_Radix == 10) && (_Value < 0)) {
    iVar1 = 1;
  }
  xtoa(_Radix,iVar1);
  return _Dest;
}

