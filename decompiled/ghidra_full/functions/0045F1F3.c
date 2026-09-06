/* Raw Ghidra reference; not compilable reconstruction. Address: 0045F1F3 */

/* Library Function - Single Match
    ___security_init_cookie
   
   Library: Visual Studio 2003 Release */

void __cdecl ___security_init_cookie(void)

{
  DWORD DVar1;
  DWORD DVar2;
  DWORD DVar3;
  LARGE_INTEGER local_14;
  _FILETIME local_c;
  
  if ((DAT_00473660 == 0) || (DAT_00473660 == 0xbb40e64e)) {
    GetSystemTimeAsFileTime(&local_c);
    DVar1 = GetCurrentProcessId();
    DVar2 = GetCurrentThreadId();
    DVar3 = GetTickCount();
    QueryPerformanceCounter(&local_14);
    DAT_00473660 = local_c.dwHighDateTime ^ local_c.dwLowDateTime ^ DVar1 ^ DVar2 ^ DVar3 ^
                   local_14.s.HighPart ^ local_14.s.LowPart;
    if (DAT_00473660 == 0) {
      DAT_00473660 = 0xbb40e64e;
    }
  }
  return;
}

