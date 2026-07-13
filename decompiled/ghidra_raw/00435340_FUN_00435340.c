/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00435340
 * Tracking name: FUN_00435340
 * Ghidra name: FUN_00435340
 * Tracked span: 48 bytes
 */


void __fastcall FUN_00435340(undefined4 *param_1)

{
  *param_1 = &PTR_FUN_0046f230;
  if ((HANDLE)param_1[1] != (HANDLE)0xffffffff) {
    CloseHandle((HANDLE)param_1[1]);
    param_1[1] = 0xffffffff;
    param_1[2] = 0;
  }
  *param_1 = &PTR_LAB_0046f210;
  return;
}

