/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x004381F0
 * Tracking name: FUN_004381f0
 * Ghidra name: FUN_004381f0
 * Tracked span: 112 bytes
 */


void __fastcall FUN_004381f0(int param_1)

{
  if (0xf < *(uint *)(param_1 + 0x18)) {
    _free(*(void **)(param_1 + 4));
  }
  *(undefined4 *)(param_1 + 0x18) = 0xf;
  *(undefined4 *)(param_1 + 0x14) = 0;
  *(undefined1 *)(param_1 + 4) = 0;
  return;
}

