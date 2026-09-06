/* Raw Ghidra reference; not compilable reconstruction. Address: 00453762 */

/* Library Function - Single Match
    _fast_error_exit
   
   Library: Visual Studio 2003 Release */

void __cdecl fast_error_exit(int param_1)

{
  if (DAT_0047720c == 1) {
    __FF_MSGBANNER();
  }
  FUN_00458efd(param_1);
                    /* WARNING: Subroutine does not return */
  ___crtExitProcess(0xff);
}

