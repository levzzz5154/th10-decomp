/* Raw Ghidra reference; not compilable reconstruction. Address: 00429B60 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __fastcall FUN_00429b60(int param_1,undefined4 param_2,char *param_3)

{
  char cVar1;
  int *piVar2;
  HANDLE pvVar3;
  DWORD nNumberOfBytesToWrite;
  int iVar4;
  byte *_Memory;
  byte *pbVar5;
  undefined4 *lpBuffer;
  tm *ptVar6;
  int iVar7;
  char *pcVar8;
  int iVar9;
  uint uVar10;
  uint uVar11;
  char *pcVar12;
  size_t _Size;
  int *piVar13;
  undefined4 *puVar14;
  byte *pbVar15;
  byte *pbVar16;
  bool bVar17;
  int *local_124;
  byte *local_120;
  DWORD local_11c;
  char *local_118;
  char *local_114;
  char *local_110;
  int local_10c;
  undefined4 *local_108;
  char local_104 [256];
  uint local_4;
  
  local_4 = DAT_00473660 ^ (uint)&local_124;
  pcVar12 = *(char **)(param_1 + 0x18);
  local_110 = (char *)0x0;
  local_118 = (char *)0x0;
  pcVar8 = param_3;
  do {
    cVar1 = *pcVar8;
    pcVar8 = pcVar8 + 1;
    *pcVar12 = cVar1;
    pcVar12 = pcVar12 + 1;
  } while (cVar1 != '\0');
  pcVar12 = param_3 + 1;
  do {
    cVar1 = *param_3;
    param_3 = param_3 + 1;
  } while (cVar1 != '\0');
  for (iVar4 = (int)param_3 - (int)pcVar12; iVar4 < 8; iVar4 = iVar4 + 1) {
    *(undefined1 *)(iVar4 + *(int *)(param_1 + 0x18)) = 0x20;
  }
  local_10c = param_1;
  FUN_00452abc("replay");
  _sprintf(local_104,"replay/%s",param_2);
  local_124 = (int *)(param_1 + 0x40);
  local_120 = (byte *)0x0;
  _Size = 100;
  local_114 = (char *)0x0;
  piVar13 = (int *)(param_1 + 0x1c);
  do {
    if (*piVar13 != 0) {
      if (local_110 == (char *)0x0) {
        local_110 = local_114;
      }
      *(undefined4 *)(*piVar13 + 8) = 0;
      _Size = _Size + 0x1c4;
      for (piVar2 = (int *)*local_124; piVar2 != (int *)0x0; piVar2 = (int *)piVar2[1]) {
        iVar4 = *piVar2;
        _Size = (_Size - 0x5464) +
                ((*(int *)(iVar4 + 0x6274) + ((*(int *)(iVar4 + 0x5460) - iVar4) / 6) * 6) - iVar4);
        *(int *)(*piVar13 + 8) =
             *(int *)(*piVar13 + 8) +
             ((*(int *)(iVar4 + 0x6274) + ((*(int *)(iVar4 + 0x5460) - iVar4) / 6) * 6) - iVar4) +
             -0x5464;
        *(int *)(*piVar13 + 4) = *(int *)(*piVar13 + 4) + (*(int *)(*piVar2 + 0x5460) - *piVar2) / 6
        ;
        param_1 = local_10c;
      }
      local_120 = (byte *)((int)local_120 + 1);
      local_118 = local_114;
    }
    local_114 = local_114 + 1;
    local_124 = local_124 + 3;
    piVar13 = piVar13 + 1;
  } while ((int)local_114 < 8);
  *(byte **)(*(int *)(param_1 + 0x18) + 0x4c) = local_120;
  iVar4 = DAT_00477708;
  *(undefined4 *)(*(int *)(param_1 + 0x18) + 0x10) = DAT_00474c44;
  *(float *)(*(int *)(param_1 + 0x18) + 0x48) =
       (float)((float10)_DAT_00470b44 -
              ((float10)*(double *)(iVar4 + 0x24) / (float10)*(double *)(iVar4 + 0x2c)) *
              (float10)_DAT_00470b44);
  _Memory = _malloc(_Size);
  puVar14 = *(undefined4 **)(param_1 + 0x18);
  pbVar5 = _Memory;
  for (iVar4 = 0x19; iVar4 != 0; iVar4 = iVar4 + -1) {
    *(undefined4 *)pbVar5 = *puVar14;
    puVar14 = puVar14 + 1;
    pbVar5 = pbVar5 + 4;
  }
  local_124 = (int *)(local_10c + 0x40);
  local_108 = (undefined4 *)(local_10c + 0x1c);
  iVar4 = 100;
  local_11c = 8;
  do {
    if ((undefined4 *)*local_108 != (undefined4 *)0x0) {
      puVar14 = (undefined4 *)*local_108;
      pbVar5 = _Memory + iVar4;
      for (iVar9 = 0x71; iVar9 != 0; iVar9 = iVar9 + -1) {
        *(undefined4 *)pbVar5 = *puVar14;
        puVar14 = puVar14 + 1;
        pbVar5 = pbVar5 + 4;
      }
      local_114 = (char *)*local_124;
      iVar4 = iVar4 + 0x1c4;
      if (local_114 != (char *)0x0) {
        do {
          pbVar5 = *(byte **)local_114;
          uVar11 = ((*(int *)(pbVar5 + 0x5460) - (int)pbVar5) / 6) * 3;
          pbVar15 = pbVar5;
          pbVar16 = _Memory + iVar4;
          for (uVar10 = (uVar11 & 0x7fffffff) >> 1; uVar10 != 0; uVar10 = uVar10 - 1) {
            *(undefined4 *)pbVar16 = *(undefined4 *)pbVar15;
            pbVar15 = pbVar15 + 4;
            pbVar16 = pbVar16 + 4;
          }
          for (iVar9 = (uVar11 & 1) << 1; iVar9 != 0; iVar9 = iVar9 + -1) {
            *pbVar16 = *pbVar15;
            pbVar15 = pbVar15 + 1;
            pbVar16 = pbVar16 + 1;
          }
          local_114 = *(char **)(local_114 + 4);
          iVar4 = iVar4 + ((*(int *)(pbVar5 + 0x5460) - (int)pbVar5) / 6) * 6;
        } while (local_114 != (char *)0x0);
        local_114 = (char *)0x0;
      }
      for (piVar13 = (int *)*local_124; piVar13 != (int *)0x0; piVar13 = (int *)piVar13[1]) {
        iVar9 = *piVar13;
        uVar10 = (*(int *)(iVar9 + 0x6274) - iVar9) - 0x5464;
        pbVar5 = (byte *)(iVar9 + 0x5464);
        pbVar15 = _Memory + iVar4;
        for (uVar11 = uVar10 >> 2; uVar11 != 0; uVar11 = uVar11 - 1) {
          *(undefined4 *)pbVar15 = *(undefined4 *)pbVar5;
          pbVar5 = pbVar5 + 4;
          pbVar15 = pbVar15 + 4;
        }
        for (uVar10 = uVar10 & 3; uVar10 != 0; uVar10 = uVar10 - 1) {
          *pbVar15 = *pbVar5;
          pbVar5 = pbVar5 + 1;
          pbVar15 = pbVar15 + 1;
        }
        iVar4 = iVar4 + -0x5464 + (*(int *)(iVar9 + 0x6274) - iVar9);
      }
    }
    local_108 = local_108 + 1;
    local_124 = local_124 + 3;
    local_11c = local_11c - 1;
  } while (local_11c != 0);
  local_120 = _Memory;
  pbVar5 = (byte *)FUN_004359b0(_Memory,iVar4,(int *)&local_11c);
  _free(_Memory);
  nNumberOfBytesToWrite = local_11c;
  EncryptDatBuffer(pbVar5,local_11c,'z',0x80,local_11c);
  EncryptDatBuffer(pbVar5,nNumberOfBytesToWrite,-0x1f,0x400,nNumberOfBytesToWrite);
  iVar9 = local_10c;
  *(int *)(*(int *)(local_10c + 0x14) + 0x20) = iVar4;
  *(DWORD *)(*(int *)(local_10c + 0x14) + 0x1c) = nNumberOfBytesToWrite;
  *(int *)(*(int *)(local_10c + 0x14) + 0xc) = *(int *)(*(int *)(local_10c + 0x14) + 0x1c) + 0x24;
  OpenSharedFileWrite(local_104);
  if (DAT_00474c38 != (HANDLE)0xffffffff) {
    WriteFile(DAT_00474c38,*(LPCVOID *)(iVar9 + 0x14),0x24,&local_11c,(LPOVERLAPPED)0x0);
    if (local_11c != 0x24) {
      CloseHandle(DAT_00474c38);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_004922a4);
      DAT_0049231e = DAT_0049231e + -1;
    }
    if ((DAT_00474c38 != (HANDLE)0xffffffff) &&
       (WriteFile(DAT_00474c38,pbVar5,nNumberOfBytesToWrite,&local_11c,(LPOVERLAPPED)0x0),
       nNumberOfBytesToWrite != local_11c)) {
      CloseHandle(DAT_00474c38);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_004922a4);
      DAT_0049231e = DAT_0049231e + -1;
    }
  }
  if (pbVar5 != (byte *)0x0) {
    _free(pbVar5);
  }
  lpBuffer = _malloc(0xffff);
  puVar14 = lpBuffer;
  for (iVar4 = 0x3fff; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar14 = 0;
    puVar14 = puVar14 + 1;
  }
  *(undefined2 *)puVar14 = 0;
  *(undefined1 *)((int)puVar14 + 2) = 0;
  pcVar12 = (char *)(lpBuffer + 3);
  *lpBuffer = 0x52455355;
  *(undefined1 *)(lpBuffer + 2) = 0;
  iVar4 = _sprintf(pcVar12,&DAT_0046e5e0);
  pcVar12 = pcVar12 + iVar4;
  iVar4 = _sprintf(pcVar12,"Version %s\r\n","1.00a");
  pcVar12 = pcVar12 + iVar4;
  iVar4 = _sprintf(pcVar12,"Name %s\r\n",*(undefined4 *)(iVar9 + 0x18));
  pcVar12 = pcVar12 + iVar4;
  ptVar6 = _localtime((time_t *)(*(int *)(iVar9 + 0x18) + 0xc));
  iVar4 = _sprintf(pcVar12,"Date %.2d/%.2d/%.2d %.2d:%.2d\r\n",ptVar6->tm_year % 100,
                   ptVar6->tm_mon + 1,ptVar6->tm_mday,ptVar6->tm_hour,ptVar6->tm_min);
  pcVar12 = pcVar12 + iVar4;
  iVar4 = _sprintf(pcVar12,"Chara %s\r\n");
  iVar7 = _sprintf(pcVar12 + iVar4,"Rank %s\r\n",
                   (&PTR_s_Easy_004746f4)[*(int *)(*(int *)(iVar9 + 0x18) + 0x58)]);
  pcVar12 = pcVar12 + iVar4 + iVar7;
  if (*(int *)(*(int *)(iVar9 + 0x18) + 0x5c) < 8) {
    if (local_110 == local_118) {
      if (local_110 == (char *)0x7) {
        iVar4 = _sprintf(pcVar12,"Extra Stage\r\n");
      }
      else {
        iVar4 = _sprintf(pcVar12,"Stage %d\r\n");
      }
    }
    else {
      iVar4 = _sprintf(pcVar12,&DAT_0046e52c,local_110);
    }
  }
  else if (local_110 == (char *)0x7) {
    iVar4 = _sprintf(pcVar12,"Extra Stage Clear\r\n");
  }
  else {
    iVar4 = _sprintf(pcVar12,"Stage All Clear\r\n");
  }
  pcVar12 = pcVar12 + iVar4;
  iVar4 = _sprintf(pcVar12,"Score %d\r\n");
  iVar9 = _sprintf(pcVar12 + iVar4,"Slow Rate %2.2f\r\n",
                   (double)*(float *)(*(int *)(iVar9 + 0x18) + 0x48));
  pvVar3 = DAT_00474c38;
  pcVar12 = pcVar12 + iVar4 + iVar9 + 1;
  uVar11 = (int)pcVar12 - (int)lpBuffer & 0x80000003;
  if ((int)uVar11 < 0) {
    uVar11 = (uVar11 - 1 | 0xfffffffc) + 1;
  }
  if (uVar11 != 0) {
    pcVar12 = pcVar12 + (4 - uVar11);
  }
  pcVar12 = pcVar12 + -(int)lpBuffer;
  bVar17 = DAT_00474c38 != (HANDLE)0xffffffff;
  lpBuffer[1] = pcVar12;
  if ((bVar17) &&
     (WriteFile(pvVar3,lpBuffer,(DWORD)pcVar12,(LPDWORD)&local_118,(LPOVERLAPPED)0x0),
     pcVar12 != local_118)) {
    CloseHandle(DAT_00474c38);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_004922a4);
    DAT_0049231e = DAT_0049231e + -1;
  }
  puVar14 = lpBuffer;
  for (iVar4 = 0x3fff; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar14 = 0;
    puVar14 = puVar14 + 1;
  }
  *(undefined2 *)puVar14 = 0;
  *(undefined1 *)((int)puVar14 + 2) = 0;
  *lpBuffer = 0x52455355;
  *(undefined1 *)(lpBuffer + 2) = 1;
  iVar4 = _sprintf((char *)(lpBuffer + 3),&DAT_0046e4f8);
  pvVar3 = DAT_00474c38;
  iVar4 = (int)lpBuffer + iVar4 + 0xd;
  uVar11 = iVar4 - (int)lpBuffer & 0x80000003;
  if ((int)uVar11 < 0) {
    uVar11 = (uVar11 - 1 | 0xfffffffc) + 1;
  }
  if (uVar11 != 0) {
    iVar4 = iVar4 + (4 - uVar11);
  }
  pcVar12 = (char *)(iVar4 - (int)lpBuffer);
  bVar17 = DAT_00474c38 != (HANDLE)0xffffffff;
  lpBuffer[1] = pcVar12;
  if ((bVar17) &&
     (WriteFile(pvVar3,lpBuffer,(DWORD)pcVar12,(LPDWORD)&local_118,(LPOVERLAPPED)0x0),
     pcVar12 != local_118)) {
    CloseHandle(DAT_00474c38);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_004922a4);
    DAT_0049231e = DAT_0049231e + -1;
  }
  _free(lpBuffer);
  if (DAT_00474c38 != (HANDLE)0xffffffff) {
    CloseHandle(DAT_00474c38);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_004922a4);
    DAT_0049231e = DAT_0049231e + -1;
  }
  return 0;
}

