/* Raw Ghidra reference; not compilable reconstruction. Address: 0042AC60 */

void __fastcall FUN_0042ac60(int param_1)

{
  if (*(int *)(param_1 + 0x1c) != 0) {
    *(undefined4 *)(*(int *)(param_1 + 0x1c) + 8) = *(undefined4 *)(param_1 + 0x20);
  }
  if (*(int *)(param_1 + 0x20) != 0) {
    *(undefined4 *)(*(int *)(param_1 + 0x20) + 4) = *(undefined4 *)(param_1 + 0x1c);
  }
  *(undefined4 *)(param_1 + 0x1c) = 0;
  *(undefined4 *)(param_1 + 0x20) = 0;
  return;
}

