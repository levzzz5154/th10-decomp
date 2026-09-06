/* Raw Ghidra reference; not compilable reconstruction. Address: 00454ED7 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Type propagation algorithm not settling */

int __cdecl FUN_00454ed7(undefined4 param_1,byte *param_2,wchar_t *param_3)

{
  byte bVar1;
  short *psVar2;
  wchar_t *pwVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int extraout_ECX;
  uint uVar7;
  byte bVar8;
  wchar_t *pwVar9;
  bool bVar10;
  undefined8 uVar11;
  wchar_t *pwVar12;
  undefined4 local_264;
  undefined4 local_260;
  size_t local_258;
  int local_254;
  undefined4 local_250;
  int local_24c;
  int local_248;
  wchar_t *local_244;
  int local_240;
  int local_23c;
  undefined4 local_238;
  byte *local_234;
  int local_230;
  undefined1 local_22c;
  char local_22b;
  int local_228;
  size_t local_224;
  wchar_t *local_220;
  int local_21c;
  wchar_t *local_218;
  uint local_214;
  wchar_t local_210 [22];
  undefined1 local_1e4 [467];
  undefined2 local_11;
  uint local_8;
  
  local_8 = DAT_00473660 ^ (uint)local_1e4;
  bVar8 = *param_2;
  local_254 = 0;
  local_224 = 0;
  local_228 = 0;
  local_244 = (wchar_t *)0x0;
  local_238 = param_1;
  do {
    if ((bVar8 == 0) || (local_234 = param_2 + 1, local_228 < 0)) {
      return local_228;
    }
    if (((char)bVar8 < ' ') || ('x' < (char)bVar8)) {
      uVar4 = 0;
    }
    else {
      uVar4 = (int)(char)(&DAT_0046a770)[(char)bVar8] & 0xf;
    }
    local_254 = (int)(char)(&DAT_0046a790)[uVar4 * 8 + local_254] >> 4;
    local_218 = param_3;
    switch(local_254) {
    case 0:
switchD_00454f6e_caseD_0:
      local_240 = 0;
      if ((PTR_DAT_004739d8[(uint)bVar8 * 2 + 1] & 0x80) != 0) {
        write_char();
        local_234 = param_2 + 2;
      }
      write_char();
      break;
    case 1:
      local_21c = -1;
      local_250 = 0;
      local_248 = 0;
      local_23c = 0;
      local_230 = 0;
      local_214 = 0;
      local_240 = 0;
      break;
    case 2:
      if (bVar8 == 0x20) {
        local_214 = local_214 | 2;
      }
      else if (bVar8 == 0x23) {
        local_214 = local_214 | 0x80;
      }
      else if (bVar8 == 0x2b) {
        local_214 = local_214 | 1;
      }
      else if (bVar8 == 0x2d) {
        local_214 = local_214 | 4;
      }
      else if (bVar8 == 0x30) {
        local_214 = local_214 | 8;
      }
      break;
    case 3:
      if (bVar8 == 0x2a) {
        local_23c = *(int *)param_3;
        local_218 = param_3 + 2;
        if (local_23c < 0) {
          local_214 = local_214 | 4;
          local_23c = -local_23c;
        }
      }
      else {
        local_23c = (char)bVar8 + -0x30 + local_23c * 10;
      }
      break;
    case 4:
      local_21c = 0;
      break;
    case 5:
      if (bVar8 == 0x2a) {
        local_21c = *(int *)param_3;
        local_218 = param_3 + 2;
        if (local_21c < 0) {
          local_21c = -1;
        }
      }
      else {
        local_21c = (char)bVar8 + -0x30 + local_21c * 10;
      }
      break;
    case 6:
      if (bVar8 == 0x49) {
        bVar1 = *local_234;
        if ((bVar1 == 0x36) && (param_2[2] == 0x34)) {
          local_234 = param_2 + 3;
          local_214 = local_214 | 0x8000;
        }
        else if ((bVar1 == 0x33) && (param_2[2] == 0x32)) {
          local_234 = param_2 + 3;
          local_214 = local_214 & 0xffff7fff;
        }
        else if (((((bVar1 != 100) && (bVar1 != 0x69)) && (bVar1 != 0x6f)) &&
                 ((bVar1 != 0x75 && (bVar1 != 0x78)))) && (bVar1 != 0x58)) {
          local_254 = 0;
          goto switchD_00454f6e_caseD_0;
        }
      }
      else if (bVar8 == 0x68) {
        local_214 = local_214 | 0x20;
      }
      else if (bVar8 == 0x6c) {
        local_214 = local_214 | 0x10;
      }
      else if (bVar8 == 0x77) {
        local_214 = local_214 | 0x800;
      }
      break;
    case 7:
      if ((char)bVar8 < 'h') {
        if ((char)bVar8 < 'e') {
          if ((char)bVar8 < 'Y') {
            if (bVar8 != 0x58) {
              if (bVar8 == 0x43) {
                if ((local_214 & 0x830) == 0) {
                  local_214 = local_214 | 0x800;
                }
                goto LAB_004551ed;
              }
              if ((bVar8 != 0x45) && (bVar8 != 0x47)) {
                if (bVar8 == 0x53) {
                  if ((local_214 & 0x830) == 0) {
                    local_214 = local_214 | 0x800;
                  }
                  goto LAB_00455176;
                }
                goto LAB_00455541;
              }
              local_250 = 1;
              bVar8 = bVar8 + 0x20;
              goto LAB_004551c1;
            }
LAB_004553f3:
            local_24c = 7;
LAB_004553f6:
            local_224 = 0x10;
            if ((local_214 & 0x80) != 0) {
              local_22b = (char)local_24c + 'Q';
              local_22c = 0x30;
              local_230 = 2;
            }
            goto LAB_00455238;
          }
          if (bVar8 == 0x5a) {
            local_218 = param_3 + 2;
            psVar2 = *(short **)param_3;
            pwVar12 = (wchar_t *)PTR_s__null__004731a0;
            pwVar3 = (wchar_t *)PTR_s__null__004731a0;
            if ((psVar2 == (short *)0x0) ||
               (local_220 = *(wchar_t **)(psVar2 + 2), pwVar3 = (wchar_t *)PTR_s__null__004731a0,
               local_220 == (wchar_t *)0x0)) goto LAB_00455367;
            local_224 = (size_t)*psVar2;
            if ((local_214 & 0x800) == 0) {
              local_240 = 0;
            }
            else {
              local_224 = (int)local_224 / 2;
              local_240 = 1;
            }
          }
          else if (bVar8 == 99) {
LAB_004551ed:
            local_218 = param_3 + 2;
            if ((local_214 & 0x810) == 0) {
              local_210[0]._0_1_ = (char)*param_3;
              local_224 = 1;
            }
            else {
              local_224 = _wctomb((char *)local_210,*param_3);
              if ((int)local_224 < 0) {
                local_248 = 1;
              }
            }
            local_220 = local_210;
          }
          else if (bVar8 == 100) goto LAB_0045522d;
        }
        else {
LAB_004551c1:
          local_214 = local_214 | 0x40;
          pwVar9 = local_210;
          pwVar12 = local_210;
          if (local_21c < 0) {
            local_21c = 6;
          }
          else if (local_21c == 0) {
            if (bVar8 == 0x67) {
              local_21c = 1;
            }
          }
          else {
            if (0x200 < local_21c) {
              local_21c = 0x200;
            }
            if ((0xa3 < local_21c) &&
               (local_220 = local_210, local_244 = _malloc(local_21c + 0x15d), pwVar9 = local_244,
               pwVar12 = local_244, local_244 == (wchar_t *)0x0)) {
              local_21c = 0xa3;
              pwVar9 = local_210;
              pwVar12 = local_220;
            }
          }
          local_220 = pwVar12;
          local_264 = *(undefined4 *)local_218;
          local_260 = *(undefined4 *)(local_218 + 2);
          local_218 = local_218 + 4;
          (*(code *)PTR_FUN_004739c0)(&local_264,pwVar9,(int)(char)bVar8,local_21c,local_250);
          uVar4 = local_214 & 0x80;
          if ((uVar4 != 0) && (local_21c == 0)) {
            (*(code *)PTR_FUN_004739cc)(pwVar9);
          }
          if ((bVar8 == 0x67) && (uVar4 == 0)) {
            (*(code *)PTR_FUN_004739c4)(pwVar9);
          }
          pwVar12 = pwVar9;
          pwVar3 = local_220;
          if ((char)*pwVar9 == '-') {
            local_214 = local_214 | 0x100;
            pwVar12 = (wchar_t *)((int)pwVar9 + 1);
            pwVar3 = (wchar_t *)((int)pwVar9 + 1);
          }
LAB_00455367:
          local_220 = pwVar3;
          local_224 = _strlen((char *)pwVar12);
        }
LAB_00455541:
        uVar4 = local_214;
        if (local_248 == 0) {
          if ((local_214 & 0x40) != 0) {
            if ((local_214 & 0x100) == 0) {
              if ((local_214 & 1) == 0) {
                if ((local_214 & 2) == 0) goto LAB_00455579;
                local_22c = 0x20;
              }
              else {
                local_22c = 0x2b;
              }
            }
            else {
              local_22c = 0x2d;
            }
            local_230 = 1;
          }
LAB_00455579:
          iVar6 = (local_23c - local_230) - local_224;
          if ((local_214 & 0xc) == 0) {
            write_multi_char(0x20,iVar6);
          }
          write_string(local_230);
          if (((uVar4 & 8) != 0) && ((uVar4 & 4) == 0)) {
            write_multi_char(0x30,iVar6);
          }
          if ((local_240 == 0) || ((int)local_224 < 1)) {
            write_string(local_224);
          }
          else {
            local_258 = local_224;
            pwVar9 = local_220;
            do {
              local_258 = local_258 - 1;
              iVar5 = _wctomb((char *)((int)&local_11 + 1),*pwVar9);
              pwVar9 = pwVar9 + 1;
              if (iVar5 < 1) break;
              write_string(iVar5);
            } while (local_258 != 0);
          }
          if ((local_214 & 4) != 0) {
            write_multi_char(0x20,iVar6);
          }
        }
      }
      else {
        if (bVar8 == 0x69) {
LAB_0045522d:
          local_214 = local_214 | 0x40;
LAB_00455231:
          local_224 = 10;
LAB_00455238:
          if ((local_214 & 0x8000) == 0) {
            local_218 = param_3 + 2;
            if ((local_214 & 0x20) == 0) {
              uVar4 = *(uint *)param_3;
              if ((local_214 & 0x40) == 0) {
                uVar7 = 0;
                goto LAB_0045548b;
              }
            }
            else if ((local_214 & 0x40) == 0) {
              uVar4 = (uint)(ushort)*param_3;
            }
            else {
              uVar4 = (uint)*param_3;
            }
            uVar7 = (int)uVar4 >> 0x1f;
          }
          else {
            uVar4 = *(uint *)param_3;
            uVar7 = *(uint *)(param_3 + 2);
            local_218 = param_3 + 4;
          }
LAB_0045548b:
          if ((((local_214 & 0x40) != 0) && ((int)uVar7 < 1)) && ((int)uVar7 < 0)) {
            bVar10 = uVar4 != 0;
            uVar4 = -uVar4;
            uVar7 = -(uVar7 + bVar10);
            local_214 = local_214 | 0x100;
          }
          uVar11 = CONCAT44(uVar7,uVar4);
          if ((local_214 & 0x8000) == 0) {
            uVar7 = 0;
          }
          if (local_21c < 0) {
            local_21c = 1;
          }
          else {
            local_214 = local_214 & 0xfffffff7;
            if (0x200 < local_21c) {
              local_21c = 0x200;
            }
          }
          if (uVar4 == 0 && uVar7 == 0) {
            local_230 = 0;
          }
          pwVar9 = &local_11;
          while( true ) {
            uVar4 = (uint)uVar11;
            iVar6 = local_21c + -1;
            if ((local_21c < 1) && (uVar4 == 0 && uVar7 == 0)) break;
            local_21c = iVar6;
            uVar11 = __aulldvrm(uVar4,uVar7,local_224,(int)local_224 >> 0x1f);
            uVar7 = (uint)((ulonglong)uVar11 >> 0x20);
            iVar6 = extraout_ECX + 0x30;
            if (0x39 < iVar6) {
              iVar6 = iVar6 + local_24c;
            }
            *(char *)pwVar9 = (char)iVar6;
            pwVar9 = (wchar_t *)((int)pwVar9 + -1);
            local_258 = uVar4;
          }
          local_224 = (int)&local_11 + -(int)pwVar9;
          local_220 = (wchar_t *)((int)pwVar9 + 1);
          local_21c = iVar6;
          if (((local_214 & 0x200) != 0) && ((*(char *)local_220 != '0' || (local_224 == 0)))) {
            *(char *)pwVar9 = '0';
            local_224 = (int)&local_11 + -(int)pwVar9 + 1;
            local_220 = pwVar9;
          }
          goto LAB_00455541;
        }
        if (bVar8 != 0x6e) {
          if (bVar8 == 0x6f) {
            local_224 = 8;
            if ((local_214 & 0x80) != 0) {
              local_214 = local_214 | 0x200;
            }
            goto LAB_00455238;
          }
          if (bVar8 == 0x70) {
            local_21c = 8;
            goto LAB_004553f3;
          }
          if (bVar8 == 0x73) {
LAB_00455176:
            iVar6 = local_21c;
            if (local_21c == -1) {
              iVar6 = 0x7fffffff;
            }
            local_218 = param_3 + 2;
            local_220 = *(wchar_t **)param_3;
            if ((local_214 & 0x810) == 0) {
              pwVar9 = local_220;
              if (local_220 == (wchar_t *)0x0) {
                pwVar9 = (wchar_t *)PTR_s__null__004731a0;
                local_220 = (wchar_t *)PTR_s__null__004731a0;
              }
              for (; (iVar6 != 0 && (iVar6 = iVar6 + -1, (char)*pwVar9 != '\0'));
                  pwVar9 = (wchar_t *)((int)pwVar9 + 1)) {
              }
              local_224 = (int)pwVar9 - (int)local_220;
            }
            else {
              if (local_220 == (wchar_t *)0x0) {
                local_220 = (wchar_t *)PTR_DAT_004731a4;
              }
              local_240 = 1;
              for (pwVar9 = local_220; (iVar6 != 0 && (iVar6 = iVar6 + -1, *pwVar9 != L'\0'));
                  pwVar9 = pwVar9 + 1) {
              }
              local_224 = (int)pwVar9 - (int)local_220 >> 1;
            }
            goto LAB_00455541;
          }
          if (bVar8 != 0x75) {
            if (bVar8 != 0x78) goto LAB_00455541;
            local_24c = 0x27;
            goto LAB_004553f6;
          }
          goto LAB_00455231;
        }
        local_218 = param_3 + 2;
        if ((local_214 & 0x20) == 0) {
          **(int **)param_3 = local_228;
        }
        else {
          *(undefined2 *)*(int **)param_3 = (undefined2)local_228;
        }
        local_248 = 1;
      }
      if (local_244 != (wchar_t *)0x0) {
        _free(local_244);
        local_244 = (wchar_t *)0x0;
      }
    }
    bVar8 = *local_234;
    param_2 = local_234;
    param_3 = local_218;
  } while( true );
}

