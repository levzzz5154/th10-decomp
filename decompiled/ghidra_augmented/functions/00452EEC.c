/* Raw Ghidra reference; not compilable reconstruction. Address: 00452EEC */

/* Library Function - Single Match
    __beginthread
   
   Library: Visual Studio 2003 Release */

uintptr_t __cdecl __beginthread(_StartAddress *_StartAddress,uint _StackSize,void *_ArgList)

{
  int *piVar1;
  _ptiddata _Ptd;
  HANDLE hThread;
  DWORD DVar2;
  pthreadlocinfo unaff_ESI;
  
  DVar2 = 0;
  if (_StartAddress == (_StartAddress *)0x0) {
    piVar1 = FUN_00456af2();
    *piVar1 = 0x16;
  }
  else {
    _Ptd = (_ptiddata)FUN_0045794d(1,0x8c);
    if (_Ptd != (_ptiddata)0x0) {
      __initptd(_Ptd,unaff_ESI);
      *(_StartAddress **)_Ptd->_con_ch_buf = _StartAddress;
      *(void **)(_Ptd->_con_ch_buf + 4) = _ArgList;
      hThread = CreateThread((LPSECURITY_ATTRIBUTES)0x0,_StackSize,FUN_00452e5a,_Ptd,4,(LPDWORD)_Ptd
                            );
      _Ptd->_thandle = (uintptr_t)hThread;
      if ((hThread != (HANDLE)0x0) && (DVar2 = ResumeThread(hThread), DVar2 != 0xffffffff)) {
        return (uintptr_t)hThread;
      }
      DVar2 = GetLastError();
    }
    _free(_Ptd);
    if (DVar2 != 0) {
      __dosmaperr(DVar2);
    }
  }
  return 0xffffffff;
}

