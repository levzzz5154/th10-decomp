/* Raw Ghidra reference; not compilable reconstruction. Address: 00435510 */

DWORD __fastcall FUN_00435510(int param_1)

{
  DWORD DVar1;
  
  if (*(HANDLE *)(param_1 + 4) == (HANDLE)0xffffffff) {
    return 0;
  }
  DVar1 = SetFilePointer(*(HANDLE *)(param_1 + 4),0,(PLONG)0x0,1);
  return DVar1;
}

