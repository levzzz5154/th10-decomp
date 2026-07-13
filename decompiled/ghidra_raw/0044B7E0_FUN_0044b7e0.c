/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0044B7E0
 * Tracking name: FUN_0044b7e0
 * Ghidra name: FUN_0044b7e0
 * Tracked span: 48 bytes
 */


undefined4 FUN_0044b7e0(void)

{
  if (DAT_00474c38 != (HANDLE)0xffffffff) {
    CloseHandle(DAT_00474c38);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_004922a4);
    DAT_0049231e = DAT_0049231e + -1;
  }
  return 0;
}

