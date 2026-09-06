/* Raw Ghidra reference; not compilable reconstruction. Address: 0045C40F */

/* Library Function - Single Match
    _crtGetLocaleInfoA@16
   
   Library: Visual Studio 2003 Release */

int crtGetLocaleInfoA(uint param_1,undefined1 *param_2,char *param_3,int param_4)

{
  int iVar1;
  int iVar2;
  char *_Source;
  int iVar3;
  
  iVar3 = 0;
  iVar2 = 0x1a;
  do {
    iVar1 = (iVar2 + iVar3) / 2;
    if (param_1 == *(uint *)(&UNK_0046b720 + iVar1 * 0x2c)) {
      if (param_2 == (undefined1 *)0x1) {
        _Source = &DAT_0046b724 + iVar1 * 0x2c;
      }
      else if (param_2 == (undefined1 *)0x3) {
        _Source = &DAT_0046b730 + iVar1 * 0x2c;
      }
      else if (param_2 == (undefined1 *)0x7) {
        _Source = &DAT_0046b738 + iVar1 * 0x2c;
      }
      else if (param_2 == (undefined1 *)0xb) {
        _Source = &DAT_0046b73c + iVar1 * 0x2c;
      }
      else if (param_2 == (undefined1 *)0x1001) {
        _Source = *(char **)(&UNK_0046b72c + iVar1 * 0x2c);
      }
      else if (param_2 == (undefined1 *)0x1002) {
        _Source = *(char **)(&UNK_0046b734 + iVar1 * 0x2c);
      }
      else {
        if (param_2 != &DAT_00001004) break;
        _Source = &DAT_0046b744 + iVar1 * 0x2c;
      }
      if ((_Source != (char *)0x0) && (0 < param_4)) {
        _strncpy(param_3,_Source,param_4 - 1);
        param_3[param_4 + -1] = '\0';
        return 1;
      }
      break;
    }
    if (param_1 < *(uint *)(&UNK_0046b720 + iVar1 * 0x2c)) {
      iVar2 = iVar1 + -1;
    }
    else {
      iVar3 = iVar1 + 1;
    }
  } while (iVar3 <= iVar2);
  iVar2 = GetLocaleInfoA(param_1,(LCTYPE)param_2,param_3,param_4);
  return iVar2;
}

