/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00405DE0
 * Tracking name: FUN_00405de0
 * Ghidra name: FUN_00405de0
 * Tracked span: 64 bytes
 */


void __fastcall FUN_00405de0(int param_1)

{
  if (*(void **)(param_1 + 0x360) != (void *)0x0) {
    _free(*(void **)(param_1 + 0x360));
  }
  *(undefined4 *)(param_1 + 0x360) = 0;
  return;
}

