/* Raw Ghidra reference; not compilable reconstruction. Address: 00456BE8 */

/* WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog */
/* WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3 */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    __tzset_lk
   
   Library: Visual Studio 2003 Release */

void __tzset_lk(void)

{
  char cVar1;
  char cVar2;
  UINT CodePage;
  uint *_Str1;
  int iVar3;
  size_t sVar4;
  long lVar5;
  DWORD DVar6;
  uint *_Str;
  int local_20 [3];
  undefined1 local_14 [8];
  undefined4 uStack_c;
  undefined *local_8;
  
  local_8 = &DAT_0046aab0;
  uStack_c = 0x456bf4;
  __lock(7);
  CodePage = DAT_00477664;
  local_8 = (undefined *)0x0;
  DAT_0047743c = 0;
  DAT_004735c4 = 0xffffffff;
  DAT_004735b8 = 0xffffffff;
  _Str1 = (uint *)__getenv_lk("TZ");
  if ((_Str1 == (uint *)0x0) || ((char)*_Str1 == '\0')) {
    if (DAT_00477440 != (uint *)0x0) {
      _free(DAT_00477440);
      DAT_00477440 = (uint *)0x0;
    }
    DVar6 = GetTimeZoneInformation((LPTIME_ZONE_INFORMATION)&DAT_00477390);
    if (DVar6 != 0xffffffff) {
      DAT_0047743c = 1;
      _DAT_00473520 = DAT_00477390 * 0x3c;
      if (DAT_004773d6 != 0) {
        _DAT_00473520 = _DAT_00473520 + DAT_004773e4 * 0x3c;
      }
      if ((DAT_0047742a == 0) || (DAT_00477438 == 0)) {
        DAT_00473524 = 0;
        DAT_00473528 = 0;
      }
      else {
        DAT_00473524 = 1;
        DAT_00473528 = (DAT_00477438 - DAT_004773e4) * 0x3c;
      }
      iVar3 = WideCharToMultiByte(CodePage,0,(LPCWSTR)&DAT_00477394,-1,PTR_DAT_004735b0,0x3f,
                                  (LPCSTR)0x0,local_20);
      if ((iVar3 == 0) || (local_20[0] != 0)) {
        *PTR_DAT_004735b0 = 0;
      }
      else {
        PTR_DAT_004735b0[0x3f] = 0;
      }
      iVar3 = WideCharToMultiByte(CodePage,0,(LPCWSTR)&DAT_004773e8,-1,PTR_DAT_004735b4,0x3f,
                                  (LPCSTR)0x0,local_20);
      if ((iVar3 == 0) || (local_20[0] != 0)) {
        *PTR_DAT_004735b4 = 0;
      }
      else {
        PTR_DAT_004735b4[0x3f] = 0;
      }
    }
  }
  else {
    if (DAT_00477440 != (uint *)0x0) {
      iVar3 = _strcmp((char *)_Str1,(char *)DAT_00477440);
      if (iVar3 == 0) goto LAB_00456dec;
      if (DAT_00477440 != (uint *)0x0) {
        _free(DAT_00477440);
      }
    }
    sVar4 = _strlen((char *)_Str1);
    DAT_00477440 = _malloc(sVar4 + 1);
    if (DAT_00477440 != (uint *)0x0) {
      FUN_0045bd80(DAT_00477440,_Str1);
      local_8 = (undefined *)0xffffffff;
      FUN_00456e03();
      _strncpy(PTR_DAT_004735b0,(char *)_Str1,3);
      PTR_DAT_004735b0[3] = 0;
      _Str = (uint *)((int)_Str1 + 3);
      cVar1 = *(char *)_Str;
      if (cVar1 == '-') {
        _Str = _Str1 + 1;
      }
      lVar5 = _atol((char *)_Str);
      _DAT_00473520 = lVar5 * 0xe10;
      for (; (cVar2 = (char)*_Str, cVar2 == '+' || (('/' < cVar2 && (cVar2 < ':'))));
          _Str = (uint *)((int)_Str + 1)) {
      }
      if ((char)*_Str == ':') {
        _Str = (uint *)((int)_Str + 1);
        lVar5 = _atol((char *)_Str);
        _DAT_00473520 = _DAT_00473520 + lVar5 * 0x3c;
        for (; ('/' < (char)*_Str && ((char)*_Str < ':')); _Str = (uint *)((int)_Str + 1)) {
        }
        if ((char)*_Str == ':') {
          _Str = (uint *)((int)_Str + 1);
          lVar5 = _atol((char *)_Str);
          _DAT_00473520 = _DAT_00473520 + lVar5;
          for (; ('/' < (char)*_Str && ((char)*_Str < ':')); _Str = (uint *)((int)_Str + 1)) {
          }
        }
      }
      if (cVar1 == '-') {
        _DAT_00473520 = -_DAT_00473520;
      }
      DAT_00473524 = (int)(char)*_Str;
      if (DAT_00473524 != 0) {
        _strncpy(PTR_DAT_004735b4,(char *)_Str,3);
        PTR_DAT_004735b4[3] = 0;
        return;
      }
      *PTR_DAT_004735b4 = 0;
      return;
    }
  }
LAB_00456dec:
  __local_unwind2((int)local_14,-1);
  return;
}

