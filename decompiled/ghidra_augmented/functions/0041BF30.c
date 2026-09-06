/* Raw Ghidra reference; not compilable reconstruction. Address: 0041BF30 */

undefined4 __fastcall FUN_0041bf30(int param_1)

{
  *(undefined4 *)(*(int *)(param_1 + 4) + 8) = *(undefined4 *)(param_1 + 8);
  if (*(int *)(param_1 + 8) != 0) {
    *(undefined4 *)(*(int *)(param_1 + 8) + 4) = *(undefined4 *)(param_1 + 4);
  }
  return 0;
}

