/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00401FF0
 * Tracking name: FUN_00401ff0
 * Ghidra name: FUN_00401ff0
 * Tracked span: 96 bytes
 */


void __fastcall FUN_00401ff0(int param_1)

{
  if (*(void **)(param_1 + 0x358) != (void *)0x0) {
    _free(*(void **)(param_1 + 0x358));
  }
  *(undefined4 *)(param_1 + 0x358) = 0;
  return;
}

