/* Raw Ghidra reference; not compilable reconstruction. Address: 00462A13 */

/* Library Function - Single Match
    int __cdecl IsExceptionObjectToBeDestroyed(void *)
   
   Library: Visual Studio 2003 Release */

int __cdecl IsExceptionObjectToBeDestroyed(void *param_1)

{
  _ptiddata p_Var1;
  int *piVar2;
  
  p_Var1 = __getptd();
  piVar2 = p_Var1->_curexception;
  while( true ) {
    if (piVar2 == (int *)0x0) {
      return 1;
    }
    if ((void *)*piVar2 == param_1) break;
    piVar2 = (int *)piVar2[1];
  }
  return 0;
}

