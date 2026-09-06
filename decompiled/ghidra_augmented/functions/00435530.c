/* Raw Ghidra reference; not compilable reconstruction. Address: 00435530 */

DWORD __fastcall FUN_00435530(int param_1)

{
  DWORD DVar1;
  
  if (*(HANDLE *)(param_1 + 4) == (HANDLE)0xffffffff) {
    return 0;
  }
  DVar1 = GetFileSize(*(HANDLE *)(param_1 + 4),(LPDWORD)0x0);
  return DVar1;
}

