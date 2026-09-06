/* Raw Ghidra reference; not compilable reconstruction. Address: 004535BD */

void __endthreadex(DWORD param_1)

{
  _ptiddata p_Var1;
  
  if (PTR_FUN_004733b0 != (undefined *)0x0) {
    (*(code *)PTR_FUN_004733b0)();
  }
  p_Var1 = __getptd();
  if (p_Var1 == (_ptiddata)0x0) {
    __amsg_exit(0x10);
  }
  __freeptd(p_Var1);
                    /* WARNING: Subroutine does not return */
  ExitThread(param_1);
}

