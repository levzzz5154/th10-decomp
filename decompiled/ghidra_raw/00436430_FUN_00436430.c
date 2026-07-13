/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00436430
 * Tracking name: FUN_00436430
 * Ghidra name: FUN_00436430
 * Tracked span: 320 bytes
 */


void __fastcall FUN_00436430(int param_1)

{
  if (*(void **)(param_1 + 0xc) != (void *)0x0) {
    _free(*(void **)(param_1 + 0xc));
    *(undefined4 *)(param_1 + 0xc) = 0;
  }
  *(undefined4 *)(param_1 + 0xc) = 0;
  *(undefined4 *)(param_1 + 4) = 0;
  *(undefined4 *)(param_1 + 8) = 0;
  return;
}

