/* Raw Ghidra reference; not compilable reconstruction. Address: 00457A7C */

/* WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog */
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3 */
/* WARNING: Function: __chkstk replaced with injection: alloca_probe */
/* WARNING: Removing unreachable block (ram,0x00458867) */

int __cdecl FUN_00457a7c(FILE *param_1,byte *param_2,undefined4 *param_3)

{
  uint uVar1;
  byte bVar2;
  undefined1 *puVar3;
  FILE *_File;
  uint uVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  uint extraout_ECX;
  FILE *extraout_ECX_00;
  FILE *pFVar9;
  FILE *extraout_ECX_01;
  FILE *extraout_ECX_02;
  FILE *extraout_ECX_03;
  undefined4 extraout_ECX_04;
  uint extraout_ECX_05;
  byte bVar10;
  byte bVar11;
  wchar_t *pwVar12;
  char *pcVar13;
  char *pcVar14;
  byte *pbVar15;
  byte *pbVar16;
  byte *pbVar17;
  wchar_t *pwVar18;
  bool bVar19;
  undefined4 *local_1ec;
  uint local_1e0;
  wchar_t local_1dc [2];
  undefined4 *local_1d8;
  int local_1d4;
  byte local_1d0;
  undefined1 local_1cf;
  undefined1 *local_1cc;
  uint local_1c8;
  int local_1c4;
  FILE *local_1c0;
  wchar_t *local_1bc;
  byte local_1b5;
  undefined8 local_1b4;
  int local_1ac;
  byte local_1a5;
  int local_1a4;
  byte *local_1a0;
  char local_19b;
  char local_19a;
  char local_199;
  FILE *local_198;
  uint local_194;
  char local_18f;
  char local_18e;
  char local_18d;
  int local_18c;
  int local_188;
  char local_181;
  char local_180;
  char local_17f [351];
  uint local_20;
  undefined1 *local_1c;
  undefined4 uStack_c;
  undefined *local_8;
  
  local_8 = &DAT_0046ab48;
  uStack_c = 0x457a8b;
  local_20 = DAT_00473660 ^ (uint)&stack0xfffffffc;
  local_198 = param_1;
  local_1a0 = param_2;
  local_1d8 = param_3;
  local_1cc = (undefined1 *)0x0;
  local_1bc = (wchar_t *)0x0;
  local_194 = 0;
  local_199 = '\0';
  local_188 = 0;
  local_1c4 = 0;
  pbVar15 = local_1a0;
LAB_00457ae4:
  while (local_1a0 = pbVar15, *local_1a0 != 0) {
    uVar4 = (uint)*local_1a0;
    iVar5 = _isspace(uVar4);
    pbVar15 = local_1a0;
    if (iVar5 == 0) {
      if (*local_1a0 != 0x25) {
        local_188 = local_188 + 1;
        uVar4 = __inc(uVar4,local_198);
        pbVar17 = pbVar15 + 1;
        local_1a0 = pbVar17;
        local_194 = uVar4;
        if (*pbVar15 != uVar4) goto LAB_0045881f;
        if ((PTR_DAT_004739d8[(uVar4 & 0xff) * 2 + 1] & 0x80) != 0) {
          local_188 = local_188 + 1;
          uVar6 = __inc(PTR_DAT_004739d8,local_198);
          local_1a0 = pbVar15 + 2;
          if (*pbVar17 != uVar6) {
            if (uVar6 != 0xffffffff) {
              FID_conflict__ungetc(uVar6,local_198);
            }
            goto LAB_0045881f;
          }
          local_188 = local_188 + -1;
        }
        goto LAB_0045883c;
      }
      iVar5 = 0;
      local_1ac = 0;
      local_1a5 = 0;
      local_1a4 = 0;
      local_1c0 = (FILE *)0x0;
      local_18c = 0;
      local_1b5 = 0;
      local_19b = '\0';
      local_18e = '\0';
      local_181 = '\0';
      local_19a = '\0';
      local_18d = '\0';
      local_18f = '\x01';
      local_1d4 = 0;
      do {
        pbVar16 = pbVar15 + 1;
        uVar6 = (uint)*pbVar16;
        uVar4 = uVar6;
        iVar7 = _isdigit(uVar6);
        pbVar17 = pbVar16;
        if (iVar7 == 0) {
          if (uVar6 < 0x4f) {
            if (uVar6 != 0x4e) {
              if (uVar6 == 0x2a) {
                local_18e = local_18e + '\x01';
              }
              else if (uVar6 != 0x46) {
                if (uVar6 == 0x49) {
                  bVar11 = pbVar15[2];
                  uVar4 = CONCAT31((int3)(uVar4 >> 8),bVar11);
                  if ((bVar11 == 0x36) && (pbVar15[3] == 0x34)) {
                    local_1d4 = local_1d4 + 1;
                    local_1b4 = 0;
                    pbVar17 = pbVar15 + 3;
                  }
                  else if (((bVar11 != 0x33) || (pbVar17 = pbVar15 + 3, *pbVar17 != 0x32)) &&
                          ((((pbVar17 = pbVar16, bVar11 != 100 && (bVar11 != 0x69)) &&
                            (bVar11 != 0x6f)) && ((bVar11 != 0x78 && (bVar11 != 0x58))))))
                  goto LAB_00457c78;
                }
                else if (uVar6 == 0x4c) {
                  local_18f = local_18f + '\x01';
                }
                else {
LAB_00457c78:
                  local_181 = local_181 + '\x01';
                  pbVar17 = pbVar16;
                }
              }
            }
          }
          else if (uVar6 == 0x68) {
            local_18f = local_18f + -1;
            local_18d = local_18d + -1;
          }
          else {
            if (uVar6 == 0x6c) {
              local_18f = local_18f + '\x01';
            }
            else if (uVar6 != 0x77) goto LAB_00457c78;
            local_18d = local_18d + '\x01';
          }
        }
        else {
          local_1c0 = (FILE *)((int)&local_1c0->_ptr + 1);
          iVar5 = (uVar6 - 0x30) + iVar5 * 10;
        }
        pbVar15 = pbVar17;
      } while (local_181 == '\0');
      if (local_18e == '\0') {
        local_1ec = local_1d8;
        local_1bc = (wchar_t *)*local_1d8;
        local_1d8 = local_1d8 + 1;
      }
      pwVar12 = local_1bc;
      local_181 = '\0';
      if ((local_18d == '\0') && ((*pbVar17 == 0x53 || (local_18d = -1, *pbVar17 == 0x43)))) {
        local_18d = '\x01';
      }
      uVar6 = *pbVar17 | 0x20;
      local_1c8 = uVar6;
      local_1a0 = pbVar17;
      uVar8 = local_194;
      local_18c = iVar5;
      if (uVar6 != 0x6e) {
        if ((uVar6 == 99) || (uVar6 == 0x7b)) {
          local_188 = local_188 + 1;
          uVar8 = __inc(uVar4,local_198);
        }
        else {
          do {
            local_188 = local_188 + 1;
            uVar8 = __inc(uVar4,local_198);
            uVar4 = uVar8;
            iVar5 = _isspace(uVar8);
            uVar6 = local_1c8;
          } while (iVar5 != 0);
        }
      }
      local_194 = uVar8;
      _File = local_198;
      pFVar9 = local_1c0;
      uVar4 = local_194;
      if ((local_1c0 == (FILE *)0x0) || (local_18c != 0)) {
        if ((int)uVar6 < 0x70) {
          if (uVar6 == 0x6f) {
LAB_00458488:
            if (local_194 == 0x2d) {
              local_19b = '\x01';
            }
            else if (local_194 != 0x2b) goto LAB_004584cf;
            local_18c = local_18c + -1;
            if ((local_18c == 0) && (local_1c0 != (FILE *)0x0)) {
              local_181 = '\x01';
            }
            else {
              local_188 = local_188 + 1;
              local_194 = __inc(local_1c0,local_198);
            }
            goto LAB_004584cf;
          }
          if (uVar6 == 99) {
            if (local_1c0 == (FILE *)0x0) {
              local_1c0 = (FILE *)0x1;
              local_18c = local_18c + 1;
            }
LAB_00458022:
            if ('\0' < local_18d) {
              local_19a = '\x01';
            }
            goto LAB_00458032;
          }
          if (uVar6 == 100) goto LAB_00458488;
          if ((int)uVar6 < 0x65) {
LAB_00458183:
            if (*pbVar17 != local_194) goto LAB_0045881f;
            local_199 = local_199 + -1;
            local_1a0 = pbVar17;
            if (local_18e == '\0') {
              local_1d8 = local_1ec;
            }
            goto LAB_00457ffc;
          }
          if (0x67 < (int)uVar6) {
            if (uVar6 == 0x69) {
              uVar6 = 100;
              goto LAB_00457dd4;
            }
            if (uVar6 != 0x6e) goto LAB_00458183;
            iVar5 = local_188;
            local_1a0 = pbVar17;
            if (local_18e != '\0') goto LAB_00457ffc;
            goto LAB_0045877c;
          }
          pcVar13 = &local_180;
          if (local_194 == 0x2d) {
            local_180 = '-';
            pcVar13 = local_17f;
LAB_00457e13:
            local_18c = local_18c + -1;
            local_188 = local_188 + 1;
            local_194 = __inc(local_1c0,local_198);
          }
          else if (local_194 == 0x2b) goto LAB_00457e13;
          if ((local_1c0 == (FILE *)0x0) || (0x15d < local_18c)) {
            local_18c = 0x15d;
          }
          while( true ) {
            uVar4 = local_194;
            uVar6 = local_194;
            iVar5 = _isdigit(local_194);
            if ((iVar5 == 0) ||
               (iVar5 = local_18c + -1, bVar19 = local_18c == 0, local_18c = iVar5, bVar19)) break;
            local_1a4 = local_1a4 + 1;
            *pcVar13 = (char)uVar4;
            pcVar13 = pcVar13 + 1;
            local_188 = local_188 + 1;
            local_194 = __inc(uVar6,_File);
          }
          if ((DAT_00473af4 == (char)uVar4) &&
             (iVar5 = local_18c + -1, bVar19 = local_18c != 0, local_18c = iVar5, bVar19)) {
            local_188 = local_188 + 1;
            uVar4 = __inc(uVar6,_File);
            *pcVar13 = DAT_00473af4;
            while( true ) {
              pcVar13 = pcVar13 + 1;
              uVar6 = uVar4;
              local_194 = uVar4;
              iVar5 = _isdigit(uVar4);
              if ((iVar5 == 0) ||
                 (iVar5 = local_18c + -1, bVar19 = local_18c == 0, local_18c = iVar5, bVar19))
              break;
              local_1a4 = local_1a4 + 1;
              *pcVar13 = (char)uVar4;
              local_188 = local_188 + 1;
              uVar4 = __inc(uVar6,_File);
            }
          }
          pcVar14 = pcVar13;
          if ((local_1a4 != 0) &&
             (((uVar4 == 0x65 || (uVar4 == 0x45)) &&
              (iVar5 = local_18c + -1, bVar19 = local_18c != 0, local_18c = iVar5, bVar19)))) {
            *pcVar13 = 'e';
            pcVar14 = pcVar13 + 1;
            local_188 = local_188 + 1;
            local_194 = __inc(uVar6,_File);
            if (local_194 == 0x2d) {
              *pcVar14 = '-';
              pcVar14 = pcVar13 + 2;
LAB_00457f53:
              bVar19 = local_18c != 0;
              uVar6 = extraout_ECX;
              local_18c = local_18c + -1;
              if (bVar19) goto LAB_00457f84;
              local_18c = 0;
            }
            else if (local_194 == 0x2b) goto LAB_00457f53;
            while ((uVar4 = local_194, uVar6 = local_194, iVar5 = _isdigit(local_194), iVar5 != 0 &&
                   (iVar5 = local_18c + -1, bVar19 = local_18c != 0, local_18c = iVar5, bVar19))) {
              local_1a4 = local_1a4 + 1;
              *pcVar14 = (char)uVar4;
              pcVar14 = pcVar14 + 1;
LAB_00457f84:
              local_188 = local_188 + 1;
              local_194 = __inc(uVar6,_File);
            }
          }
          local_188 = local_188 + -1;
          if (uVar4 != 0xffffffff) {
            FID_conflict__ungetc(uVar4,_File);
          }
          if (local_1a4 != 0) {
            if (local_18e == '\0') {
              local_1c4 = local_1c4 + 1;
              *pcVar14 = '\0';
              (*(code *)PTR_FUN_004739c8)(local_18f + -1,local_1bc,&local_180);
            }
            goto LAB_00457ffc;
          }
        }
        else {
          if (uVar6 == 0x70) {
            local_18f = '\x01';
            goto LAB_00458488;
          }
          if (uVar6 == 0x73) goto LAB_00458022;
          if (uVar6 == 0x75) goto LAB_00458488;
          if (uVar6 != 0x78) {
            if (uVar6 == 0x7b) {
              if ('\0' < local_18d) {
                local_19a = '\x01';
              }
              pbVar17 = local_1a0 + 1;
              pbVar15 = pbVar17;
              if (*pbVar17 == 0x5e) {
                pbVar15 = local_1a0 + 2;
                local_1b5 = 0xff;
              }
              if (local_1cc == (undefined1 *)0x0) {
                local_1c = &stack0xfffffe08;
                local_1cc = &stack0xfffffe08;
                local_8 = (undefined *)0xffffffff;
              }
              puVar3 = local_1cc;
              local_1a0 = pbVar17;
              _memset(local_1cc,0,0x20);
              pFVar9 = extraout_ECX_02;
              bVar11 = local_1a5;
              if ((local_1c8 == 0x7b) && (*pbVar15 == 0x5d)) {
                puVar3[0xb] = 0x20;
                pbVar15 = pbVar15 + 1;
                bVar11 = 0x5d;
              }
LAB_004582ee:
              do {
                bVar10 = *pbVar15;
                if (bVar10 == 0x5d) goto code_r0x004582fc;
                if ((bVar10 == 0x2d) && (bVar11 != 0)) {
                  bVar2 = pbVar15[1];
                  pFVar9 = (FILE *)CONCAT31((int3)((uint)pFVar9 >> 8),bVar2);
                  if (bVar2 != 0x5d) {
                    bVar10 = bVar2;
                    if (bVar11 < bVar2) {
                      bVar10 = bVar11;
                      bVar11 = bVar2;
                    }
                    if (bVar10 <= bVar11) {
                      uVar4 = (uint)bVar10;
                      local_1e0 = (uint)(byte)((bVar11 - bVar10) + 1);
                      do {
                        pFVar9 = (FILE *)(uVar4 & 7);
                        puVar3[uVar4 >> 3] = puVar3[uVar4 >> 3] | '\x01' << (sbyte)pFVar9;
                        uVar4 = uVar4 + 1;
                        local_1e0 = local_1e0 - 1;
                      } while (local_1e0 != 0);
                    }
                    pbVar15 = pbVar15 + 2;
                    bVar11 = 0;
                    goto LAB_004582ee;
                  }
                }
                local_1a5 = bVar10;
                pFVar9 = (FILE *)(bVar10 & 7);
                puVar3[bVar10 >> 3] = puVar3[bVar10 >> 3] | '\x01' << (sbyte)pFVar9;
                pbVar15 = pbVar15 + 1;
                bVar11 = local_1a5;
              } while( true );
            }
            goto LAB_00458183;
          }
LAB_00457dd4:
          if (local_194 == 0x2d) {
            local_19b = '\x01';
LAB_00458321:
            local_18c = local_18c + -1;
            if ((local_18c == 0) && (local_1c0 != (FILE *)0x0)) {
              local_181 = '\x01';
            }
            else {
              local_188 = local_188 + 1;
              local_194 = __inc(local_1c0,local_198);
              pFVar9 = extraout_ECX_03;
            }
          }
          else if (local_194 == 0x2b) goto LAB_00458321;
          if (local_194 == 0x30) {
            local_188 = local_188 + 1;
            local_194 = __inc(pFVar9,local_198);
            if (((char)local_194 == 'x') || ((char)local_194 == 'X')) {
              local_188 = local_188 + 1;
              local_194 = __inc(extraout_ECX_04,local_198);
              if ((local_1c0 != (FILE *)0x0) && (local_18c = local_18c + -2, local_18c < 1)) {
                local_181 = local_181 + '\x01';
              }
              uVar6 = 0x78;
            }
            else {
              local_1a4 = 1;
              if (uVar6 == 0x78) {
                local_188 = local_188 + -1;
                if (local_194 != 0xffffffff) {
                  FID_conflict__ungetc(local_194,local_198);
                }
                local_194 = 0x30;
              }
              else {
                if ((local_1c0 != (FILE *)0x0) && (local_18c = local_18c + -1, local_18c == 0)) {
                  local_181 = local_181 + '\x01';
                }
                uVar6 = 0x6f;
              }
            }
          }
LAB_004584cf:
          uVar4 = local_194;
          if (local_1d4 == 0) {
            while (local_181 == '\0') {
              uVar8 = uVar4;
              if ((uVar6 == 0x78) || (uVar6 == 0x70)) {
                iVar5 = _isxdigit(uVar4);
                if (iVar5 != 0) {
                  local_1ac = local_1ac << 4;
                  uVar8 = uVar4;
                  iVar5 = _isdigit(uVar4);
                  if (iVar5 == 0) {
                    uVar4 = (uVar4 & 0xffffffdf) - 7;
                  }
                  goto LAB_004586b5;
                }
LAB_004586af:
                local_181 = local_181 + '\x01';
              }
              else {
                iVar5 = _isdigit(uVar4);
                if (iVar5 == 0) goto LAB_004586af;
                if (uVar6 == 0x6f) {
                  if (0x37 < (int)uVar4) goto LAB_004586af;
                  local_1ac = local_1ac << 3;
                }
                else {
                  local_1ac = local_1ac * 10;
                }
              }
LAB_004586b5:
              if (local_181 == '\0') {
                local_1a4 = local_1a4 + 1;
                local_1ac = local_1ac + -0x30 + uVar4;
                if ((local_1c0 == (FILE *)0x0) || (local_18c = local_18c + -1, local_18c != 0)) {
                  local_188 = local_188 + 1;
                  uVar4 = __inc(uVar8,local_198);
                }
                else {
                  local_181 = '\x01';
                }
              }
              else {
                local_188 = local_188 + -1;
                if (uVar4 != 0xffffffff) {
                  FID_conflict__ungetc(uVar4,local_198);
                }
              }
            }
            local_194 = uVar4;
            if (local_19b != '\0') {
              local_1ac = -local_1ac;
            }
          }
          else {
            while (local_181 == '\0') {
              uVar8 = uVar4;
              if ((uVar6 == 0x78) || (uVar6 == 0x70)) {
                iVar5 = _isxdigit(uVar4);
                if (iVar5 != 0) {
                  local_1b4 = CONCAT44(local_1b4._4_4_ << 4 | (uint)local_1b4 >> 0x1c,
                                       (uint)local_1b4 << 4);
                  uVar8 = uVar4;
                  iVar5 = _isdigit(uVar4);
                  if (iVar5 == 0) {
                    uVar4 = (uVar4 & 0xffffffdf) - 7;
                  }
                  goto LAB_00458597;
                }
LAB_00458591:
                local_181 = local_181 + '\x01';
              }
              else {
                iVar5 = _isdigit(uVar4);
                if (iVar5 == 0) goto LAB_00458591;
                if (uVar6 == 0x6f) {
                  if (0x37 < (int)uVar4) goto LAB_00458591;
                  uVar8 = local_1b4._4_4_ << 3 | (uint)local_1b4 >> 0x1d;
                  local_1b4 = CONCAT44(uVar8,(uint)local_1b4 << 3);
                }
                else {
                  local_1b4 = __allmul((uint)local_1b4,local_1b4._4_4_,10,0);
                  uVar8 = extraout_ECX_05;
                }
              }
LAB_00458597:
              if (local_181 == '\0') {
                local_1a4 = local_1a4 + 1;
                uVar1 = uVar4 - 0x30;
                local_1b4 = CONCAT44(local_1b4._4_4_ + ((int)uVar1 >> 0x1f) +
                                     (uint)CARRY4((uint)local_1b4,uVar1),(uint)local_1b4 + uVar1);
                if ((local_1c0 == (FILE *)0x0) || (local_18c = local_18c + -1, local_18c != 0)) {
                  local_188 = local_188 + 1;
                  uVar4 = __inc(uVar8,local_198);
                }
                else {
                  local_181 = '\x01';
                }
              }
              else {
                local_188 = local_188 + -1;
                if (uVar4 != 0xffffffff) {
                  FID_conflict__ungetc(uVar4,local_198);
                }
              }
            }
            local_194 = uVar4;
            if (local_19b != '\0') {
              local_1b4._4_4_ = (int)((ulonglong)local_1b4 >> 0x20);
              local_1b4 = CONCAT44(-(local_1b4._4_4_ + (uint)((uint)local_1b4 != 0)),
                                   -(uint)local_1b4);
            }
          }
          if (uVar6 == 0x46) {
            local_1a4 = 0;
          }
          if (local_1a4 != 0) {
            if (local_18e == '\0') {
              local_1c4 = local_1c4 + 1;
              iVar5 = local_1ac;
              pwVar12 = local_1bc;
LAB_0045877c:
              if (local_1d4 == 0) {
                if (local_18f == '\0') {
                  *pwVar12 = (wchar_t)iVar5;
                }
                else {
                  *(int *)pwVar12 = iVar5;
                }
              }
              else {
                *(uint *)pwVar12 = (uint)local_1b4;
                *(int *)(pwVar12 + 2) = local_1b4._4_4_;
              }
            }
            goto LAB_00457ffc;
          }
        }
      }
      else {
LAB_0045881f:
        if (uVar4 != 0xffffffff) {
          FID_conflict__ungetc(local_194,local_198);
        }
      }
      break;
    }
    local_188 = local_188 + -1;
    do {
      local_188 = local_188 + 1;
      uVar6 = __inc(uVar4,local_198);
      uVar4 = uVar6;
      iVar5 = _isspace(uVar6);
    } while (iVar5 != 0);
    pbVar15 = local_1a0;
    if (uVar6 != 0xffffffff) {
      FID_conflict__ungetc(uVar6,local_198);
      pbVar15 = local_1a0;
    }
    do {
      pbVar15 = pbVar15 + 1;
      iVar5 = _isspace((uint)*pbVar15);
    } while (iVar5 != 0);
  }
  goto LAB_0045885e;
code_r0x004582fc:
  pwVar12 = local_1bc;
  uVar6 = local_1c8;
  if (local_1c8 == 0x7b) {
    local_1a0 = pbVar15;
  }
LAB_00458032:
  local_188 = local_188 + -1;
  pwVar18 = pwVar12;
  if (local_194 != 0xffffffff) {
    pFVar9 = local_198;
    FID_conflict__ungetc(local_194,local_198);
  }
  while( true ) {
    if ((local_1c0 != (FILE *)0x0) &&
       (iVar5 = local_18c + -1, bVar19 = local_18c == 0, local_18c = iVar5, bVar19))
    goto LAB_00458433;
    local_188 = local_188 + 1;
    local_194 = __inc(pFVar9,local_198);
    if ((local_194 == 0xffffffff) ||
       ((bVar11 = (byte)local_194, pFVar9 = extraout_ECX_00, uVar6 != 99 &&
        (((uVar6 != 0x73 ||
          (((8 < (int)local_194 && ((int)local_194 < 0xe)) || (local_194 == 0x20)))) &&
         ((uVar6 != 0x7b ||
          (pFVar9 = (FILE *)(int)(char)(local_1cc[(int)local_194 >> 3] ^ local_1b5),
          uVar6 = local_1c8, ((uint)pFVar9 & 1 << (bVar11 & 7)) == 0)))))))) break;
    if (local_18e == '\0') {
      if (local_19a == '\0') {
        *(byte *)pwVar12 = bVar11;
        pwVar12 = (wchar_t *)((int)pwVar12 + 1);
        local_1bc = pwVar12;
      }
      else {
        local_1d0 = bVar11;
        if ((PTR_DAT_004739d8[(local_194 & 0xff) * 2 + 1] & 0x80) != 0) {
          local_188 = local_188 + 1;
          uVar4 = __inc(PTR_DAT_004739d8,local_198);
          local_1cf = (undefined1)uVar4;
        }
        _mbtowc(local_1dc,(char *)&local_1d0,DAT_00473af0);
        *pwVar12 = local_1dc[0];
        pwVar12 = pwVar12 + 1;
        pFVar9 = extraout_ECX_01;
        local_1bc = pwVar12;
      }
    }
    else {
      pwVar18 = (wchar_t *)((int)pwVar18 + 1);
    }
  }
  local_188 = local_188 + -1;
  if (local_194 != 0xffffffff) {
    FID_conflict__ungetc(local_194,local_198);
  }
LAB_00458433:
  if (pwVar18 == pwVar12) {
LAB_0045885e:
    if ((local_194 == 0xffffffff) && ((local_1c4 == 0 && (local_199 == '\0')))) {
      local_1c4 = -1;
    }
    return local_1c4;
  }
  if ((local_18e == '\0') && (local_1c4 = local_1c4 + 1, local_1c8 != 99)) {
    if (local_19a == '\0') {
      *(byte *)local_1bc = 0;
    }
    else {
      *local_1bc = L'\0';
    }
  }
LAB_00457ffc:
  local_199 = local_199 + '\x01';
  local_1a0 = local_1a0 + 1;
LAB_0045883c:
  pbVar15 = local_1a0;
  if ((local_194 == 0xffffffff) && ((*local_1a0 != 0x25 || (local_1a0[1] != 0x6e))))
  goto LAB_0045885e;
  goto LAB_00457ae4;
}

