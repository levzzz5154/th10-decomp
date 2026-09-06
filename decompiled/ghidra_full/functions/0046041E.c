/* Raw Ghidra reference; not compilable reconstruction. Address: 0046041E */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined4 __cdecl FUN_0046041e(int param_1,_locale_t param_2,LPCWSTR param_3,char *param_4)

{
  byte bVar1;
  bool bVar2;
  size_t _Size;
  DWORD DVar3;
  LPSTR _LpLCData;
  char *_Source;
  char *_Dest;
  int iVar4;
  byte *pbVar5;
  char local_88 [28];
  undefined1 local_6c [100];
  uint local_8;
  
  local_8 = DAT_00473660 ^ (uint)local_6c;
  if (param_1 != 1) {
    if (param_1 != 0) {
      return 0xffffffff;
    }
    pbVar5 = &DAT_004776c4;
    iVar4 = ___crtGetLocaleInfoW((LCID)param_2,(LCTYPE)param_3,(LPWSTR)&DAT_004776c4,4,0);
    if (iVar4 != 0) {
      *param_4 = '\0';
      do {
        bVar1 = *pbVar5;
        iVar4 = _isdigit((uint)bVar1);
        if (iVar4 == 0) {
          return 0;
        }
        pbVar5 = pbVar5 + 2;
        *param_4 = *param_4 * '\n' + bVar1 + -0x30;
      } while ((int)pbVar5 < 0x4776cc);
      return 0;
    }
    return 0xffffffff;
  }
  _Source = local_88;
  bVar2 = false;
  _Size = ___crtGetLocaleInfoA(param_2,param_3,(LCTYPE)_Source,(LPSTR)0x80,0);
  if (_Size == 0) {
    DVar3 = GetLastError();
    if (DVar3 != 0x7a) {
      return 0xffffffff;
    }
    _LpLCData = (LPSTR)___crtGetLocaleInfoA(param_2,param_3,0,(LPSTR)0x0,0);
    if (_LpLCData == (LPSTR)0x0) {
      return 0xffffffff;
    }
    _Source = _malloc((size_t)_LpLCData);
    if (_Source == (char *)0x0) {
      return 0xffffffff;
    }
    bVar2 = true;
    _Size = ___crtGetLocaleInfoA(param_2,param_3,(LCTYPE)_Source,_LpLCData,0);
    if (_Size == 0) goto LAB_004604cd;
  }
  _Dest = _malloc(_Size);
  *(char **)param_4 = _Dest;
  if (_Dest != (char *)0x0) {
    _strncpy(_Dest,_Source,_Size);
    if (bVar2) {
      _free(_Source);
    }
    return 0;
  }
  if (!bVar2) {
    return 0xffffffff;
  }
LAB_004604cd:
  _free(_Source);
  return 0xffffffff;
}

