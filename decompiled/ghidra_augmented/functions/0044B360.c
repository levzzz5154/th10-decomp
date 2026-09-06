/* Raw Ghidra reference; not compilable reconstruction. Address: 0044B360 */

byte * FUN_0044b360(size_t *param_1,int param_2)

{
  undefined4 *puVar1;
  int iVar2;
  size_t *psVar3;
  char *in_EAX;
  char *pcVar4;
  char *pcVar5;
  int iVar6;
  byte *lpBuffer;
  HANDLE hFile;
  
  psVar3 = param_1;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_004922a4);
  DAT_0049231e = DAT_0049231e + '\x01';
  if (param_2 == 0) {
    pcVar4 = _strrchr(in_EAX,0x5c);
    pcVar5 = in_EAX;
    if (pcVar4 != (char *)0x0) {
      pcVar5 = pcVar4 + 1;
    }
    pcVar5 = _strrchr(pcVar5,0x2f);
    if (pcVar5 != (char *)0x0) {
      in_EAX = pcVar5 + 1;
    }
    puVar1 = DAT_00497990;
    iVar2 = DAT_00497994;
    if (DAT_00497990 != (undefined4 *)0x0) {
      for (; 0 < iVar2; iVar2 = iVar2 + -1) {
        iVar6 = __stricmp(in_EAX,(char *)*puVar1);
        if (iVar6 == 0) {
          param_1 = (size_t *)puVar1[2];
          goto LAB_0044b3ea;
        }
        puVar1 = puVar1 + 4;
      }
    }
    param_1 = (size_t *)0x0;
LAB_0044b3ea:
    if (psVar3 != (size_t *)0x0) {
      *psVar3 = (size_t)param_1;
    }
    if ((param_1 != (size_t *)0x0) && (lpBuffer = _malloc((size_t)param_1), lpBuffer != (byte *)0x0)
       ) {
      FUN_00434dd0(0x497990,lpBuffer);
LAB_0044b4a8:
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_004922a4);
      DAT_0049231e = DAT_0049231e + -1;
      return lpBuffer;
    }
  }
  else {
    hFile = CreateFileA(in_EAX,0x80000000,1,(LPSECURITY_ATTRIBUTES)0x0,3,0x8000080,(HANDLE)0x0);
    if (hFile != (HANDLE)0xffffffff) {
      param_1 = (size_t *)GetFileSize(hFile,(LPDWORD)0x0);
      lpBuffer = _malloc((size_t)param_1);
      if (lpBuffer != (byte *)0x0) {
        ReadFile(hFile,lpBuffer,(DWORD)param_1,(LPDWORD)&param_1,(LPOVERLAPPED)0x0);
        if (psVar3 != (size_t *)0x0) {
          *psVar3 = (size_t)param_1;
        }
        CloseHandle(hFile);
        goto LAB_0044b4a8;
      }
      CloseHandle(hFile);
    }
  }
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_004922a4);
  DAT_0049231e = DAT_0049231e + -1;
  return (byte *)0x0;
}

