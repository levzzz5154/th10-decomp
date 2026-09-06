/* Raw Ghidra reference; not compilable reconstruction. Address: 0044B620 */

undefined4 OpenSharedFileWrite(LPCSTR param_1)

{
  DWORD dwMessageId;
  DWORD dwLanguageId;
  LPCSTR *lpBuffer;
  DWORD nSize;
  va_list *Arguments;
  
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_004922a4);
  DAT_0049231e = DAT_0049231e + '\x01';
  DAT_00474c38 = CreateFileA(param_1,0x40000000,1,(LPSECURITY_ATTRIBUTES)0x0,2,0x80,(HANDLE)0x0);
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

