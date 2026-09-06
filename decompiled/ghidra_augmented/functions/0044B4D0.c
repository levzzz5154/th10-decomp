/* Raw Ghidra reference; not compilable reconstruction. Address: 0044B4D0 */

undefined4 ProbeFileExists(LPCSTR param_1)

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

