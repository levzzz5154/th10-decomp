/* Raw Ghidra reference; not compilable reconstruction. Address: 004537DC */

/* WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog */
/* WARNING: Function: __chkstk replaced with injection: alloca_probe */
/* WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3 */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int entry(void)

{
  HMODULE pHVar1;
  int iVar2;
  int *piVar3;
  _OSVERSIONINFOA local_114;
  _STARTUPINFOA local_74;
  int local_30;
  int local_2c;
  byte *local_24;
  uint local_20;
  undefined1 *local_1c;
  undefined4 uStack_c;
  undefined *local_8;
  
  local_8 = &DAT_0046a770;
  uStack_c = 0x4537e8;
  local_114.szCSDVersion[0x7c] = -0xc;
  local_114.szCSDVersion[0x7d] = '7';
  local_114.szCSDVersion[0x7e] = 'E';
  local_114.szCSDVersion[0x7f] = '\0';
  local_1c = (undefined1 *)&local_114;
  local_114.dwOSVersionInfoSize = 0x94;
  GetVersionExA(&local_114);
  DAT_00477470 = local_114.dwPlatformId;
  DAT_0047747c = local_114.dwMajorVersion;
  _DAT_00477480 = local_114.dwMinorVersion;
  _DAT_00477474 = local_114.dwBuildNumber & 0x7fff;
  if (local_114.dwPlatformId != 2) {
    _DAT_00477474 = _DAT_00477474 | 0x8000;
  }
  _DAT_00477478 = local_114.dwMajorVersion * 0x100 + local_114.dwMinorVersion;
  pHVar1 = GetModuleHandleA((LPCSTR)0x0);
  if (((short)pHVar1->unused == 0x5a4d) &&
     (piVar3 = (int *)((int)&pHVar1->unused + pHVar1[0xf].unused), *piVar3 == 0x4550)) {
    if ((short)piVar3[6] == 0x10b) {
      if (0xe < (uint)piVar3[0x1d]) {
        iVar2 = piVar3[0x3a];
        goto LAB_0045389d;
      }
    }
    else if (((short)piVar3[6] == 0x20b) && (0xe < (uint)piVar3[0x21])) {
      iVar2 = piVar3[0x3e];
LAB_0045389d:
      local_20 = (uint)(iVar2 != 0);
      goto LAB_004538a3;
    }
  }
  local_20 = 0;
LAB_004538a3:
  iVar2 = __heap_init();
  if (iVar2 == 0) {
    fast_error_exit(0x1c);
  }
  iVar2 = __mtinit();
  if (iVar2 == 0) {
    fast_error_exit(0x10);
  }
  __RTC_Initialize();
  local_8 = (undefined *)0x0;
  iVar2 = __ioinit();
  if (iVar2 < 0) {
    __amsg_exit(0x1b);
  }
  DAT_00499348 = GetCommandLineA();
  DAT_00477204 = ___crtGetEnvironmentStringsA();
  iVar2 = __setargv();
  if (iVar2 < 0) {
    __amsg_exit(8);
  }
  iVar2 = __setenvp();
  if (iVar2 < 0) {
    __amsg_exit(9);
  }
  local_2c = __cinit(1);
  if (local_2c != 0) {
    __amsg_exit(local_2c);
  }
  local_74.dwFlags = 0;
  GetStartupInfoA(&local_74);
  local_24 = __wincmdln();
  pHVar1 = GetModuleHandleA((LPCSTR)0x0);
  iVar2 = GameMain(pHVar1);
  local_30 = iVar2;
  if (local_20 == 0) {
                    /* WARNING: Subroutine does not return */
    _exit(iVar2);
  }
  __cexit();
  return iVar2;
}

