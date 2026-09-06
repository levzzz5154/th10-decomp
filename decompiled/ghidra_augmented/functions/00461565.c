/* Raw Ghidra reference; not compilable reconstruction. Address: 00461565 */

/* WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog */
/* WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3 */
/* WARNING: Function: __chkstk replaced with injection: alloca_probe */
/* WARNING: Unable to track spacebase fully for stack */
/* Library Function - Single Match
    ___crtGetLocaleInfoW
   
   Library: Visual Studio 2003 Release */

int __cdecl ___crtGetLocaleInfoW(LCID param_1,LCTYPE param_2,LPWSTR param_3,int param_4,int param_5)

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
  
  if (DAT_004776cc == 0) {
    uStackY_4c = 0x461588;
    iVar3 = GetLocaleInfoW(0,1,(LPWSTR)0x0,0);
    if (iVar3 == 0) {
      DVar4 = GetLastError();
      if (DVar4 == 0x78) {
        DAT_004776cc = 2;
      }
    }
    else {
      DAT_004776cc = 1;
    }
  }
  if (DAT_004776cc == 1) {
    uStackY_4c = 0x4615c4;
    iVar3 = GetLocaleInfoW(param_1,param_2,param_3,param_4);
    return iVar3;
  }
  if ((DAT_004776cc == 2) || (DAT_004776cc == 0)) {
    local_20 = 0;
    bVar2 = false;
    if (param_5 == 0) {
      param_5 = DAT_00477664;
    }
    uStackY_4c = 0x4615f3;
    iVar3 = GetLocaleInfoA(param_1,param_2,(LPSTR)0x0,0);
    if (iVar3 != 0) {
      puVar5 = (undefined1 *)(iVar3 + 3U & 0xfffffffc);
      iVar1 = -(int)puVar5;
      puVar6 = &stack0xffffffc8 + iVar1;
      if (&stack0xffffffc8 == puVar5) {
        *(int *)(&stack0xffffffc4 + iVar1) = iVar3;
        *(undefined4 *)(&stack0xffffffc0 + iVar1) = 0x461640;
        puVar6 = _malloc(*(size_t *)(&stack0xffffffc4 + iVar1));
        if (puVar6 == (void *)0x0) {
          return 0;
        }
        bVar2 = true;
      }
      *(int *)(&stack0xffffffc4 + iVar1) = iVar3;
      *(undefined1 **)(&stack0xffffffc0 + iVar1) = puVar6;
      *(LCTYPE *)(&stack0xffffffbc + iVar1) = param_2;
      *(LCID *)(&stack0xffffffb8 + iVar1) = param_1;
      puVar7 = (undefined1 *)((int)&uStackY_4c + iVar1);
      *(undefined4 *)((int)&uStackY_4c + iVar1) = 0x46165a;
      iVar3 = GetLocaleInfoA(*(LCID *)(&stack0xffffffb8 + iVar1),
                             *(LCTYPE *)(&stack0xffffffbc + iVar1),
                             *(LPSTR *)(&stack0xffffffc0 + iVar1),*(int *)(&stack0xffffffc4 + iVar1)
                            );
      puVar5 = puVar7;
      if (iVar3 != 0) {
        if (param_4 == 0) {
          *(undefined4 *)(puVar7 + -4) = 0;
          *(undefined4 *)(puVar7 + -8) = 0;
        }
        else {
          *(int *)(puVar7 + -4) = param_4;
          *(LPWSTR *)(puVar7 + -8) = param_3;
        }
        *(undefined4 *)(puVar7 + -0xc) = 0xffffffff;
        *(undefined1 **)(puVar7 + -0x10) = puVar6;
        *(undefined4 *)(puVar7 + -0x14) = 1;
        *(int *)(puVar7 + -0x18) = param_5;
        puVar5 = puVar7 + -0x1c;
        *(undefined4 *)(puVar7 + -0x1c) = 0x46167a;
        local_20 = MultiByteToWideChar(*(UINT *)(puVar7 + -0x18),*(DWORD *)(puVar7 + -0x14),
                                       *(LPCSTR *)(puVar7 + -0x10),*(int *)(puVar7 + -0xc),
                                       *(LPWSTR *)(puVar7 + -8),*(int *)(puVar7 + -4));
      }
      if (bVar2) {
        *(undefined1 **)(puVar5 + -4) = puVar6;
        *(undefined4 *)(puVar5 + -8) = 0x461688;
        _free(*(void **)(puVar5 + -4));
        return local_20;
      }
      return local_20;
    }
  }
  return 0;
}

