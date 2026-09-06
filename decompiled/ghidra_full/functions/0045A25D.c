/* Raw Ghidra reference; not compilable reconstruction. Address: 0045A25D */

/* WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog */
/* WARNING: Function: __chkstk replaced with injection: alloca_probe */
/* WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3 */
/* WARNING: Unable to track spacebase fully for stack */
/* Library Function - Single Match
    ___crtGetStringTypeA
   
   Library: Visual Studio 2003 Release */

BOOL __cdecl
___crtGetStringTypeA
          (_locale_t _Plocinfo,DWORD _DWInfoType,LPCSTR _LpSrcStr,int _CchSrc,LPWORD _LpCharType,
          int _Code_page,BOOL _BError)

{
  int iVar1;
  bool bVar2;
  BOOL BVar3;
  DWORD DVar4;
  int iVar5;
  undefined1 *puVar6;
  int *piVar7;
  LPWORD pWVar8;
  void *extraout_EAX;
  LCID Locale;
  undefined1 *puVar9;
  void *_Memory;
  LPWORD pWVar10;
  undefined4 uStackY_58;
  BOOL local_28;
  WORD local_20 [2];
  undefined1 *local_1c;
  undefined4 uStack_c;
  undefined *local_8;
  
  local_8 = &DAT_0046b5c8;
  uStack_c = 0x45a269;
  _Memory = (void *)0x0;
  if (DAT_00477618 == 0) {
    BVar3 = GetStringTypeW(1,L"",1,local_20);
    if (BVar3 == 0) {
      DVar4 = GetLastError();
      if (DVar4 == 0x78) {
        DAT_00477618 = 2;
      }
    }
    else {
      DAT_00477618 = 1;
    }
  }
  if ((DAT_00477618 == 2) || (DAT_00477618 == 0)) {
    Locale = _Code_page;
    if (_Code_page == 0) {
      Locale = DAT_00477654;
    }
    pWVar10 = _LpCharType;
    if (_LpCharType == (LPWORD)0x0) {
      pWVar10 = DAT_00477664;
    }
    pWVar8 = (LPWORD)FUN_004601a1(Locale);
    if (pWVar8 != (LPWORD)0xffffffff) {
      if (pWVar8 != pWVar10) {
        uStackY_58 = 0x45a3e0;
        FUN_004601e8((UINT)pWVar10,(UINT)pWVar8,(char *)_DWInfoType,(uint *)&_LpSrcStr,(int *)0x0,0)
        ;
        _Memory = extraout_EAX;
        _DWInfoType = (DWORD)extraout_EAX;
        if (extraout_EAX == (void *)0x0) {
          return 0;
        }
      }
      BVar3 = GetStringTypeA(Locale,(DWORD)_Plocinfo,(LPCSTR)_DWInfoType,(int)_LpSrcStr,
                             (LPWORD)_CchSrc);
      if (_Memory != (void *)0x0) {
        _free(_Memory);
        return BVar3;
      }
      return BVar3;
    }
  }
  else if (DAT_00477618 == 1) {
    local_28 = 0;
    bVar2 = false;
    if (_LpCharType == (LPWORD)0x0) {
      _LpCharType = DAT_00477664;
    }
    uStackY_58 = 0x45a2fb;
    iVar5 = MultiByteToWideChar((UINT)_LpCharType,(uint)(_BError != 0) * 8 + 1,(LPCSTR)_DWInfoType,
                                (int)_LpSrcStr,(LPWSTR)0x0,0);
    if (iVar5 != 0) {
      local_8 = (undefined *)0x0;
      puVar6 = (undefined1 *)(iVar5 * 2 + 3U & 0xfffffffc);
      iVar1 = -(int)puVar6;
      piVar7 = (int *)(&stack0xffffffc4 + iVar1);
      local_1c = &stack0xffffffc4 + iVar1;
      *(int *)((int)local_20 + iVar1 + -0x20) = iVar5 * 2;
      *(undefined4 *)(&stack0xffffffbc + iVar1) = 0;
      *(undefined1 **)(&stack0xffffffb8 + iVar1) = &stack0xffffffc4 + iVar1;
      *(undefined4 *)(&stack0xffffffb4 + iVar1) = 0x45a32d;
      _memset(*(void **)(&stack0xffffffb8 + iVar1),*(int *)(&stack0xffffffbc + iVar1),
              *(size_t *)((int)local_20 + iVar1 + -0x20));
      local_8 = (undefined *)0xffffffff;
      if (&stack0xffffffc4 == puVar6) {
        *(int *)((int)local_20 + iVar1 + -0x20) = iVar5;
        *(undefined4 *)(&stack0xffffffbc + iVar1) = 2;
        *(undefined4 *)(&stack0xffffffb8 + iVar1) = 0x45a357;
        piVar7 = FUN_0045794d(*(uint *)(&stack0xffffffbc + iVar1),
                              *(uint *)((int)local_20 + iVar1 + -0x20));
        if (piVar7 == (int *)0x0) {
          return 0;
        }
        bVar2 = true;
      }
      *(int *)((int)local_20 + iVar1 + -0x20) = iVar5;
      *(int **)(&stack0xffffffbc + iVar1) = piVar7;
      *(LPCSTR *)(&stack0xffffffb8 + iVar1) = _LpSrcStr;
      *(DWORD *)(&stack0xffffffb4 + iVar1) = _DWInfoType;
      *(undefined4 *)(&stack0xffffffb0 + iVar1) = 1;
      *(LPWORD *)(&stack0xffffffac + iVar1) = _LpCharType;
      puVar9 = (undefined1 *)((int)&uStackY_58 + iVar1);
      *(undefined4 *)((int)&uStackY_58 + iVar1) = 0x45a379;
      iVar5 = MultiByteToWideChar(*(UINT *)(&stack0xffffffac + iVar1),
                                  *(DWORD *)(&stack0xffffffb0 + iVar1),
                                  *(LPCSTR *)(&stack0xffffffb4 + iVar1),
                                  *(int *)(&stack0xffffffb8 + iVar1),
                                  *(LPWSTR *)(&stack0xffffffbc + iVar1),
                                  *(int *)((int)local_20 + iVar1 + -0x20));
      puVar6 = puVar9;
      if (iVar5 != 0) {
        *(int *)(puVar9 + -4) = _CchSrc;
        *(int *)(puVar9 + -8) = iVar5;
        *(int **)(puVar9 + -0xc) = piVar7;
        *(_locale_t *)(puVar9 + -0x10) = _Plocinfo;
        puVar6 = puVar9 + -0x14;
        *(undefined4 *)(puVar9 + -0x14) = 0x45a38b;
        local_28 = GetStringTypeW(*(DWORD *)(puVar9 + -0x10),*(LPCWSTR *)(puVar9 + -0xc),
                                  *(int *)(puVar9 + -8),*(LPWORD *)(puVar9 + -4));
      }
      if (bVar2) {
        *(int **)(puVar6 + -4) = piVar7;
        *(undefined4 *)(puVar6 + -8) = 0x45a39a;
        _free(*(void **)(puVar6 + -4));
        return local_28;
      }
      return local_28;
    }
  }
  return 0;
}

