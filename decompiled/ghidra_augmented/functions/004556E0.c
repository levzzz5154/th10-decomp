/* Raw Ghidra reference; not compilable reconstruction. Address: 004556E0 */

/* WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog */
/* Library Function - Single Match
    void __cdecl _inconsistency(void)
   
   Library: Visual Studio 2003 Release */

void __cdecl _inconsistency(void)

{
  if (PTR_terminate_004731a8 != (undefined *)0x0) {
    (*(code *)PTR_terminate_004731a8)();
    return;
  }
                    /* WARNING: Subroutine does not return */
  terminate();
}

