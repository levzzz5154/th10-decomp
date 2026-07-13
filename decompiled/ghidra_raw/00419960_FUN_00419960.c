/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00419960
 * Tracking name: FUN_00419960
 * Ghidra name: FUN_00419960
 * Tracked span: 1504 bytes
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00419960(undefined4 param_1,size_t param_2,int param_3)

{
  char cVar1;
  double dVar2;
  uint uVar3;
  byte *_Memory;
  uint *_Memory_00;
  uint *_Memory_01;
  uint *_Str;
  uint *puVar4;
  undefined4 *puVar5;
  float *pfVar6;
  long lVar7;
  char *pcVar8;
  float fVar9;
  uint *puVar10;
  float *pfVar11;
  int iVar12;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  float *pfVar13;
  bool bVar14;
  double dVar15;
  int local_24;
  int local_20;
  
  local_24 = -1;
  local_20 = 0;
  _Memory = FUN_0044b360(&param_2,1);
  if (_Memory == (byte *)0x0) {
    return 0xffffffff;
  }
  _Memory_00 = _malloc(0x1000);
  _Memory_01 = _malloc(0x1000);
  _Str = _malloc(0x1000);
  if (0 < (int)param_2) {
    do {
      FUN_00419f40(_Memory_00,&param_2,0x1000);
      puVar4 = _Memory_01;
      do {
        cVar1 = *(char *)(((int)_Memory_00 - (int)_Memory_01) + (int)puVar4);
        *(char *)puVar4 = cVar1;
        puVar4 = (uint *)((int)puVar4 + 1);
      } while (cVar1 != '\0');
      puVar4 = FUN_00452730(_Memory_01,':');
      if (puVar4 != (uint *)0x0) {
        pcVar8 = (char *)((int)puVar4 + 1);
        iVar12 = (int)_Str - (int)pcVar8;
        do {
          cVar1 = *pcVar8;
          pcVar8[iVar12] = cVar1;
          pcVar8 = pcVar8 + 1;
        } while (cVar1 != '\0');
        *(undefined1 *)puVar4 = 0;
        FUN_0041a0a0();
      }
      FUN_0041a0a0();
      puVar4 = _Memory_00;
      do {
        uVar3 = *puVar4;
        *(char *)(((int)_Memory_01 - (int)_Memory_00) + (int)puVar4) = (char)uVar3;
        puVar4 = (uint *)((int)puVar4 + 1);
      } while ((char)uVar3 != '\0');
      puVar4 = FUN_00452730(_Memory_01,':');
      if (puVar4 != (uint *)0x0) {
        pcVar8 = (char *)((int)puVar4 + 1);
        iVar12 = (int)_Str - (int)pcVar8;
        do {
          cVar1 = *pcVar8;
          pcVar8[iVar12] = cVar1;
          pcVar8 = pcVar8 + 1;
        } while (cVar1 != '\0');
        *(undefined1 *)puVar4 = 0;
        FUN_0041a0a0();
      }
      FUN_0041a0a0();
      iVar12 = 8;
      bVar14 = true;
      puVar4 = _Memory_01;
      pcVar8 = "Version";
      do {
        if (iVar12 == 0) break;
        iVar12 = iVar12 + -1;
        bVar14 = (char)*puVar4 == *pcVar8;
        puVar4 = (uint *)((int)puVar4 + 1);
        pcVar8 = pcVar8 + 1;
      } while (bVar14);
      if (bVar14) {
        iVar12 = 4;
        bVar14 = true;
        puVar4 = _Str;
        pcVar8 = "0.0";
        do {
          if (iVar12 == 0) break;
          iVar12 = iVar12 + -1;
          bVar14 = (char)*puVar4 == *pcVar8;
          puVar4 = (uint *)((int)puVar4 + 1);
          pcVar8 = pcVar8 + 1;
        } while (bVar14);
        if (!bVar14) {
          FUN_00419040();
          break;
        }
      }
      else {
        iVar12 = 6;
        bVar14 = true;
        puVar4 = _Memory_01;
        pcVar8 = "Stage";
        do {
          if (iVar12 == 0) break;
          iVar12 = iVar12 + -1;
          bVar14 = (char)*puVar4 == *pcVar8;
          puVar4 = (uint *)((int)puVar4 + 1);
          pcVar8 = pcVar8 + 1;
        } while (bVar14);
        if (bVar14) {
          local_24 = _atol((char *)_Str);
          local_20 = 0;
          if ((local_24 < 1) || (7 < local_24)) {
            local_24 = -1;
          }
        }
        else {
          iVar12 = 9;
          bVar14 = true;
          puVar4 = _Memory_01;
          pcVar8 = "StageEnd";
          do {
            if (iVar12 == 0) break;
            iVar12 = iVar12 + -1;
            bVar14 = (char)*puVar4 == *pcVar8;
            puVar4 = (uint *)((int)puVar4 + 1);
            pcVar8 = pcVar8 + 1;
          } while (bVar14);
          if (bVar14) {
            local_24 = -1;
          }
          else {
            iVar12 = 5;
            bVar14 = true;
            puVar4 = _Memory_01;
            pcVar8 = "Tips";
            do {
              if (iVar12 == 0) break;
              iVar12 = iVar12 + -1;
              bVar14 = (char)*puVar4 == *pcVar8;
              puVar4 = (uint *)((int)puVar4 + 1);
              pcVar8 = pcVar8 + 1;
            } while (bVar14);
            if ((bVar14) && (0 < local_24)) {
              if (local_20 < 0xff) {
                puVar5 = operator_new(0x88);
                if (puVar5 == (undefined4 *)0x0) {
                  pfVar6 = (float *)0x0;
                }
                else {
                  pfVar6 = (float *)FUN_00418d00(extraout_ECX,puVar5);
                }
                local_20 = local_20 + 1;
                pfVar6[6] = 0.0;
joined_r0x00419bbf:
                do {
                  if ((int)param_2 < 1) break;
                  FUN_00419f40(_Memory_00,&param_2,0x1000);
                  FUN_0041a050();
                  iVar12 = 4;
                  bVar14 = true;
                  puVar4 = _Memory_01;
                  pcVar8 = "Pos";
                  do {
                    if (iVar12 == 0) break;
                    iVar12 = iVar12 + -1;
                    bVar14 = (char)*puVar4 == *pcVar8;
                    puVar4 = (uint *)((int)puVar4 + 1);
                    pcVar8 = pcVar8 + 1;
                  } while (bVar14);
                  if (bVar14) {
                    puVar4 = FUN_00452730(_Str,',');
                    if (puVar4 != (uint *)0x0) {
                      *(undefined1 *)puVar4 = 0;
                      FUN_0041a0a0();
                      FUN_0041a0a0();
                      lVar7 = _atol((char *)_Str);
                      *pfVar6 = (float)lVar7;
                      lVar7 = _atol((char *)((int)puVar4 + 1));
                      pfVar6[1] = (float)lVar7;
                    }
                    goto joined_r0x00419bbf;
                  }
                  iVar12 = 5;
                  bVar14 = true;
                  puVar4 = _Memory_01;
                  pcVar8 = "Text";
                  do {
                    if (iVar12 == 0) break;
                    iVar12 = iVar12 + -1;
                    bVar14 = (char)*puVar4 == *pcVar8;
                    puVar4 = (uint *)((int)puVar4 + 1);
                    pcVar8 = pcVar8 + 1;
                  } while (bVar14);
                  if (bVar14) {
                    puVar4 = FUN_00452730(_Str,'\"');
                    if (puVar4 != (uint *)0x0) {
                      pcVar8 = _strrchr((char *)((int)puVar4 + 1),0x22);
                      if (pcVar8 == (char *)0x0) break;
                      *pcVar8 = '\0';
                      _strncpy((char *)(pfVar6 + 7),(char *)((int)puVar4 + 1),0x41);
                    }
                    goto joined_r0x00419bbf;
                  }
                  iVar12 = 6;
                  bVar14 = true;
                  puVar4 = _Memory_01;
                  pcVar8 = "Count";
                  do {
                    if (iVar12 == 0) break;
                    iVar12 = iVar12 + -1;
                    bVar14 = (char)*puVar4 == *pcVar8;
                    puVar4 = (uint *)((int)puVar4 + 1);
                    pcVar8 = pcVar8 + 1;
                  } while (bVar14);
                  if (bVar14) {
                    fVar9 = (float)_atol((char *)_Str);
                    pfVar6[0x18] = fVar9;
                    goto joined_r0x00419bbf;
                  }
                  iVar12 = 5;
                  bVar14 = true;
                  puVar4 = _Memory_01;
                  pcVar8 = "Time";
                  do {
                    if (iVar12 == 0) break;
                    iVar12 = iVar12 + -1;
                    bVar14 = (char)*puVar4 == *pcVar8;
                    puVar4 = (uint *)((int)puVar4 + 1);
                    pcVar8 = pcVar8 + 1;
                  } while (bVar14);
                  if (bVar14) {
                    fVar9 = (float)_atol((char *)_Str);
                    pfVar6[0x1b] = fVar9;
                    goto joined_r0x00419bbf;
                  }
                  iVar12 = 5;
                  bVar14 = true;
                  puVar4 = _Memory_01;
                  pcVar8 = "Base";
                  do {
                    if (iVar12 == 0) break;
                    iVar12 = iVar12 + -1;
                    bVar14 = (char)*puVar4 == *pcVar8;
                    puVar4 = (uint *)((int)puVar4 + 1);
                    pcVar8 = pcVar8 + 1;
                  } while (bVar14);
                  if (bVar14) {
                    fVar9 = (float)FUN_004198c0(iVar12,(byte *)_Str,0x4744b0,0x3d);
                    pfVar6[0x1a] = fVar9;
                    goto joined_r0x00419bbf;
                  }
                  iVar12 = 6;
                  bVar14 = true;
                  puVar4 = _Memory_01;
                  pcVar8 = "Align";
                  do {
                    if (iVar12 == 0) break;
                    iVar12 = iVar12 + -1;
                    bVar14 = (char)*puVar4 == *pcVar8;
                    puVar4 = (uint *)((int)puVar4 + 1);
                    pcVar8 = pcVar8 + 1;
                  } while (bVar14);
                  if (bVar14) {
                    fVar9 = (float)FUN_004198c0(iVar12,(byte *)_Str,0x474494,3);
                    pfVar6[0x19] = fVar9;
                    goto joined_r0x00419bbf;
                  }
                  iVar12 = 7;
                  bVar14 = true;
                  puVar4 = _Memory_01;
                  pcVar8 = "Remain";
                  do {
                    if (iVar12 == 0) break;
                    iVar12 = iVar12 + -1;
                    bVar14 = (char)*puVar4 == *pcVar8;
                    puVar4 = (uint *)((int)puVar4 + 1);
                    pcVar8 = pcVar8 + 1;
                  } while (bVar14);
                  if (bVar14) {
                    fVar9 = (float)_atol((char *)_Str);
                    pfVar6[0x1c] = fVar9;
                    goto joined_r0x00419bbf;
                  }
                  iVar12 = 6;
                  bVar14 = true;
                  puVar4 = _Memory_01;
                  pcVar8 = "Scale";
                  do {
                    if (iVar12 == 0) break;
                    iVar12 = iVar12 + -1;
                    bVar14 = (char)*puVar4 == *pcVar8;
                    puVar4 = (uint *)((int)puVar4 + 1);
                    pcVar8 = pcVar8 + 1;
                  } while (bVar14);
                  if (bVar14) {
                    dVar15 = _atof((char *)_Str);
                    dVar2 = (double)_DAT_00470c40;
                    pfVar6[0x1f] = (float)dVar15;
                    if (dVar15 <= dVar2) {
                      if (dVar15 < (double)_DAT_00470c60) {
                        pfVar6[0x1f] = -4.0;
                      }
                    }
                    else {
                      pfVar6[0x1f] = 4.0;
                    }
                    goto joined_r0x00419bbf;
                  }
                  iVar12 = 6;
                  bVar14 = true;
                  puVar4 = _Memory_01;
                  pcVar8 = "Color";
                  do {
                    if (iVar12 == 0) break;
                    iVar12 = iVar12 + -1;
                    bVar14 = (char)*puVar4 == *pcVar8;
                    puVar4 = (uint *)((int)puVar4 + 1);
                    pcVar8 = pcVar8 + 1;
                  } while (bVar14);
                  if (bVar14) {
                    puVar4 = FUN_00452730(_Str,',');
                    if (puVar4 != (uint *)0x0) {
                      *(undefined1 *)puVar4 = 0;
                      FUN_0041a0a0();
                      lVar7 = _atol((char *)_Str);
                      *(char *)((int)pfVar6 + 0x86) = (char)lVar7;
                      puVar10 = FUN_00452730((uint *)((int)puVar4 + 1),',');
                      if (puVar10 != (uint *)0x0) {
                        *(undefined1 *)puVar10 = 0;
                        FUN_0041a0a0();
                        lVar7 = _atol((char *)((int)puVar4 + 1));
                        *(char *)((int)pfVar6 + 0x85) = (char)lVar7;
                        pcVar8 = (char *)FUN_0041a0a0();
                        lVar7 = _atol(pcVar8);
                        *(char *)(pfVar6 + 0x21) = (char)lVar7;
                      }
                    }
                    goto joined_r0x00419bbf;
                  }
                  iVar12 = 6;
                  bVar14 = true;
                  puVar4 = _Memory_01;
                  pcVar8 = "Alpha";
                  do {
                    if (iVar12 == 0) break;
                    iVar12 = iVar12 + -1;
                    bVar14 = (char)*puVar4 == *pcVar8;
                    puVar4 = (uint *)((int)puVar4 + 1);
                    pcVar8 = pcVar8 + 1;
                  } while (bVar14);
                  if (bVar14) {
                    lVar7 = _atol((char *)_Str);
                    *(char *)((int)pfVar6 + 0x87) = (char)lVar7;
                    goto joined_r0x00419bbf;
                  }
                  iVar12 = 4;
                  bVar14 = true;
                  puVar4 = _Memory_01;
                  pcVar8 = "End";
                  do {
                    if (iVar12 == 0) break;
                    iVar12 = iVar12 + -1;
                    bVar14 = (char)*puVar4 == *pcVar8;
                    puVar4 = (uint *)((int)puVar4 + 1);
                    pcVar8 = pcVar8 + 1;
                  } while (bVar14);
                } while (!bVar14);
                pfVar11 = pfVar6 + 7;
                do {
                  cVar1 = *(char *)pfVar11;
                  pfVar11 = (float *)((int)pfVar11 + 1);
                } while (cVar1 != '\0');
                iVar12 = (int)pfVar11 - ((int)pfVar6 + 0x1d);
                fVar9 = (float)iVar12;
                if (iVar12 < 0) {
                  fVar9 = fVar9 + _DAT_00470b98;
                }
                pfVar6[0x20] = fVar9 * pfVar6[0x1f] * _DAT_00470c5c;
                FUN_0041ab10(local_24 * 3 + 6,(int)(pfVar6 + 3));
                if (param_3 == 0) {
                  puVar5 = operator_new(0x88);
                  if (puVar5 == (undefined4 *)0x0) {
                    pfVar11 = (float *)0x0;
                  }
                  else {
                    pfVar11 = (float *)FUN_00418d00(extraout_ECX_00,puVar5);
                  }
                  pfVar13 = pfVar11;
                  for (iVar12 = 0x22; iVar12 != 0; iVar12 = iVar12 + -1) {
                    *pfVar13 = *pfVar6;
                    pfVar6 = pfVar6 + 1;
                    pfVar13 = pfVar13 + 1;
                  }
                  pfVar11[3] = (float)pfVar11;
                  pfVar11[4] = 0.0;
                  pfVar11[5] = 0.0;
                  FUN_0041ab10(local_24 * 3 + 0x1e,(int)(pfVar11 + 3));
                }
              }
              else {
                local_24 = -1;
              }
            }
          }
        }
      }
    } while (0 < (int)param_2);
  }
  _free(_Memory_00);
  _free(_Memory_01);
  _free(_Str);
  _free(_Memory);
  return 0;
}

