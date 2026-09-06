/* Raw Ghidra reference; not compilable reconstruction. Address: 004535BD */

void __cdecl __endthreadex(uint _Retval)

{
  _ptiddata _Ptd;
  
  if (PTR_FUN_004733b0 != (undefined *)0x0) {
    (*(code *)PTR_FUN_004733b0)();
  }
  _Ptd = __getptd();
  if (_Ptd == (_ptiddata)0x0) {
    __amsg_exit(0x10);
  }
  __freeptd(_Ptd);
                    /* WARNING: Subroutine does not return */
  ExitThread(_Retval);
}

