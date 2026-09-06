/* Raw Ghidra reference; not compilable reconstruction. Address: 00457250 */

/* WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog */
/* WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3 */
/* Library Function - Single Match
    __isindst
   
   Library: Visual Studio 2003 Release */

int __cdecl __isindst(tm *_Time)

{
  bool bVar1;
  undefined3 extraout_var;
  
  __lock(6);
  bVar1 = __isindst_lk();
  FUN_00457285();
  return CONCAT31(extraout_var,bVar1);
}

