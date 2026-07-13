/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0041AD60
 * Tracking name: FUN_0041ad60
 * Ghidra name: FUN_0041ad60
 * Tracked span: 48 bytes
 */


void __fastcall FUN_0041ad60(int param_1)

{
  if (*(void **)(param_1 + 0x358) != (void *)0x0) {
    _free(*(void **)(param_1 + 0x358));
  }
  *(undefined4 *)(param_1 + 0x358) = 0;
  return;
}

