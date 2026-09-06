/* Raw Ghidra reference; not compilable reconstruction. Address: 00463A5C */

/* Library Function - Single Match
    long __stdcall __CxxUnhandledExceptionFilter(struct _EXCEPTION_POINTERS *)
   
   Library: Visual Studio 2003 Release */

int __CxxUnhandledExceptionFilter(int *param_1)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = (int *)*param_1;
  if (((*piVar1 == -0x1f928c9d) && (piVar1[4] == 3)) &&
     ((piVar1[5] == 0x19930520 || (piVar1[5] == 0x19930521)))) {
                    /* WARNING: Subroutine does not return */
    terminate();
  }
  if ((DAT_004776d8 != (_func_int *)0x0) && (iVar2 = _ValidateExecute(DAT_004776d8), iVar2 != 0)) {
    iVar2 = (*DAT_004776d8)(param_1);
    return iVar2;
  }
  return 0;
}

