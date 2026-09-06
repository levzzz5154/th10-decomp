/* Raw Ghidra reference; not compilable reconstruction. Address: 00462F7C */

/* WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog */
/* WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3 */
/* Library Function - Single Match
    ___DestructExceptionObject
   
   Library: Visual Studio 2003 Release */

void __cdecl ___DestructExceptionObject(int param_1)

{
  void *pvVar1;
  
  if ((param_1 != 0) && (pvVar1 = *(void **)(*(int *)(param_1 + 0x1c) + 4), pvVar1 != (void *)0x0))
  {
    _CallMemberFunction0(*(void **)(param_1 + 0x18),pvVar1);
  }
  return;
}

