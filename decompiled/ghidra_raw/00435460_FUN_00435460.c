/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00435460
 * Tracking name: FUN_00435460
 * Ghidra name: FUN_00435460
 * Tracked span: 288 bytes
 */


void __fastcall FUN_00435460(int param_1)

{
  if (*(HANDLE *)(param_1 + 4) != (HANDLE)0xffffffff) {
    CloseHandle(*(HANDLE *)(param_1 + 4));
    *(undefined4 *)(param_1 + 4) = 0xffffffff;
    *(undefined4 *)(param_1 + 8) = 0;
  }
  return;
}

