/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0041A200
 * Tracking name: FUN_0041a200
 * Ghidra name: FUN_0041a200
 * Tracked span: 2320 bytes
 */


undefined4 FUN_0041a200(int param_1,LPCSTR param_2)

{
  char cVar1;
  char *_Dest;
  int iVar2;
  char *pcVar3;
  tm *ptVar4;
  int *piVar5;
  int iVar6;
  undefined4 extraout_ECX;
  undefined4 uVar7;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  undefined4 extraout_ECX_02;
  undefined4 extraout_ECX_03;
  undefined4 extraout_ECX_04;
  undefined4 extraout_ECX_05;
  undefined4 extraout_ECX_06;
  undefined4 extraout_ECX_07;
  ulonglong uVar8;
  int local_54;
  int local_50;
  int *local_4c;
  int *local_48;
  DWORD local_44;
  DWORD local_40;
  DWORD local_3c;
  DWORD local_38;
  DWORD local_34;
  DWORD local_30;
  DWORD local_2c;
  DWORD local_28;
  DWORD local_24;
  DWORD local_20;
  DWORD local_1c;
  DWORD local_18;
  DWORD local_14;
  DWORD local_10;
  DWORD local_c [2];
  
  _Dest = _malloc(0x1000);
  FUN_00452abc("hint");
  iVar2 = FUN_0044b620(param_2);
  if (iVar2 == 0) {
    _sprintf(_Dest,"# ========================================================= \r\n");
    pcVar3 = _Dest;
    uVar7 = extraout_ECX;
    do {
      cVar1 = *pcVar3;
      uVar7 = CONCAT31((int3)((uint)uVar7 >> 8),cVar1);
      pcVar3 = pcVar3 + 1;
    } while (cVar1 != '\0');
    FUN_0044b740(uVar7,_Dest);
    _sprintf(_Dest,&DAT_0046d510);
    pcVar3 = _Dest;
    uVar7 = extraout_ECX_00;
    do {
      cVar1 = *pcVar3;
      uVar7 = CONCAT31((int3)((uint)uVar7 >> 8),cVar1);
      pcVar3 = pcVar3 + 1;
    } while (cVar1 != '\0');
    FUN_0044b740(uVar7,_Dest);
    _sprintf(_Dest,"#\r\n");
    pcVar3 = _Dest;
    uVar7 = extraout_ECX_01;
    do {
      cVar1 = *pcVar3;
      uVar7 = CONCAT31((int3)((uint)uVar7 >> 8),cVar1);
      pcVar3 = pcVar3 + 1;
    } while (cVar1 != '\0');
    FUN_0044b740(uVar7,_Dest);
    _sprintf(_Dest,&DAT_0046d4d8);
    pcVar3 = _Dest;
    uVar7 = extraout_ECX_02;
    do {
      cVar1 = *pcVar3;
      uVar7 = CONCAT31((int3)((uint)uVar7 >> 8),cVar1);
      pcVar3 = pcVar3 + 1;
    } while (cVar1 != '\0');
    FUN_0044b740(uVar7,_Dest);
    _sprintf(_Dest,&DAT_0046d490);
    pcVar3 = _Dest;
    uVar7 = extraout_ECX_03;
    do {
      cVar1 = *pcVar3;
      uVar7 = CONCAT31((int3)((uint)uVar7 >> 8),cVar1);
      pcVar3 = pcVar3 + 1;
    } while (cVar1 != '\0');
    FUN_0044b740(uVar7,_Dest);
    _sprintf(_Dest,"#\r\n");
    pcVar3 = _Dest;
    uVar7 = extraout_ECX_04;
    do {
      cVar1 = *pcVar3;
      uVar7 = CONCAT31((int3)((uint)uVar7 >> 8),cVar1);
      pcVar3 = pcVar3 + 1;
    } while (cVar1 != '\0');
    FUN_0044b740(uVar7,_Dest);
    FID_conflict___time32((__time32_t *)&local_48);
    ptVar4 = _localtime((time_t *)&local_48);
    _sprintf(_Dest,"#                                Time-stamp: <%.4d/%.2d/%.2d %.2d:%.2d>\r\n",
             ptVar4->tm_year + 0x76c,ptVar4->tm_mon + 1,ptVar4->tm_mday,ptVar4->tm_hour,
             ptVar4->tm_min);
    pcVar3 = _Dest;
    uVar7 = extraout_ECX_05;
    do {
      cVar1 = *pcVar3;
      uVar7 = CONCAT31((int3)((uint)uVar7 >> 8),cVar1);
      pcVar3 = pcVar3 + 1;
    } while (cVar1 != '\0');
    FUN_0044b740(uVar7,_Dest);
    _sprintf(_Dest,"\r\n\r\n");
    pcVar3 = _Dest;
    uVar7 = extraout_ECX_06;
    do {
      cVar1 = *pcVar3;
      uVar7 = CONCAT31((int3)((uint)uVar7 >> 8),cVar1);
      pcVar3 = pcVar3 + 1;
    } while (cVar1 != '\0');
    FUN_0044b740(uVar7,_Dest);
    _sprintf(_Dest,"Version = %s\r\n\r\n");
    pcVar3 = _Dest;
    uVar7 = extraout_ECX_07;
    do {
      cVar1 = *pcVar3;
      uVar7 = CONCAT31((int3)((uint)uVar7 >> 8),cVar1);
      pcVar3 = pcVar3 + 1;
    } while (cVar1 != '\0');
    FUN_0044b740(uVar7,_Dest);
    local_4c = (int *)(param_1 + 0x7c);
    local_54 = 0;
    do {
      piVar5 = (int *)*local_4c;
      local_50 = 0;
      if (piVar5 != (int *)0x0) {
        do {
          local_48 = (int *)piVar5[1];
          iVar2 = *piVar5;
          if (*(int *)(iVar2 + 0x70) != 0) {
            if (local_50 == 0) {
              _sprintf(_Dest,"# ================================== \r\n");
              pcVar3 = _Dest;
              do {
                cVar1 = *pcVar3;
                pcVar3 = pcVar3 + 1;
              } while (cVar1 != '\0');
              if ((DAT_00474c38 != (HANDLE)0xffffffff) &&
                 (WriteFile(DAT_00474c38,_Dest,(int)pcVar3 - (int)(_Dest + 1),&local_44,
                            (LPOVERLAPPED)0x0), (int)pcVar3 - (int)(_Dest + 1) != local_44)) {
                CloseHandle(DAT_00474c38);
                LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_004922a4);
                DAT_0049231e = DAT_0049231e + -1;
              }
              _sprintf(_Dest,"Stage : %d\r\n\r\n");
              pcVar3 = _Dest;
              do {
                cVar1 = *pcVar3;
                pcVar3 = pcVar3 + 1;
              } while (cVar1 != '\0');
              if ((DAT_00474c38 != (HANDLE)0xffffffff) &&
                 (WriteFile(DAT_00474c38,_Dest,(int)pcVar3 - (int)(_Dest + 1),&local_40,
                            (LPOVERLAPPED)0x0), (int)pcVar3 - (int)(_Dest + 1) != local_40)) {
                CloseHandle(DAT_00474c38);
                LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_004922a4);
                DAT_0049231e = DAT_0049231e + -1;
              }
            }
            _sprintf(_Dest,"Tips\r\n");
            pcVar3 = _Dest;
            do {
              cVar1 = *pcVar3;
              pcVar3 = pcVar3 + 1;
            } while (cVar1 != '\0');
            if ((DAT_00474c38 != (HANDLE)0xffffffff) &&
               (WriteFile(DAT_00474c38,_Dest,(int)pcVar3 - (int)(_Dest + 1),&local_3c,
                          (LPOVERLAPPED)0x0), (int)pcVar3 - (int)(_Dest + 1) != local_3c)) {
              CloseHandle(DAT_00474c38);
              LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_004922a4);
              DAT_0049231e = DAT_0049231e + -1;
            }
            if (0 < *(int *)(iVar2 + 0x70)) {
              _sprintf(_Dest,"\tRemain\t: %d\r\n");
            }
            pcVar3 = _Dest;
            do {
              cVar1 = *pcVar3;
              pcVar3 = pcVar3 + 1;
            } while (cVar1 != '\0');
            if ((DAT_00474c38 != (HANDLE)0xffffffff) &&
               (WriteFile(DAT_00474c38,_Dest,(int)pcVar3 - (int)(_Dest + 1),&local_38,
                          (LPOVERLAPPED)0x0), (int)pcVar3 - (int)(_Dest + 1) != local_38)) {
              CloseHandle(DAT_00474c38);
              LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_004922a4);
              DAT_0049231e = DAT_0049231e + -1;
            }
            _sprintf(_Dest,"\tText\t: \"%s\"\r\n");
            pcVar3 = _Dest;
            do {
              cVar1 = *pcVar3;
              pcVar3 = pcVar3 + 1;
            } while (cVar1 != '\0');
            if ((DAT_00474c38 != (HANDLE)0xffffffff) &&
               (WriteFile(DAT_00474c38,_Dest,(int)pcVar3 - (int)(_Dest + 1),&local_34,
                          (LPOVERLAPPED)0x0), (int)pcVar3 - (int)(_Dest + 1) != local_34)) {
              CloseHandle(DAT_00474c38);
              LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_004922a4);
              DAT_0049231e = DAT_0049231e + -1;
            }
            FUN_00463b2c();
            uVar8 = FUN_00463b2c();
            _sprintf(_Dest,"\tPos\t\t: %d, %d\r\n",(int)uVar8);
            pcVar3 = _Dest;
            do {
              cVar1 = *pcVar3;
              pcVar3 = pcVar3 + 1;
            } while (cVar1 != '\0');
            if ((DAT_00474c38 != (HANDLE)0xffffffff) &&
               (WriteFile(DAT_00474c38,_Dest,(int)pcVar3 - (int)(_Dest + 1),&local_30,
                          (LPOVERLAPPED)0x0), (int)pcVar3 - (int)(_Dest + 1) != local_30)) {
              CloseHandle(DAT_00474c38);
              LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_004922a4);
              DAT_0049231e = DAT_0049231e + -1;
            }
            _sprintf(_Dest,"\tCount\t: %d\r\n");
            pcVar3 = _Dest;
            do {
              cVar1 = *pcVar3;
              pcVar3 = pcVar3 + 1;
            } while (cVar1 != '\0');
            if ((DAT_00474c38 != (HANDLE)0xffffffff) &&
               (WriteFile(DAT_00474c38,_Dest,(int)pcVar3 - (int)(_Dest + 1),&local_2c,
                          (LPOVERLAPPED)0x0), (int)pcVar3 - (int)(_Dest + 1) != local_2c)) {
              CloseHandle(DAT_00474c38);
              LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_004922a4);
              DAT_0049231e = DAT_0049231e + -1;
            }
            iVar6 = 0;
            do {
              if ((&DAT_004744b4)[iVar6 * 2] == *(int *)(iVar2 + 0x68)) break;
              iVar6 = iVar6 + 1;
            } while (iVar6 < 0x3d);
            _sprintf(_Dest,"\tBase\t: %s\r\n");
            pcVar3 = _Dest;
            do {
              cVar1 = *pcVar3;
              pcVar3 = pcVar3 + 1;
            } while (cVar1 != '\0');
            if ((DAT_00474c38 != (HANDLE)0xffffffff) &&
               (WriteFile(DAT_00474c38,_Dest,(int)pcVar3 - (int)(_Dest + 1),&local_28,
                          (LPOVERLAPPED)0x0), (int)pcVar3 - (int)(_Dest + 1) != local_28)) {
              CloseHandle(DAT_00474c38);
              LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_004922a4);
              DAT_0049231e = DAT_0049231e + -1;
            }
            iVar6 = 0;
            do {
              if ((&DAT_00474498)[iVar6 * 2] == *(int *)(iVar2 + 100)) break;
              iVar6 = iVar6 + 1;
            } while (iVar6 < 3);
            _sprintf(_Dest,"\tAlign\t: %s\r\n");
            pcVar3 = _Dest;
            do {
              cVar1 = *pcVar3;
              pcVar3 = pcVar3 + 1;
            } while (cVar1 != '\0');
            if ((DAT_00474c38 != (HANDLE)0xffffffff) &&
               (WriteFile(DAT_00474c38,_Dest,(int)pcVar3 - (int)(_Dest + 1),&local_24,
                          (LPOVERLAPPED)0x0), (int)pcVar3 - (int)(_Dest + 1) != local_24)) {
              CloseHandle(DAT_00474c38);
              LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_004922a4);
              DAT_0049231e = DAT_0049231e + -1;
            }
            _sprintf(_Dest,"\tTime\t: %d\r\n");
            pcVar3 = _Dest;
            do {
              cVar1 = *pcVar3;
              pcVar3 = pcVar3 + 1;
            } while (cVar1 != '\0');
            if ((DAT_00474c38 != (HANDLE)0xffffffff) &&
               (WriteFile(DAT_00474c38,_Dest,(int)pcVar3 - (int)(_Dest + 1),&local_20,
                          (LPOVERLAPPED)0x0), (int)pcVar3 - (int)(_Dest + 1) != local_20)) {
              CloseHandle(DAT_00474c38);
              LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_004922a4);
              DAT_0049231e = DAT_0049231e + -1;
            }
            _sprintf(_Dest,"\tAlpha\t: %d\r\n");
            pcVar3 = _Dest;
            do {
              cVar1 = *pcVar3;
              pcVar3 = pcVar3 + 1;
            } while (cVar1 != '\0');
            if ((DAT_00474c38 != (HANDLE)0xffffffff) &&
               (WriteFile(DAT_00474c38,_Dest,(int)pcVar3 - (int)(_Dest + 1),&local_1c,
                          (LPOVERLAPPED)0x0), (int)pcVar3 - (int)(_Dest + 1) != local_1c)) {
              CloseHandle(DAT_00474c38);
              LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_004922a4);
              DAT_0049231e = DAT_0049231e + -1;
            }
            _sprintf(_Dest,"\tColor\t: %d, %d, %d\r\n",(uint)*(byte *)(iVar2 + 0x86),
                     (uint)*(byte *)(iVar2 + 0x85));
            pcVar3 = _Dest;
            do {
              cVar1 = *pcVar3;
              pcVar3 = pcVar3 + 1;
            } while (cVar1 != '\0');
            if ((DAT_00474c38 != (HANDLE)0xffffffff) &&
               (WriteFile(DAT_00474c38,_Dest,(int)pcVar3 - (int)(_Dest + 1),&local_18,
                          (LPOVERLAPPED)0x0), (int)pcVar3 - (int)(_Dest + 1) != local_18)) {
              CloseHandle(DAT_00474c38);
              LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_004922a4);
              DAT_0049231e = DAT_0049231e + -1;
            }
            _sprintf(_Dest,"\tScale\t: %.1f\r\n",(double)*(float *)(iVar2 + 0x7c));
            pcVar3 = _Dest;
            do {
              cVar1 = *pcVar3;
              pcVar3 = pcVar3 + 1;
            } while (cVar1 != '\0');
            if ((DAT_00474c38 != (HANDLE)0xffffffff) &&
               (WriteFile(DAT_00474c38,_Dest,(int)pcVar3 - (int)(_Dest + 1),&local_14,
                          (LPOVERLAPPED)0x0), (int)pcVar3 - (int)(_Dest + 1) != local_14)) {
              CloseHandle(DAT_00474c38);
              LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_004922a4);
              DAT_0049231e = DAT_0049231e + -1;
            }
            _sprintf(_Dest,"End\r\n\r\n");
            pcVar3 = _Dest;
            do {
              cVar1 = *pcVar3;
              pcVar3 = pcVar3 + 1;
            } while (cVar1 != '\0');
            if ((DAT_00474c38 != (HANDLE)0xffffffff) &&
               (WriteFile(DAT_00474c38,_Dest,(int)pcVar3 - (int)(_Dest + 1),&local_10,
                          (LPOVERLAPPED)0x0), (int)pcVar3 - (int)(_Dest + 1) != local_10)) {
              CloseHandle(DAT_00474c38);
              LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_004922a4);
              DAT_0049231e = DAT_0049231e + -1;
            }
            local_50 = local_50 + 1;
            if (0xfe < local_50) break;
          }
          piVar5 = local_48;
        } while (local_48 != (int *)0x0);
        if (local_50 != 0) {
          _sprintf(_Dest,"StageEnd\r\n");
          pcVar3 = _Dest;
          do {
            cVar1 = *pcVar3;
            pcVar3 = pcVar3 + 1;
          } while (cVar1 != '\0');
          if ((DAT_00474c38 != (HANDLE)0xffffffff) &&
             (WriteFile(DAT_00474c38,_Dest,(int)pcVar3 - (int)(_Dest + 1),local_c,(LPOVERLAPPED)0x0)
             , (int)pcVar3 - (int)(_Dest + 1) != local_c[0])) {
            CloseHandle(DAT_00474c38);
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_004922a4);
            DAT_0049231e = DAT_0049231e + -1;
          }
        }
      }
      local_54 = local_54 + 1;
      local_4c = local_4c + 3;
    } while (local_54 < 8);
  }
  if (DAT_00474c38 != (HANDLE)0xffffffff) {
    CloseHandle(DAT_00474c38);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_004922a4);
    DAT_0049231e = DAT_0049231e + -1;
  }
  _free(_Dest);
  return 0;
}

