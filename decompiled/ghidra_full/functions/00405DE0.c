/* Raw Ghidra reference; not compilable reconstruction. Address: 00405DE0 */

void __fastcall FUN_00405de0(int param_1)

{
  if (*(void **)(param_1 + 0x360) != (void *)0x0) {
    _free(*(void **)(param_1 + 0x360));
  }
  *(undefined4 *)(param_1 + 0x360) = 0;
  return;
}

