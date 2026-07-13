/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00435370
 * Tracking name: FUN_00435370
 * Ghidra name: FUN_00435370
 * Tracked span: 240 bytes
 */


/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined1 __thiscall FUN_00435370(void *this,LPCSTR param_1,char *param_2)

{
  char cVar1;
  HANDLE hFile;
  DWORD dwCreationDisposition;
  int local_10c;
  char acStack_108 [260];
  uint local_4;
  
  local_4 = DAT_00473660 ^ (uint)&local_10c;
  dwCreationDisposition = 0;
  local_10c = 0;
  (**(code **)(*(int *)this + 4))();
  cVar1 = *param_2;
  if (cVar1 == '\0') {
LAB_004353f6:
    if (*param_2 != '\0') {
      FUN_00435610(acStack_108);
      hFile = CreateFileA(acStack_108,*(DWORD *)((int)this + 8),1,(LPSECURITY_ATTRIBUTES)0x0,
                          dwCreationDisposition,0x8000080,(HANDLE)0x0);
      *(HANDLE *)((int)this + 4) = hFile;
      if (hFile != (HANDLE)0xffffffff) {
        if (local_10c != 0) {
          SetFilePointer(hFile,0,(PLONG)0x0,2);
        }
        return 1;
      }
    }
  }
  else {
    do {
      if (cVar1 == 'r') {
        *(undefined4 *)((int)this + 8) = 0x80000000;
        dwCreationDisposition = 3;
        goto LAB_004353f6;
      }
      if (cVar1 == 'w') {
        DeleteFileA(param_1);
        dwCreationDisposition = 2;
LAB_004353ef:
        *(undefined4 *)((int)this + 8) = 0x40000000;
        goto LAB_004353f6;
      }
      if (cVar1 == 'a') {
        local_10c = 1;
        dwCreationDisposition = 4;
        goto LAB_004353ef;
      }
      cVar1 = param_2[1];
      param_2 = param_2 + 1;
    } while (cVar1 != '\0');
  }
  return 0;
}

