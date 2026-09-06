/* Raw Ghidra reference; not compilable reconstruction. Address: 004014F0 */

undefined4 __fastcall FUN_004014f0(int param_1)

{
  *(undefined4 *)(param_1 + 0x896c) = 0;
  *(undefined4 *)(param_1 + 0x8970) = 0;
  *(int *)(param_1 + 0x8990) = *(int *)(param_1 + 0x8990) + 1;
  return 1;
}

