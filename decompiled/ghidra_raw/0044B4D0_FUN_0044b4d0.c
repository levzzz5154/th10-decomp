/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0044B4D0
 * Tracking name: FUN_0044b4d0
 * Ghidra name: FUN_0044b4d0
 * Tracked span: 112 bytes
 */


undefined4 FUN_0044b4d0(LPCSTR param_1)

{
  HANDLE hObject;
  
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_004922a4);
  DAT_0049231e = DAT_0049231e + '\x01';
  hObject = CreateFileA(param_1,0x80000000,1,(LPSECURITY_ATTRIBUTES)0x0,3,0x8000080,(HANDLE)0x0);
  if (hObject != (HANDLE)0xffffffff) {
    CloseHandle(hObject);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_004922a4);
    DAT_0049231e = DAT_0049231e + -1;
    return 1;
  }
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_004922a4);
  DAT_0049231e = DAT_0049231e + -1;
  return 0;
}

