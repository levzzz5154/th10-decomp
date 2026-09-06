/* Raw Ghidra reference; not compilable reconstruction. Address: 00438680 */

int __fastcall FUN_00438680(int param_1)

{
  if (0xf < *(uint *)(param_1 + 0x18)) {
    return *(int *)(param_1 + 4);
  }
  return param_1 + 4;
}

