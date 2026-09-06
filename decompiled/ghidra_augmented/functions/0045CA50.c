/* Raw Ghidra reference; not compilable reconstruction. Address: 0045CA50 */

/* Library Function - Single Match
    ___get_qualified_locale
   
   Library: Visual Studio 2003 Release */

BOOL __cdecl ___get_qualified_locale(LPLC_STRINGS _LpInStr,UINT *_LpCodePage,LPLC_STRINGS _LpOutStr)

{
  LCID LVar1;
  undefined2 uVar2;
  bool bVar3;
  undefined3 extraout_var;
  uint _Value;
  BOOL BVar4;
  int iVar5;
  
  if (DAT_00477648 == (code *)0x0) {
    if (DAT_00477470 == 2) {
      DAT_00477648 = GetLocaleInfoA_exref;
    }
    else {
      DAT_00477648 = crtGetLocaleInfoA;
    }
  }
  if (_LpInStr == (LPLC_STRINGS)0x0) {
LAB_0045cb2a:
    _GetLcidFromDefault();
LAB_0045cb2f:
    if (DAT_00477628 == 0) {
      return 0;
    }
  }
  else {
    DAT_0047763c = _LpInStr->szLanguage + 0x20;
    DAT_00477644 = _LpInStr;
    if ((DAT_0047763c != (wchar_t *)0x0) && ((char)*DAT_0047763c != '\0')) {
      _TranslateName(0x46bd50,0x16,&DAT_0047763c);
    }
    DAT_00477628 = 0;
    if ((DAT_00477644 == (LPLC_STRINGS)0x0) || ((char)DAT_00477644->szLanguage[0] == '\0')) {
      if ((DAT_0047763c == (wchar_t *)0x0) || ((char)*DAT_0047763c == '\0')) goto LAB_0045cb2a;
      _GetLcidFromCountry();
      goto LAB_0045cb2f;
    }
    if ((DAT_0047763c == (wchar_t *)0x0) || ((char)*DAT_0047763c == '\0')) {
      _GetLcidFromLanguage();
    }
    else {
      _GetLcidFromLangCountry();
    }
    if (DAT_00477628 == 0) {
      bVar3 = _TranslateName(0x46bf00,0x40,&DAT_00477644);
      if (CONCAT31(extraout_var,bVar3) != 0) {
        if ((DAT_0047763c == (wchar_t *)0x0) || ((char)*DAT_0047763c == '\0')) {
          _GetLcidFromLanguage();
        }
        else {
          _GetLcidFromLangCountry();
        }
      }
      goto LAB_0045cb2f;
    }
  }
  _Value = FUN_0045c377((char *)_LpInStr->szCountry);
  if (((_Value == 0) || (BVar4 = IsValidCodePage(_Value & 0xffff), BVar4 == 0)) ||
     (BVar4 = IsValidLocale(DAT_0047762c,1), LVar1 = DAT_0047762c, BVar4 == 0)) {
LAB_0045cbff:
    BVar4 = 0;
  }
  else {
    if (_LpCodePage != (UINT *)0x0) {
      uVar2 = (undefined2)DAT_00477630;
      *(short *)_LpCodePage = (short)DAT_0047762c;
      *(undefined2 *)((int)_LpCodePage + 2) = uVar2;
      *(short *)(_LpCodePage + 1) = (short)_Value;
    }
    if (_LpOutStr != (LPLC_STRINGS)0x0) {
      if ((short)*_LpCodePage == 0x814) {
        FUN_0045bd80((uint *)_LpOutStr,(uint *)"Norwegian-Nynorsk");
      }
      else {
        iVar5 = (*DAT_00477648)(LVar1,0x1001,_LpOutStr,0x40);
        if (iVar5 == 0) goto LAB_0045cbff;
      }
      iVar5 = (*DAT_00477648)(DAT_00477630,0x1002,_LpOutStr->szLanguage + 0x20,0x40);
      if (iVar5 == 0) goto LAB_0045cbff;
      __itoa(_Value,(char *)_LpOutStr->szCountry,10);
    }
    BVar4 = 1;
  }
  return BVar4;
}

