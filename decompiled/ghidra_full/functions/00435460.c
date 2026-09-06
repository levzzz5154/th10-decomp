/* Raw Ghidra reference; not compilable reconstruction. Address: 00435460 */

void __fastcall FUN_00435460(int param_1)

{
  if (*(HANDLE *)(param_1 + 4) != (HANDLE)0xffffffff) {
    CloseHandle(*(HANDLE *)(param_1 + 4));
    *(undefined4 *)(param_1 + 4) = 0xffffffff;
    *(undefined4 *)(param_1 + 8) = 0;
  }
  return;
}

