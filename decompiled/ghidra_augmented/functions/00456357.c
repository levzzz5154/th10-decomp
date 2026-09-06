/* Raw Ghidra reference; not compilable reconstruction. Address: 00456357 */

/* Library Function - Single Match
    __getptd
   
   Library: Visual Studio 2003 Release */

_ptiddata __cdecl __getptd(void)

{
  DWORD dwErrCode;
  _ptiddata p_Var1;
  int iVar2;
  DWORD DVar3;
  
  dwErrCode = GetLastError();
  p_Var1 = (_ptiddata)(*DAT_00477378)(DAT_00473390);
  if (p_Var1 == (_ptiddata)0x0) {
    p_Var1 = (_ptiddata)FUN_0045794d(1,0x8c);
    if (p_Var1 != (_ptiddata)0x0) {
      iVar2 = (*DAT_0047737c)(DAT_00473390,p_Var1);
      if (iVar2 != 0) {
        p_Var1->_initaddr = &DAT_004735d0;
        p_Var1->_holdrand = 1;
        DVar3 = GetCurrentThreadId();
        p_Var1->_thandle = 0xffffffff;
        p_Var1->_tid = DVar3;
        goto LAB_004563bc;
      }
    }
    __amsg_exit(0x10);
  }
LAB_004563bc:
  SetLastError(dwErrCode);
  return p_Var1;
}

