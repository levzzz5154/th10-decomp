/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0043C870
 * Tracking name: FUN_0043c870
 * Ghidra name: FUN_0043c870
 * Tracked span: 64 bytes
 */


undefined4 __fastcall FUN_0043c870(void *param_1)

{
  if (param_1 != (void *)0x0) {
    FUN_0043cb00((int)param_1);
    _free(param_1);
  }
  return 0;
}

