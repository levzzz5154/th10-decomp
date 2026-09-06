/* Raw Ghidra reference; not compilable reconstruction. Address: 00461AF9 */

/* WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog */
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3 */
/* WARNING: Function: __chkstk replaced with injection: alloca_probe */
/* WARNING: Unable to track spacebase fully for stack */
/* WARNING: This function may have set the stack pointer */
/* WARNING: Type propagation algorithm not settling */

int __cdecl
FUN_00461af9(LCID param_1,DWORD param_2,byte *param_3,char *param_4,byte *param_5,char *param_6,
            UINT param_7)

{
  bool bVar1;
  bool bVar2;
  byte *pbVar3;
  int iVar4;
  DWORD DVar5;
  BOOL BVar6;
  BYTE *pBVar7;
  undefined1 *puVar8;
  undefined1 *puVar9;
  int iVar10;
  undefined1 *puVar11;
  undefined1 *puVar12;
  int iVar13;
  UINT UVar14;
  byte *_Memory;
  byte *extraout_EAX;
  UINT UVar15;
  undefined1 *puVar16;
  undefined1 *puVar17;
  undefined1 *puVar18;
  size_t unaff_EDI;
  byte *_Memory_00;
  undefined4 uStackY_84;
  int local_4c;
  byte *local_44;
  byte *local_40;
  byte *local_38;
  _cpinfo local_34;
  uint local_20;
  undefined1 *local_1c;
  undefined4 uStack_c;
  undefined *local_8;
  
  pbVar3 = param_5;
  local_8 = &DAT_0046c9c0;
  uStack_c = 0x461b05;
  local_20 = DAT_00473660 ^ (uint)&stack0xfffffffc;
  local_40 = param_3;
  local_38 = param_5;
  _Memory_00 = (byte *)0x0;
  if (DAT_004776d4 == 0) {
    uStackY_84 = 0x461b38;
    iVar4 = CompareStringW(0,0,L"",1,L"",1);
    if (iVar4 == 0) {
      DVar5 = GetLastError();
      if (DVar5 == 0x78) {
        DAT_004776d4 = 2;
      }
    }
    else {
      DAT_004776d4 = 1;
    }
  }
  if (0 < (int)param_4) {
    param_4 = (char *)_strncnt(param_4,unaff_EDI);
  }
  if (0 < (int)param_6) {
    param_6 = (char *)_strncnt(param_6,unaff_EDI);
  }
  if ((DAT_004776d4 == 2) || (DAT_004776d4 == 0)) {
    local_44 = (byte *)0x0;
    if (param_1 == 0) {
      param_1 = DAT_00477654;
    }
    UVar15 = param_7;
    if (param_7 == 0) {
      UVar15 = DAT_00477664;
    }
    UVar14 = FUN_004601a1(param_1);
    if (UVar14 != 0xffffffff) {
      if (UVar14 == UVar15) {
LAB_00461e40:
        uStackY_84 = 0x461e58;
        iVar4 = CompareStringA(param_1,param_2,(PCNZCH)local_40,(int)param_4,(PCNZCH)local_38,
                               (int)param_6);
        if (_Memory_00 != (byte *)0x0) {
          _free(_Memory_00);
          _free(local_44);
          return iVar4;
        }
        return iVar4;
      }
      uStackY_84 = 0x461e09;
      FUN_004601e8(UVar15,UVar14,(char *)param_3,(uint *)&param_4,(int *)0x0,0);
      if (_Memory != (byte *)0x0) {
        uStackY_84 = 0x461e24;
        FUN_004601e8(UVar15,UVar14,(char *)pbVar3,(uint *)&param_6,(int *)0x0,0);
        _Memory_00 = _Memory;
        local_44 = extraout_EAX;
        local_40 = _Memory;
        local_38 = extraout_EAX;
        if (extraout_EAX != (byte *)0x0) goto LAB_00461e40;
        _free(_Memory);
      }
    }
  }
  else if (DAT_004776d4 == 1) {
    bVar2 = false;
    bVar1 = false;
    local_4c = 0;
    if (param_7 == 0) {
      param_7 = DAT_00477664;
    }
    if ((param_4 == (char *)0x0) || (param_6 == (char *)0x0)) {
      if (param_4 == param_6) {
        return 2;
      }
      if (1 < (int)param_6) {
        return 1;
      }
      if (1 < (int)param_4) {
        return 3;
      }
      BVar6 = GetCPInfo(param_7,&local_34);
      if (BVar6 == 0) {
        return 0;
      }
      if (0 < (int)param_4) {
        if (local_34.MaxCharSize < 2) {
          return 3;
        }
        pBVar7 = local_34.LeadByte;
        while( true ) {
          if (local_34.LeadByte[0] == 0) {
            return 3;
          }
          if (pBVar7[1] == 0) break;
          if ((*pBVar7 <= *param_3) && (*param_3 <= pBVar7[1])) {
            return 2;
          }
          pBVar7 = pBVar7 + 2;
          local_34.LeadByte[0] = *pBVar7;
        }
        return 3;
      }
      if (0 < (int)param_6) {
        if (1 < local_34.MaxCharSize) {
          pBVar7 = local_34.LeadByte;
          while ((local_34.LeadByte[0] != 0 && (pBVar7[1] != 0))) {
            if ((*pBVar7 <= *pbVar3) && (*pbVar3 <= pBVar7[1])) {
              return 2;
            }
            pBVar7 = pBVar7 + 2;
            local_34.LeadByte[0] = *pBVar7;
          }
        }
        return 1;
      }
    }
    uStackY_84 = 0x461c76;
    iVar4 = MultiByteToWideChar(param_7,9,(LPCSTR)param_3,(int)param_4,(LPWSTR)0x0,0);
    if (iVar4 != 0) {
      puVar8 = (undefined1 *)(iVar4 * 2 + 3U & 0xfffffffc);
      iVar10 = -(int)puVar8;
      puVar9 = &stack0xffffff98 + iVar10;
      local_1c = &stack0xffffff98 + iVar10;
      local_8 = (undefined *)0xffffffff;
      if (&stack0xffffff98 == puVar8) {
        *(int *)(&stack0xffffff94 + iVar10) = iVar4 * 2;
        *(undefined4 *)(&stack0xffffff90 + iVar10) = 0x461cce;
        puVar9 = _malloc(*(size_t *)(&stack0xffffff94 + iVar10));
        if (puVar9 == (undefined1 *)0x0) {
          return 0;
        }
        bVar2 = true;
      }
      *(int *)(&stack0xffffff94 + iVar10) = iVar4;
      *(undefined1 **)(&stack0xffffff90 + iVar10) = puVar9;
      *(char **)(&stack0xffffff8c + iVar10) = param_4;
      *(byte **)(&stack0xffffff88 + iVar10) = param_3;
      *(undefined4 *)(&stack0xffffff84 + iVar10) = 1;
      *(UINT *)(&stack0xffffff80 + iVar10) = param_7;
      puVar16 = (undefined1 *)((int)&uStackY_84 + iVar10);
      *(undefined4 *)((int)&uStackY_84 + iVar10) = 0x461cf2;
      iVar10 = MultiByteToWideChar(*(UINT *)(&stack0xffffff80 + iVar10),
                                   *(DWORD *)(&stack0xffffff84 + iVar10),
                                   *(LPCSTR *)(&stack0xffffff88 + iVar10),
                                   *(int *)(&stack0xffffff8c + iVar10),
                                   *(LPWSTR *)(&stack0xffffff90 + iVar10),
                                   *(int *)(&stack0xffffff94 + iVar10));
      puVar8 = puVar16;
      if (iVar10 != 0) {
        *(undefined4 *)(puVar16 + -4) = 0;
        *(undefined4 *)(puVar16 + -8) = 0;
        *(char **)(puVar16 + -0xc) = param_6;
        *(byte **)(puVar16 + -0x10) = pbVar3;
        *(undefined4 *)(puVar16 + -0x14) = 9;
        *(UINT *)(puVar16 + -0x18) = param_7;
        puVar17 = puVar16 + -0x1c;
        *(undefined4 *)(puVar16 + -0x1c) = 0x461d0f;
        iVar10 = MultiByteToWideChar(*(UINT *)(puVar16 + -0x18),*(DWORD *)(puVar16 + -0x14),
                                     *(LPCSTR *)(puVar16 + -0x10),*(int *)(puVar16 + -0xc),
                                     *(LPWSTR *)(puVar16 + -8),*(int *)(puVar16 + -4));
        puVar8 = puVar17;
        if (iVar10 != 0) {
          puVar11 = (undefined1 *)(iVar10 * 2 + 3U & 0xfffffffc);
          *(undefined4 *)(puVar17 + -4) = 0x461d31;
          iVar13 = -(int)puVar11;
          puVar12 = puVar17 + iVar13;
          puVar8 = puVar17 + iVar13;
          local_1c = puVar17 + iVar13;
          local_8 = (undefined *)0xffffffff;
          if (puVar17 == puVar11) {
            sRamfffffffc = iVar10 * 2;
            uRamfffffff8 = 0x461d64;
            puVar12 = _malloc(sRamfffffffc);
            if (puVar12 == (undefined1 *)0x0) goto LAB_00461dab;
            bVar1 = true;
          }
          *(int *)(puVar17 + iVar13 + -4) = iVar10;
          *(undefined1 **)(puVar17 + iVar13 + -8) = puVar12;
          *(char **)(puVar17 + iVar13 + -0xc) = param_6;
          *(byte **)(puVar17 + iVar13 + -0x10) = pbVar3;
          *(undefined4 *)(puVar17 + iVar13 + -0x14) = 1;
          *(UINT *)(puVar17 + iVar13 + -0x18) = param_7;
          puVar18 = puVar17 + iVar13 + -0x1c;
          *(undefined4 *)(puVar17 + iVar13 + -0x1c) = 0x461d85;
          iVar13 = MultiByteToWideChar(*(UINT *)(puVar17 + iVar13 + -0x18),
                                       *(DWORD *)(puVar17 + iVar13 + -0x14),
                                       *(LPCSTR *)(puVar17 + iVar13 + -0x10),
                                       *(int *)(puVar17 + iVar13 + -0xc),
                                       *(LPWSTR *)(puVar17 + iVar13 + -8),
                                       *(int *)(puVar17 + iVar13 + -4));
          puVar8 = puVar18;
          if (iVar13 != 0) {
            *(int *)(puVar18 + -4) = iVar10;
            *(undefined1 **)(puVar18 + -8) = puVar12;
            *(int *)(puVar18 + -0xc) = iVar4;
            *(undefined1 **)(puVar18 + -0x10) = puVar9;
            *(DWORD *)(puVar18 + -0x14) = param_2;
            *(LCID *)(puVar18 + -0x18) = param_1;
            puVar8 = puVar18 + -0x1c;
            *(undefined4 *)(puVar18 + -0x1c) = 0x461d9b;
            local_4c = CompareStringW(*(LCID *)(puVar18 + -0x18),*(DWORD *)(puVar18 + -0x14),
                                      *(PCNZWCH *)(puVar18 + -0x10),*(int *)(puVar18 + -0xc),
                                      *(PCNZWCH *)(puVar18 + -8),*(int *)(puVar18 + -4));
          }
          if (bVar1) {
            *(undefined1 **)(puVar8 + -4) = puVar12;
            *(undefined4 *)(puVar8 + -8) = 0x461daa;
            _free(*(void **)(puVar8 + -4));
          }
        }
      }
LAB_00461dab:
      if (bVar2) {
        *(undefined1 **)(puVar8 + -4) = puVar9;
        *(undefined4 *)(puVar8 + -8) = 0x461db9;
        _free(*(void **)(puVar8 + -4));
        return local_4c;
      }
      return local_4c;
    }
  }
  return 0;
}

