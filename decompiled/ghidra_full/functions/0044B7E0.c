/* Raw Ghidra reference; not compilable reconstruction. Address: 0044B7E0 */

undefined4 CloseProbeFile(void)

{
  if (DAT_00474c38 != (HANDLE)0xffffffff) {
    CloseHandle(DAT_00474c38);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_004922a4);
    DAT_0049231e = DAT_0049231e + -1;
  }
  return 0;
}

