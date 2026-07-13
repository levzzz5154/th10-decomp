/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0044B6B0
 * Tracking name: FUN_0044b6b0
 * Ghidra name: FUN_0044b6b0
 * Tracked span: 144 bytes
 */


undefined4 FUN_0044b6b0(LPCSTR param_1)

{
  DWORD dwMessageId;
  DWORD dwLanguageId;
  LPCSTR *lpBuffer;
  DWORD nSize;
  va_list *Arguments;
  
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_004922a4);
  DAT_0049231e = DAT_0049231e + '\x01';
  DAT_00474c38 = CreateFileA(param_1,0x80000000,1,(LPSECURITY_ATTRIBUTES)0x0,3,0x8000080,(HANDLE)0x0
                            );
  if (DAT_00474c38 == (HANDLE)0xffffffff) {
    Arguments = (va_list *)0x0;
    nSize = 0;
    lpBuffer = &param_1;
    dwLanguageId = 0x400;
    dwMessageId = GetLastError();
    FormatMessageA(0x1300,(LPCVOID)0x0,dwMessageId,dwLanguageId,(LPSTR)lpBuffer,nSize,Arguments);
    LocalFree(param_1);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_004922a4);
    DAT_0049231e = DAT_0049231e + -1;
    return 0xffffffff;
  }
  return 0;
}

