/* Raw Ghidra reference; not compilable reconstruction. Address: 00401FF0 */

void __fastcall FUN_00401ff0(int param_1)

{
  if (*(void **)(param_1 + 0x358) != (void *)0x0) {
    _free(*(void **)(param_1 + 0x358));
  }
  *(undefined4 *)(param_1 + 0x358) = 0;
  return;
}

