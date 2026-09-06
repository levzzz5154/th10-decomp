/* Raw Ghidra reference; not compilable reconstruction. Address: 00461695 */

/* WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog */
/* WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3 */
/* WARNING: Function: __chkstk replaced with injection: alloca_probe */
/* WARNING: Unable to track spacebase fully for stack */
/* Library Function - Single Match
    ___crtGetLocaleInfoA
   
   Library: Visual Studio 2003 Release */

int __cdecl
___crtGetLocaleInfoA
          (_locale_t _Plocinfo,LPCWSTR _LocaleName,LCTYPE _LCType,LPSTR _LpLCData,int _CchData)

{
  int iVar1;
  bool bVar2;
  int iVar3;
  DWORD DVar4;
  undefined1 *puVar5;
  undefined1 *puVar6;
  undefined1 *puVar7;
  undefined4 uStackY_4c;
  int local_20;
  
  if (DAT_004776d0 == 0) {
    uStackY_4c = 0x4616b8;
    iVar3 = GetLocaleInfoW(0,1,(LPWSTR)0x0,0);
    if (iVar3 == 0) {
      DVar4 = GetLastError();
      if (DVar4 == 0x78) {
        DAT_004776d0 = 2;
      }
    }
    else {
      DAT_004776d0 = 1;
    }
  }
  if ((DAT_004776d0 == 2) || (DAT_004776d0 == 0)) {
    uStackY_4c = 0x4617cc;
    iVar3 = GetLocaleInfoA((LCID)_Plocinfo,(LCTYPE)_LocaleName,(LPSTR)_LCType,(int)_LpLCData);
    return iVar3;
  }
  if (DAT_004776d0 == 1) {
    local_20 = 0;
    bVar2 = false;
    if (_CchData == 0) {
      _CchData = DAT_00477664;
    }
    uStackY_4c = 0x461715;
    iVar3 = GetLocaleInfoW((LCID)_Plocinfo,(LCTYPE)_LocaleName,(LPWSTR)0x0,0);
    if (iVar3 != 0) {
      puVar5 = (undefined1 *)(iVar3 * 2 + 3U & 0xfffffffc);
      iVar1 = -(int)puVar5;
      puVar6 = &stack0xffffffc8 + iVar1;
      if (&stack0xffffffc8 == puVar5) {
        *(int *)(&stack0xffffffc4 + iVar1) = iVar3 * 2;
        *(undefined4 *)(&stack0xffffffc0 + iVar1) = 0x461768;
        puVar6 = _malloc(*(size_t *)(&stack0xffffffc4 + iVar1));
        if (puVar6 == (void *)0x0) {
          return 0;
        }
        bVar2 = true;
      }
      *(int *)(&stack0xffffffc4 + iVar1) = iVar3;
      *(undefined1 **)(&stack0xffffffc0 + iVar1) = puVar6;
      *(LPCWSTR *)(&stack0xffffffbc + iVar1) = _LocaleName;
      *(_locale_t *)(&stack0xffffffb8 + iVar1) = _Plocinfo;
      puVar7 = (undefined1 *)((int)&uStackY_4c + iVar1);
      *(undefined4 *)((int)&uStackY_4c + iVar1) = 0x461784;
      iVar3 = GetLocaleInfoW(*(LCID *)(&stack0xffffffb8 + iVar1),
                             *(LCTYPE *)(&stack0xffffffbc + iVar1),
                             *(LPWSTR *)(&stack0xffffffc0 + iVar1),
                             *(int *)(&stack0xffffffc4 + iVar1));
      puVar5 = puVar7;
      if (iVar3 != 0) {
        *(undefined4 *)(puVar7 + -4) = 0;
        *(undefined4 *)(puVar7 + -8) = 0;
        if (_LpLCData == (LPSTR)0x0) {
          *(undefined4 *)(puVar7 + -0xc) = 0;
          *(undefined4 *)(puVar7 + -0x10) = 0;
        }
        else {
          *(LPSTR *)(puVar7 + -0xc) = _LpLCData;
          *(LCTYPE *)(puVar7 + -0x10) = _LCType;
        }
        *(undefined4 *)(puVar7 + -0x14) = 0xffffffff;
        *(undefined1 **)(puVar7 + -0x18) = puVar6;
        *(undefined4 *)(puVar7 + -0x1c) = 0;
        *(int *)(puVar7 + -0x20) = _CchData;
        puVar5 = puVar7 + -0x24;
        *(undefined4 *)(puVar7 + -0x24) = 0x4617a6;
        local_20 = WideCharToMultiByte(*(UINT *)(puVar7 + -0x20),*(DWORD *)(puVar7 + -0x1c),
                                       *(LPCWSTR *)(puVar7 + -0x18),*(int *)(puVar7 + -0x14),
                                       *(LPSTR *)(puVar7 + -0x10),*(int *)(puVar7 + -0xc),
                                       *(LPCSTR *)(puVar7 + -8),*(LPBOOL *)(puVar7 + -4));
      }
      if (bVar2) {
        *(undefined1 **)(puVar5 + -4) = puVar6;
        *(undefined4 *)(puVar5 + -8) = 0x4617b4;
        _free(*(void **)(puVar5 + -4));
        return local_20;
      }
      return local_20;
    }
  }
  return 0;
}

