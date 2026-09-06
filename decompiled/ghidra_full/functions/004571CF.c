/* Raw Ghidra reference; not compilable reconstruction. Address: 004571CF */

/* WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog */
/* WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3 */
/* Library Function - Single Match
    ___tzset
   
   Library: Visual Studio 2003 Release */

void __cdecl ___tzset(void)

{
  if (DAT_00477444 == 0) {
    __lock(6);
    if (DAT_00477444 == 0) {
      __tzset_lk();
      DAT_00477444 = DAT_00477444 + 1;
    }
    FUN_00457212();
  }
  return;
}

