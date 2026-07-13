/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0044BD10
 * Tracking name: FUN_0044bd10
 * Ghidra name: FUN_0044bd10
 * Tracked span: 272 bytes
 */


/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int FUN_0044bd10(void)

{
  int iVar1;
  _OSVERSIONINFOA *p_Var2;
  _OSVERSIONINFOA local_a8;
  uint local_c;
  
  local_c = DAT_00473660 ^ (uint)&stack0xfffffffc;
  p_Var2 = &local_a8;
  for (iVar1 = 0x25; iVar1 != 0; iVar1 = iVar1 + -1) {
    p_Var2->dwOSVersionInfoSize = 0;
    p_Var2 = (_OSVERSIONINFOA *)&p_Var2->dwMajorVersion;
  }
  local_a8.dwOSVersionInfoSize = 0x94;
  GetVersionExA(&local_a8);
  if (local_a8.dwPlatformId == 0) {
    return 0x1f;
  }
  if (local_a8.dwPlatformId == 1) {
    if (local_a8.dwMajorVersion == 4) {
      return (-(uint)(local_a8.dwMinorVersion != 0) & 3) + 0x5f;
    }
    return local_a8.dwMajorVersion * 100 + local_a8.dwMinorVersion;
  }
  if (local_a8.dwPlatformId != 2) {
    return -1;
  }
  if (local_a8.dwMajorVersion == 5) {
    return 2000;
  }
  return (local_a8.dwMajorVersion * 100 + local_a8.dwMinorVersion) * 10;
}

