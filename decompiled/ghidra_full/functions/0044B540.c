/* Raw Ghidra reference; not compilable reconstruction. Address: 0044B540 */

undefined4 WriteWholeFile(LPCSTR param_1,LPCVOID param_2)

{
  HANDLE hFile;
  DWORD dwMessageId;
  DWORD unaff_EDI;
  DWORD dwLanguageId;
  LPCSTR *lpBuffer;
  DWORD nSize;
  va_list *Arguments;
  DWORD local_4;
  
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_004922a4);
  DAT_0049231e = DAT_0049231e + '\x01';
  hFile = CreateFileA(param_1,0x40000000,1,(LPSECURITY_ATTRIBUTES)0x0,2,0x80,(HANDLE)0x0);
  Arguments = (va_list *)0x0;
  if (hFile == (HANDLE)0xffffffff) {
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
  WriteFile(hFile,param_2,unaff_EDI,&local_4,(LPOVERLAPPED)0x0);
  if (unaff_EDI != local_4) {
    CloseHandle(hFile);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_004922a4);
    DAT_0049231e = DAT_0049231e + -1;
    return 0xfffffffe;
  }
  CloseHandle(hFile);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_004922a4);
  DAT_0049231e = DAT_0049231e + -1;
  return 0;
}

