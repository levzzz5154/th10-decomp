/* Raw Ghidra reference; not compilable reconstruction. Address: 0044B790 */

void * ReadSharedFile(void)

{
  void *lpBuffer;
  size_t unaff_EDI;
  DWORD local_4;
  
  if (DAT_00474c38 == (HANDLE)0xffffffff) {
    return (void *)0x0;
  }
  lpBuffer = _malloc(unaff_EDI);
  if (lpBuffer == (void *)0x0) {
    CloseHandle(DAT_00474c38);
    return (void *)0x0;
  }
  ReadFile(DAT_00474c38,lpBuffer,unaff_EDI,&local_4,(LPOVERLAPPED)0x0);
  return lpBuffer;
}

