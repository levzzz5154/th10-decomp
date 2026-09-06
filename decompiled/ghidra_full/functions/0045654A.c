/* Raw Ghidra reference; not compilable reconstruction. Address: 0045654A */

/* Library Function - Single Match
    __mtinit
   
   Library: Visual Studio 2003 Release */

int __cdecl __mtinit(void)

{
  int iVar1;
  HMODULE hModule;
  DWORD *pDVar2;
  DWORD DVar3;
  
  iVar1 = __mtinitlocks();
  if (iVar1 == 0) {
    __mtterm();
    return 0;
  }
  hModule = GetModuleHandleA("kernel32.dll");
  if (hModule != (HMODULE)0x0) {
    DAT_00477374 = GetProcAddress(hModule,"FlsAlloc");
    DAT_00477378 = GetProcAddress(hModule,"FlsGetValue");
    DAT_0047737c = GetProcAddress(hModule,"FlsSetValue");
    DAT_00477380 = GetProcAddress(hModule,"FlsFree");
    if (DAT_00477378 == (FARPROC)0x0) {
      DAT_00477378 = TlsGetValue_exref;
      DAT_0047737c = TlsSetValue_exref;
      DAT_00477374 = FUN_0045631e;
      DAT_00477380 = TlsFree_exref;
    }
  }
  DAT_00473390 = (*DAT_00477374)(__freefls_4);
  if (((DAT_00473390 != -1) && (pDVar2 = (DWORD *)FUN_0045794d(1,0x8c), pDVar2 != (DWORD *)0x0)) &&
     (iVar1 = (*DAT_0047737c)(DAT_00473390,pDVar2), iVar1 != 0)) {
    pDVar2[0x15] = (DWORD)&DAT_004735d0;
    pDVar2[5] = 1;
    DVar3 = GetCurrentThreadId();
    pDVar2[1] = 0xffffffff;
    *pDVar2 = DVar3;
    return 1;
  }
  __mtterm();
  return 0;
}

