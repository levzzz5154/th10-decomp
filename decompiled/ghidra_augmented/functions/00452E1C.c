/* Raw Ghidra reference; not compilable reconstruction. Address: 00452E1C */

void __cdecl __endthread(void)

{
  _ptiddata _Ptd;
  
  if (PTR_FUN_004733b0 != (undefined *)0x0) {
    (*(code *)PTR_FUN_004733b0)();
  }
  _Ptd = __getptd();
  if (_Ptd == (_ptiddata)0x0) {
    __amsg_exit(0x10);
  }
  if ((HANDLE)_Ptd->_thandle != (HANDLE)0xffffffff) {
    CloseHandle((HANDLE)_Ptd->_thandle);
  }
  __freeptd(_Ptd);
                    /* WARNING: Subroutine does not return */
  ExitThread(0);
}

