/* Raw Ghidra reference; not compilable reconstruction. Address: 0045980E */

/* WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog */
/* WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3 */
/* Library Function - Single Match
    ___crtInitCritSecAndSpinCount
   
   Library: Visual Studio 2003 Release */

void __cdecl ___crtInitCritSecAndSpinCount(undefined4 param_1,undefined4 param_2)

{
  HMODULE hModule;
  
  if (DAT_004775c4 == (code *)0x0) {
    if (DAT_00477470 != 1) {
      hModule = GetModuleHandleA("kernel32.dll");
      if (hModule != (HMODULE)0x0) {
        DAT_004775c4 = GetProcAddress(hModule,"InitializeCriticalSectionAndSpinCount");
        if (DAT_004775c4 != (FARPROC)0x0) goto LAB_0045985a;
      }
    }
    DAT_004775c4 = ___crtInitCritSecNoSpinCount_8;
  }
LAB_0045985a:
  (*DAT_004775c4)(param_1,param_2);
  return;
}

