/* Raw Ghidra reference; not compilable reconstruction. Address: 0045E0E4 */

/* WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog */
/* WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3 */
/* Library Function - Single Match
    _getenv
   
   Library: Visual Studio 2003 Release */

char * __cdecl _getenv(char *_VarName)

{
  char *pcVar1;
  
  __lock(7);
  pcVar1 = (char *)__getenv_lk((uchar *)_VarName);
  FUN_0045e11a();
  return pcVar1;
}

