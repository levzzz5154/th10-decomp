/* Raw Ghidra reference; not compilable reconstruction. Address: 00439FF0 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int FUN_00439ff0(void)

{
  char cVar1;
  byte bVar2;
  DWORD DVar3;
  char *pcVar4;
  byte *pbVar5;
  int iVar6;
  byte *pbVar7;
  LPSTR *ppCVar8;
  bool bVar9;
  _STARTUPINFOA local_258;
  byte local_214 [264];
  byte local_10c [264];
  uint local_4;
  
  local_4 = DAT_00473660 ^ (uint)&local_258;
  DAT_00497ba8 = CreateMutexA((LPSECURITY_ATTRIBUTES)0x0,1,"Touhou 10 App");
  DVar3 = GetLastError();
  if (DVar3 == 0xb7) {
    FUN_0044b8e0(&DAT_0046f394);
    return -1;
  }
  local_258.cb = 0x44;
  ppCVar8 = &local_258.lpReserved;
  for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
    *ppCVar8 = (LPSTR)0x0;
    ppCVar8 = ppCVar8 + 1;
  }
  GetModuleFileNameA((HMODULE)0x0,(LPSTR)local_10c,0x105);
  GetConsoleTitleA((LPSTR)local_214,0x105);
  GetStartupInfoA(&local_258);
  if (local_258.lpTitle == (char *)0x0) {
    DAT_00491ff4 = DAT_00491ff4 | 0x40;
  }
  else {
    pcVar4 = _strrchr(local_258.lpTitle,0x2e);
    iVar6 = ProbeFileExists(local_258.lpTitle);
    if ((iVar6 != 0) && (pcVar4 != (char *)0x0)) {
      iVar6 = __stricmp(pcVar4,".lnk");
      if (iVar6 == 0) {
        do {
          FUN_0043a290(local_258.lpTitle);
          pcVar4 = _strrchr((char *)local_214,0x2e);
          iVar6 = __stricmp(pcVar4,".lnk");
        } while (iVar6 == 0);
      }
      else {
        iVar6 = -(int)local_258.lpTitle;
        do {
          cVar1 = *local_258.lpTitle;
          local_258.lpTitle[(int)(local_214 + iVar6)] = cVar1;
          local_258.lpTitle = local_258.lpTitle + 1;
        } while (cVar1 != '\0');
      }
      pbVar7 = local_214;
      pbVar5 = local_10c;
      do {
        bVar2 = *pbVar5;
        bVar9 = bVar2 < *pbVar7;
        if (bVar2 != *pbVar7) {
LAB_0043a15d:
          iVar6 = (1 - (uint)bVar9) - (uint)(bVar9 != 0);
          goto LAB_0043a162;
        }
        if (bVar2 == 0) break;
        bVar2 = pbVar5[1];
        bVar9 = bVar2 < pbVar7[1];
        if (bVar2 != pbVar7[1]) goto LAB_0043a15d;
        pbVar5 = pbVar5 + 2;
        pbVar7 = pbVar7 + 2;
      } while (bVar2 != 0);
      iVar6 = 0;
LAB_0043a162:
      if (iVar6 != 0) {
        DAT_00492518 = 1;
      }
    }
    DAT_00491ff4 = DAT_00491ff4 & 0xffffffbf;
  }
  return (DAT_00497ba8 != (HANDLE)0x0) - 1;
}

