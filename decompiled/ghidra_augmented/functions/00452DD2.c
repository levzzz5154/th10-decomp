/* Raw Ghidra reference; not compilable reconstruction. Address: 00452DD2 */

/* WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog */
/* WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3 */
/* Library Function - Single Match
    __onexit
   
   Library: Visual Studio 2003 Release */

_onexit_t __cdecl __onexit(_onexit_t _Func)

{
  _onexit_t p_Var1;
  
  FUN_00457577();
  p_Var1 = (_onexit_t)__onexit_lk();
  FUN_00452e04();
  return p_Var1;
}

