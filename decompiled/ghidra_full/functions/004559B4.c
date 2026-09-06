/* Raw Ghidra reference; not compilable reconstruction. Address: 004559B4 */

/* Library Function - Single Match
    ___lc_strtolc
   
   Library: Visual Studio 2003 Release */

undefined4 __cdecl ___lc_strtolc(char *param_1,char *param_2)

{
  char cVar1;
  size_t _Count;
  char *_Str;
  char *_Dest;
  
  _Str = param_2;
  _memset(param_1,0,0x90);
  if (*param_2 != '\0') {
    if ((*param_2 != '.') || (param_2[1] == '\0')) {
      param_2 = (char *)0x0;
      do {
        _Count = _strcspn(_Str,"_.,");
        if (_Count == 0) {
          return 0xffffffff;
        }
        cVar1 = _Str[_Count];
        if (param_2 == (char *)0x0) {
          if (0x3f < _Count) {
            return 0xffffffff;
          }
          _Dest = param_1;
          if (cVar1 == '.') {
            return 0xffffffff;
          }
        }
        else if (param_2 == (char *)0x1) {
          if (0x3f < _Count) {
            return 0xffffffff;
          }
          if (cVar1 == '_') {
            return 0xffffffff;
          }
          _Dest = param_1 + 0x40;
        }
        else {
          if (param_2 != (char *)0x2) {
            return 0xffffffff;
          }
          if (0xf < _Count) {
            return 0xffffffff;
          }
          if ((cVar1 != '\0') && (cVar1 != ',')) {
            return 0xffffffff;
          }
          _Dest = param_1 + 0x80;
        }
        _strncpy(_Dest,_Str,_Count);
        if ((cVar1 == ',') || (cVar1 == '\0')) {
          return 0;
        }
        param_2 = param_2 + 1;
        _Str = _Str + _Count + 1;
      } while( true );
    }
    _strncpy(param_1 + 0x80,param_2 + 1,0xf);
    param_1[0x8f] = '\0';
  }
  return 0;
}

