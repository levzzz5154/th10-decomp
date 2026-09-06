/* Raw Ghidra reference; not compilable reconstruction. Address: 0045AA93 */

/* WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog */
/* WARNING: Function: __chkstk replaced with injection: alloca_probe */
/* WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3 */
/* Library Function - Single Match
    __store_winword
   
   Library: Visual Studio 2003 Release */

undefined4 __cdecl
__store_winword(int param_1,int param_2,undefined2 *param_3,int *param_4,uint *param_5,int param_6)

{
  byte bVar1;
  undefined1 *puVar2;
  undefined1 *puVar3;
  undefined1 *_Memory;
  int iVar4;
  byte *pbVar5;
  uint uVar6;
  uint uVar7;
  short local_4c;
  short local_4a;
  undefined2 local_46;
  undefined2 local_44;
  undefined2 local_42;
  undefined2 local_40;
  undefined2 local_3e;
  undefined1 *local_3c;
  int local_38;
  code *local_34;
  size_t local_30;
  int local_2c;
  byte *local_28;
  byte *local_24;
  char local_1d;
  undefined1 *local_1c;
  undefined4 uStack_c;
  undefined *local_8;
  
  local_8 = &DAT_0046b710;
  uStack_c = 0x45aa9f;
  if (param_2 == 0) {
    local_24 = *(byte **)(param_6 + 0xa0);
  }
  else if (param_2 == 1) {
    local_24 = *(byte **)(param_6 + 0xa4);
  }
  else {
    local_24 = *(byte **)(param_6 + 0xa8);
  }
  if (*(int *)(param_6 + 0xb0) != 1) {
    local_34 = GetDateFormatA_exref;
    if (param_2 == 2) {
      local_34 = GetTimeFormatA_exref;
    }
    local_4c = param_3[10] + 0x76c;
    local_4a = param_3[8] + 1;
    local_46 = param_3[6];
    local_44 = param_3[4];
    local_42 = param_3[2];
    local_40 = *param_3;
    local_3e = 0;
    local_30 = (*local_34)(*(undefined4 *)(param_6 + 0xac),0,&local_4c,local_24,0,0);
    if (local_30 != 0) {
      local_38 = 0;
      local_1c = &stack0xffffffa8;
      local_3c = &stack0xffffffa8;
      _Memory = &stack0xffffffa8;
      local_8 = (undefined *)0xffffffff;
      puVar2 = &stack0xffffffa8;
      puVar3 = &stack0xffffffa8;
      if (&stack0x00000000 == (undefined1 *)0x58) {
        _Memory = _malloc(local_30);
        if (_Memory == (undefined1 *)0x0) goto LAB_0045abf3;
        local_38 = 1;
        puVar2 = local_3c;
        puVar3 = local_1c;
      }
      local_1c = puVar3;
      local_3c = puVar2;
      local_28 = _Memory;
      iVar4 = (*local_34)(*(undefined4 *)(param_6 + 0xac),0,&local_4c,local_24,_Memory,local_30);
      while ((iVar4 = iVar4 + -1, 0 < iVar4 && (*param_5 != 0))) {
        *(byte *)*param_4 = *local_28;
        *param_4 = *param_4 + 1;
        local_28 = local_28 + 1;
        *param_5 = *param_5 - 1;
      }
      if (local_38 == 0) {
        return 1;
      }
      _free(_Memory);
      return 1;
    }
  }
LAB_0045abf3:
  bVar1 = *local_24;
  pbVar5 = local_24;
  do {
    if ((bVar1 == 0) || (*param_5 == 0)) {
      return 1;
    }
    local_1d = '\0';
    local_2c = 0;
    local_28 = pbVar5;
    uVar7 = 0;
    do {
      uVar6 = uVar7;
      local_28 = local_28 + 1;
      uVar7 = uVar6 + 1;
    } while (*local_28 == bVar1);
    local_24 = pbVar5;
    if ((char)bVar1 < 'e') {
      if (bVar1 == 100) {
        if (uVar6 == 0) {
          local_2c = 1;
        }
        else if (uVar6 != 1) {
          if (uVar6 == 2) {
            local_1d = 'a';
          }
          else if (uVar6 == 3) {
            local_1d = 'A';
          }
          goto LAB_0045aeab;
        }
        local_1d = 'd';
LAB_0045aeab:
        if (local_1d != '\0') {
          iVar4 = __expandtime(param_4,param_1,param_3,param_6,local_2c);
          if (iVar4 == 0) {
            return 0;
          }
          goto LAB_0045ae5d;
        }
        bVar1 = *local_24;
        if (((*(byte *)(*(int *)(param_1 + 0x48) + 1 + (uint)bVar1 * 2) & 0x80) != 0) &&
           (1 < *param_5)) {
          local_24 = local_24 + 1;
          if (*local_24 == 0) {
            return 0;
          }
          *(byte *)*param_4 = bVar1;
          *param_4 = *param_4 + 1;
          *param_5 = *param_5 - 1;
        }
        *(byte *)*param_4 = *local_24;
        *param_4 = *param_4 + 1;
        local_24 = local_24 + 1;
        *param_5 = *param_5 - 1;
      }
      else {
        if (bVar1 != 0x27) {
          if (bVar1 == 0x41) {
LAB_0045ac54:
            iVar4 = ___ascii_stricmp((char *)pbVar5,"am/pm");
            if (iVar4 == 0) {
              local_28 = pbVar5 + 5;
            }
            else {
              iVar4 = ___ascii_stricmp((char *)pbVar5,"a/p");
              if (iVar4 == 0) {
                local_28 = pbVar5 + 3;
              }
            }
            local_1d = 'p';
          }
          else if (bVar1 == 0x48) {
            if (uVar6 == 0) {
              local_2c = 1;
            }
            else if (uVar7 != 2) goto LAB_0045aeab;
            local_1d = 'H';
          }
          else if (bVar1 == 0x4d) {
            if (uVar6 == 0) {
              local_2c = 1;
            }
            else if (uVar6 != 1) {
              if (uVar6 == 2) {
                local_1d = 'b';
              }
              else if (uVar6 == 3) {
                local_1d = 'B';
              }
              goto LAB_0045aeab;
            }
            local_1d = 'm';
          }
          else if (bVar1 == 0x61) goto LAB_0045ac54;
          goto LAB_0045aeab;
        }
        local_24 = pbVar5 + uVar7;
        if ((uVar7 & 1) != 0) {
          while( true ) {
            bVar1 = *local_24;
            if ((bVar1 == 0) || (*param_5 == 0)) goto LAB_0045af0b;
            if (bVar1 == 0x27) break;
            if (((*(byte *)(*(int *)(param_1 + 0x48) + 1 + (uint)bVar1 * 2) & 0x80) != 0) &&
               (1 < *param_5)) {
              local_24 = local_24 + 1;
              if (*local_24 == 0) {
                return 0;
              }
              *(byte *)*param_4 = bVar1;
              *param_4 = *param_4 + 1;
              *param_5 = *param_5 - 1;
            }
            *(byte *)*param_4 = *local_24;
            *param_4 = *param_4 + 1;
            local_24 = local_24 + 1;
            *param_5 = *param_5 - 1;
          }
          local_24 = local_24 + 1;
        }
      }
    }
    else {
      if (bVar1 == 0x68) {
        if (uVar6 == 0) {
          local_2c = 1;
        }
        else if (uVar7 != 2) goto LAB_0045aeab;
        local_1d = 'I';
        goto LAB_0045aeab;
      }
      if (bVar1 == 0x6d) {
        if (uVar6 == 0) {
          local_2c = 1;
        }
        else if (uVar7 != 2) goto LAB_0045aeab;
        local_1d = 'M';
        goto LAB_0045aeab;
      }
      if (bVar1 == 0x73) {
        if (uVar6 == 0) {
          local_2c = 1;
        }
        else if (uVar7 != 2) goto LAB_0045aeab;
        local_1d = 'S';
        goto LAB_0045aeab;
      }
      if (bVar1 != 0x74) {
        if (bVar1 == 0x79) {
          if (uVar6 == 1) {
            local_1d = 'y';
          }
          else if (uVar6 == 3) {
            local_1d = 'Y';
          }
        }
        goto LAB_0045aeab;
      }
      if (*(int *)(param_3 + 4) < 0xc) {
        pbVar5 = *(byte **)(param_6 + 0x98);
      }
      else {
        pbVar5 = *(byte **)(param_6 + 0x9c);
      }
      if ((uVar7 == 1) && (*param_5 != 0)) {
        bVar1 = *pbVar5;
        if (((*(byte *)(*(int *)(param_1 + 0x48) + 1 + (uint)bVar1 * 2) & 0x80) != 0) &&
           (1 < *param_5)) {
          pbVar5 = pbVar5 + 1;
          if (*pbVar5 == 0) {
            return 0;
          }
          *(byte *)*param_4 = bVar1;
          *param_4 = *param_4 + 1;
          *param_5 = *param_5 - 1;
        }
        *(byte *)*param_4 = *pbVar5;
        *param_4 = *param_4 + 1;
        *param_5 = *param_5 - 1;
      }
      else {
        while( true ) {
          bVar1 = *pbVar5;
          if ((bVar1 == 0) || (*param_5 == 0)) break;
          if (((*(byte *)(*(int *)(param_1 + 0x48) + 1 + (uint)bVar1 * 2) & 0x80) != 0) &&
             (1 < *param_5)) {
            pbVar5 = pbVar5 + 1;
            if (*pbVar5 == 0) {
              return 0;
            }
            *(byte *)*param_4 = bVar1;
            *param_4 = *param_4 + 1;
            *param_5 = *param_5 - 1;
          }
          *(byte *)*param_4 = *pbVar5;
          *param_4 = *param_4 + 1;
          pbVar5 = pbVar5 + 1;
          *param_5 = *param_5 - 1;
        }
      }
LAB_0045ae5d:
      local_24 = local_28;
    }
LAB_0045af0b:
    bVar1 = *local_24;
    pbVar5 = local_24;
  } while( true );
}

