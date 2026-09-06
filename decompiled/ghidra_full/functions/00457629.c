/* Raw Ghidra reference; not compilable reconstruction. Address: 00457629 */

/* WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog */
/* WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3 */
/* WARNING: Removing unreachable block (ram,0x004576dd) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    _doexit
   
   Library: Visual Studio 2003 Release */

void __cdecl doexit(UINT param_1,int param_2,int param_3)

{
  HANDLE hProcess;
  UINT uExitCode;
  
  __lock(8);
  if (DAT_004774b0 == 1) {
    uExitCode = param_1;
    hProcess = GetCurrentProcess();
    TerminateProcess(hProcess,uExitCode);
  }
  _DAT_004774ac = 1;
  DAT_004774a8 = (undefined1)param_3;
  if (param_2 == 0) {
    if (DAT_00499310 != (undefined4 *)0x0) {
      while (DAT_0049930c = DAT_0049930c + -1, DAT_00499310 <= DAT_0049930c) {
        if ((code *)*DAT_0049930c != (code *)0x0) {
          (*(code *)*DAT_0049930c)();
        }
      }
    }
    __initterm((undefined4 *)&DAT_00473058);
  }
  __initterm((undefined4 *)&DAT_00473064);
  FUN_004576d8();
  if (param_3 != 0) {
    return;
  }
  DAT_004774b0 = 1;
  ___crtExitProcess(param_1);
  return;
}

