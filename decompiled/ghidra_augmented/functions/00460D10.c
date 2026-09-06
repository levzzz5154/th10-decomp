/* Raw Ghidra reference; not compilable reconstruction. Address: 00460D10 */

/* Library Function - Single Match
    __fptostr
   
   Library: Visual Studio 2003 Release */

errno_t __cdecl __fptostr(char *_Buf,size_t _SizeInBytes,int _Digits,STRFLT _PtFlt)

{
  char *_Str;
  char *_Dst;
  char *pcVar1;
  size_t sVar2;
  char *pcVar3;
  char cVar4;
  
  _Dst = _Buf;
  pcVar3 = *(char **)(_Digits + 0xc);
  _Str = _Buf + 1;
  *_Buf = '0';
  pcVar1 = _Str;
  if (0 < (int)_SizeInBytes) {
    _Buf = (char *)_SizeInBytes;
    _SizeInBytes = 0;
    do {
      cVar4 = *pcVar3;
      if (cVar4 == '\0') {
        cVar4 = '0';
      }
      else {
        pcVar3 = pcVar3 + 1;
      }
      *pcVar1 = cVar4;
      pcVar1 = pcVar1 + 1;
      _Buf = _Buf + -1;
    } while (_Buf != (char *)0x0);
  }
  *pcVar1 = '\0';
  if ((-1 < (int)_SizeInBytes) && ('4' < *pcVar3)) {
    while (pcVar1 = pcVar1 + -1, *pcVar1 == '9') {
      *pcVar1 = '0';
    }
    *pcVar1 = *pcVar1 + '\x01';
  }
  if (*_Dst == '1') {
    *(int *)(_Digits + 4) = *(int *)(_Digits + 4) + 1;
  }
  else {
    sVar2 = _strlen(_Str);
    pcVar1 = _memmove(_Dst,_Str,sVar2 + 1);
  }
  return (errno_t)pcVar1;
}

