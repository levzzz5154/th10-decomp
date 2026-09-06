/* Raw Ghidra reference; not compilable reconstruction. Address: 0045EE1D */

/* WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog */
/* WARNING: Function: __chkstk replaced with injection: alloca_probe */
/* WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3 */
/* WARNING: Unable to track spacebase fully for stack */

uint __cdecl
FUN_0045ee1d(LCID param_1,uint param_2,LPCSTR param_3,uint param_4,int *param_5,int param_6,
            UINT param_7,int param_8)

{
  bool bVar1;
  bool bVar2;
  int iVar3;
  DWORD DVar4;
  undefined1 *puVar5;
  int iVar6;
  UINT UVar7;
  LPCSTR lpSrcStr;
  int *extraout_EAX;
  uint uVar8;
  undefined1 *puVar9;
  undefined1 *puVar10;
  undefined1 *puVar11;
  undefined1 *puVar12;
  char *pcVar13;
  undefined4 uStackY_78;
  uint local_50;
  int *local_34;
  LPCSTR local_2c;
  size_t local_28;
  undefined1 *local_24;
  undefined1 *local_20;
  undefined1 *local_1c;
  undefined4 uStack_c;
  undefined *local_8;
  
  local_8 = &DAT_0046c648;
  uStack_c = 0x45ee29;
  if (DAT_00477694 == 0) {
    uStackY_78 = 0x45ee4a;
    iVar3 = LCMapStringW(0,0x100,L"",1,(LPWSTR)0x0,0);
    if (iVar3 == 0) {
      DVar4 = GetLastError();
      if (DVar4 == 0x78) {
        DAT_00477694 = 2;
      }
    }
    else {
      DAT_00477694 = 1;
    }
  }
  pcVar13 = param_3;
  uVar8 = param_4;
  if (0 < (int)param_4) {
    do {
      uVar8 = uVar8 - 1;
      if (*pcVar13 == '\0') goto LAB_0045ee83;
      pcVar13 = pcVar13 + 1;
    } while (uVar8 != 0);
    uVar8 = 0xffffffff;
LAB_0045ee83:
    param_4 = param_4 + (-1 - uVar8);
  }
  if ((DAT_00477694 != 2) && (DAT_00477694 != 0)) {
    if (DAT_00477694 == 1) {
      uVar8 = 0;
      bVar2 = false;
      bVar1 = false;
      if (param_7 == 0) {
        param_7 = DAT_00477664;
      }
      uStackY_78 = 0x45eee3;
      iVar3 = MultiByteToWideChar(param_7,(uint)(param_8 != 0) * 8 + 1,param_3,param_4,(LPWSTR)0x0,0
                                 );
      if (iVar3 != 0) {
        puVar5 = (undefined1 *)(iVar3 * 2 + 3U & 0xfffffffc);
        iVar6 = -(int)puVar5;
        local_1c = &stack0xffffffa4 + iVar6;
        local_20 = &stack0xffffffa4 + iVar6;
        local_8 = (undefined *)0xffffffff;
        if (&stack0xffffffa4 == puVar5) {
          *(int *)(&stack0xffffffa0 + iVar6) = iVar3 * 2;
          *(undefined4 *)(&stack0xffffff9c + iVar6) = 0x45ef3c;
          local_20 = _malloc(*(size_t *)(&stack0xffffffa0 + iVar6));
          if (local_20 == (undefined1 *)0x0) {
            return 0;
          }
          bVar2 = true;
        }
        *(int *)(&stack0xffffffa0 + iVar6) = iVar3;
        *(undefined1 **)(&stack0xffffff9c + iVar6) = local_20;
        *(uint *)(&stack0xffffff98 + iVar6) = param_4;
        *(LPCSTR *)(&stack0xffffff94 + iVar6) = param_3;
        *(undefined4 *)(&stack0xffffff90 + iVar6) = 1;
        *(UINT *)(&stack0xffffff8c + iVar6) = param_7;
        puVar9 = (undefined1 *)((int)&uStackY_78 + iVar6);
        *(undefined4 *)((int)&uStackY_78 + iVar6) = 0x45ef64;
        iVar6 = MultiByteToWideChar(*(UINT *)(&stack0xffffff8c + iVar6),
                                    *(DWORD *)(&stack0xffffff90 + iVar6),
                                    *(LPCSTR *)(&stack0xffffff94 + iVar6),
                                    *(int *)(&stack0xffffff98 + iVar6),
                                    *(LPWSTR *)(&stack0xffffff9c + iVar6),
                                    *(int *)(&stack0xffffffa0 + iVar6));
        puVar5 = puVar9;
        if (iVar6 != 0) {
          *(undefined4 *)(puVar9 + -4) = 0;
          *(undefined4 *)(puVar9 + -8) = 0;
          *(int *)(puVar9 + -0xc) = iVar3;
          *(undefined1 **)(puVar9 + -0x10) = local_20;
          *(uint *)(puVar9 + -0x14) = param_2;
          *(LCID *)(puVar9 + -0x18) = param_1;
          puVar10 = puVar9 + -0x1c;
          *(undefined4 *)(puVar9 + -0x1c) = 0x45ef7e;
          uVar8 = LCMapStringW(*(LCID *)(puVar9 + -0x18),*(DWORD *)(puVar9 + -0x14),
                               *(LPCWSTR *)(puVar9 + -0x10),*(int *)(puVar9 + -0xc),
                               *(LPWSTR *)(puVar9 + -8),*(int *)(puVar9 + -4));
          puVar5 = puVar10;
          if (uVar8 != 0) {
            if ((param_2 & 0x400) == 0) {
              puVar5 = (undefined1 *)(uVar8 * 2 + 3 & 0xfffffffc);
              *(undefined4 *)(puVar10 + -4) = 0x45efd3;
              iVar6 = -(int)puVar5;
              local_1c = puVar10 + iVar6;
              local_24 = puVar10 + iVar6;
              local_8 = (undefined *)0xffffffff;
              if (puVar10 == puVar5) {
                *(uint *)(puVar10 + iVar6 + -4) = uVar8 * 2;
                *(undefined4 *)(puVar10 + iVar6 + -8) = 0x45f00a;
                local_24 = _malloc(*(size_t *)(puVar10 + iVar6 + -4));
                puVar5 = puVar10 + iVar6;
                if (local_24 == (undefined1 *)0x0) goto LAB_0045f052;
                bVar1 = true;
              }
              *(uint *)(puVar10 + iVar6 + -4) = uVar8;
              *(undefined1 **)(puVar10 + iVar6 + -8) = local_24;
              *(int *)(puVar10 + iVar6 + -0xc) = iVar3;
              *(undefined1 **)(puVar10 + iVar6 + -0x10) = local_20;
              *(uint *)(puVar10 + iVar6 + -0x14) = param_2;
              *(LCID *)(puVar10 + iVar6 + -0x18) = param_1;
              puVar12 = puVar10 + iVar6 + -0x1c;
              *(undefined4 *)(puVar10 + iVar6 + -0x1c) = 0x45f02d;
              iVar3 = LCMapStringW(*(LCID *)(puVar10 + iVar6 + -0x18),
                                   *(DWORD *)(puVar10 + iVar6 + -0x14),
                                   *(LPCWSTR *)(puVar10 + iVar6 + -0x10),
                                   *(int *)(puVar10 + iVar6 + -0xc),
                                   *(LPWSTR *)(puVar10 + iVar6 + -8),*(int *)(puVar10 + iVar6 + -4))
              ;
              puVar5 = puVar12;
              if (iVar3 != 0) {
                *(undefined4 *)(puVar12 + -4) = 0;
                *(undefined4 *)(puVar12 + -8) = 0;
                if (param_6 == 0) {
                  *(undefined4 *)(puVar12 + -0xc) = 0;
                  *(undefined4 *)(puVar12 + -0x10) = 0;
                }
                else {
                  *(int *)(puVar12 + -0xc) = param_6;
                  *(int **)(puVar12 + -0x10) = param_5;
                }
                *(uint *)(puVar12 + -0x14) = uVar8;
                *(undefined1 **)(puVar12 + -0x18) = local_24;
                *(undefined4 *)(puVar12 + -0x1c) = 0;
                *(UINT *)(puVar12 + -0x20) = param_7;
                puVar5 = puVar12 + -0x24;
                *(undefined4 *)(puVar12 + -0x24) = 0x45f050;
                uVar8 = WideCharToMultiByte(*(UINT *)(puVar12 + -0x20),*(DWORD *)(puVar12 + -0x1c),
                                            *(LPCWSTR *)(puVar12 + -0x18),*(int *)(puVar12 + -0x14),
                                            *(LPSTR *)(puVar12 + -0x10),*(int *)(puVar12 + -0xc),
                                            *(LPCSTR *)(puVar12 + -8),*(LPBOOL *)(puVar12 + -4));
              }
            }
            else if ((param_6 != 0) && ((int)uVar8 <= param_6)) {
              *(int *)(puVar10 + -4) = param_6;
              *(int **)(puVar10 + -8) = param_5;
              *(int *)(puVar10 + -0xc) = iVar3;
              *(undefined1 **)(puVar10 + -0x10) = local_20;
              *(uint *)(puVar10 + -0x14) = param_2;
              *(LCID *)(puVar10 + -0x18) = param_1;
              puVar11 = puVar10 + -0x1c;
              *(undefined4 *)(puVar10 + -0x1c) = 0x45efb9;
              LCMapStringW(*(LCID *)(puVar10 + -0x18),*(DWORD *)(puVar10 + -0x14),
                           *(LPCWSTR *)(puVar10 + -0x10),*(int *)(puVar10 + -0xc),
                           *(LPWSTR *)(puVar10 + -8),*(int *)(puVar10 + -4));
              puVar5 = puVar11;
            }
          }
        }
LAB_0045f052:
        if (bVar1) {
          *(undefined1 **)(puVar5 + -4) = local_24;
          *(undefined4 *)(puVar5 + -8) = 0x45f05f;
          _free(*(void **)(puVar5 + -4));
        }
        if (bVar2) {
          *(undefined1 **)(puVar5 + -4) = local_20;
          *(undefined4 *)(puVar5 + -8) = 0x45f06d;
          _free(*(void **)(puVar5 + -4));
          return uVar8;
        }
        return uVar8;
      }
    }
    return 0;
  }
  local_2c = (LPCSTR)0x0;
  pcVar13 = (char *)0x0;
  local_34 = (int *)0x0;
  bVar1 = false;
  if (param_1 == 0) {
    param_1 = DAT_00477654;
  }
  if (param_7 == 0) {
    param_7 = DAT_00477664;
  }
  UVar7 = FUN_004601a1(param_1);
  if (UVar7 == 0xffffffff) {
    return 0;
  }
  if (UVar7 == param_7) {
    uStackY_78 = 0x45f1c5;
    local_50 = LCMapStringA(param_1,param_2,param_3,param_4,(LPSTR)param_5,param_6);
    goto LAB_0045f1c7;
  }
  uStackY_78 = 0x45f0cd;
  FUN_004601e8(param_7,UVar7,param_3,&param_4,(int *)0x0,0);
  if (lpSrcStr == (LPCSTR)0x0) {
    return 0;
  }
  uStackY_78 = 0x45f0e9;
  local_28 = LCMapStringA(param_1,param_2,lpSrcStr,param_4,(LPSTR)0x0,0);
  if (local_28 != 0) {
    local_8 = (undefined *)0x0;
    local_1c = &stack0xffffffa4;
    pcVar13 = &stack0xffffffa4;
    _memset(&stack0xffffffa4,0,local_28);
    local_8 = (undefined *)0xffffffff;
    if (&stack0x00000000 == (undefined1 *)0x5c) {
      pcVar13 = _malloc(local_28);
      if (pcVar13 != (char *)0x0) {
        _memset(pcVar13,0,local_28);
        bVar1 = true;
        goto LAB_0045f154;
      }
    }
    else {
LAB_0045f154:
      uStackY_78 = 0x45f16a;
      local_28 = LCMapStringA(param_1,param_2,lpSrcStr,param_4,pcVar13,local_28);
      if (local_28 != 0) {
        uStackY_78 = 0x45f18b;
        FUN_004601e8(UVar7,param_7,pcVar13,&local_28,param_5,param_6);
        local_50 = -(uint)(extraout_EAX != (int *)0x0) & local_28;
        local_34 = extraout_EAX;
        goto LAB_0045f19f;
      }
    }
    local_50 = 0;
  }
LAB_0045f19f:
  local_2c = lpSrcStr;
  if (bVar1) {
    _free(pcVar13);
  }
LAB_0045f1c7:
  if (local_2c != (LPCSTR)0x0) {
    _free(local_2c);
  }
  if (local_34 != (int *)0x0) {
    if (param_5 != local_34) {
      _free(local_34);
      return local_50;
    }
    return local_50;
  }
  return local_50;
}

