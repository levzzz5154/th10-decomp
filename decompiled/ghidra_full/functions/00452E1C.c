/* Raw Ghidra reference; not compilable reconstruction. Address: 00452E1C */

void __endthread(void)

{
  _ptiddata p_Var1;
  
  if (PTR_FUN_004733b0 != (undefined *)0x0) {
    (*(code *)PTR_FUN_004733b0)();
  }
  p_Var1 = __getptd();
  if (p_Var1 == (_ptiddata)0x0) {
    __amsg_exit(0x10);
  }
  if ((HANDLE)p_Var1->_thandle != (HANDLE)0xffffffff) {
    CloseHandle((HANDLE)p_Var1->_thandle);
  }
  __freeptd(p_Var1);
                    /* WARNING: Subroutine does not return */
  ExitThread(0);
}

